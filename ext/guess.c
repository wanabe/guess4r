#include <stdio.h>
#include <ruby.h>
#include <ruby/encoding.h>
#include <libguess/libguess.h>

#ifndef GUESS_REGION_DEFAULT
#define GUESS_REGION_DEFAULT GUESS_REGION_JP
#endif

VALUE guess4r_enc__guess_region(VALUE klass) {
  return rb_ivar_get(klass, rb_intern("guess_region"));
}

static rb_encoding* _guess_encoding(VALUE str) {
  rb_encoding *enc;
  const char *encname;

  encname = libguess_determine_encoding(RSTRING_PTR(str), RSTRING_LEN(str),
                                        RSTRING_PTR(guess4r_enc__guess_region(rb_cEncoding)));
  return rb_enc_find(encname);
}

static VALUE guess4r_str__guess_encoding(VALUE str) {
  return rb_enc_from_encoding(_guess_encoding(str));
}

static VALUE guess4r_str__guess_bang(VALUE str) {
  return rb_enc_associate(str, _guess_encoding(str));
}

static VALUE guess4r_str__guess(VALUE str) {
  return guess4r_str__guess_bang(rb_str_dup(str));
}

static VALUE guess4r_f__guess_open(int argc, VALUE *argv) {
  VALUE *args, opt, f, str, enc;
  int i;

  args = ALLOCA_N(VALUE, argc + 1);
  args[0] = argv[0];
  if (TYPE(argv[argc - 1]) != T_HASH) {
    args[1] = args[argc++] = rb_hash_new();
  } else {
    args[1] = argv[argc - 1];
  }

  rb_hash_aset(args[1], ID2SYM(rb_intern("encoding")), rb_const_get(rb_cEncoding, rb_intern("ASCII_8BIT")));
  rb_funcall(args[1], rb_intern("delete"), 1, ID2SYM(rb_intern("external_encoding")));
  rb_funcall(args[1], rb_intern("delete"), 1, ID2SYM(rb_intern("internal_encoding")));
  f = rb_funcall2(rb_mKernel, rb_intern("open"), 2, args);
  str = rb_funcall(f, rb_intern("read"), 0);
  enc = guess4r_str__guess_encoding(str);
  rb_funcall(f, rb_intern("close"), 0);
  rb_hash_aset(args[1], ID2SYM(rb_intern("encoding")), enc);

  MEMCPY(args, argv, VALUE, argc - 1);
  return rb_funcall_passing_block(rb_mKernel, rb_intern("open"), argc, args);
}

VALUE guess4r_enc__guess_region_set(VALUE klass, VALUE str) {
  return rb_str_replace(guess4r_enc__guess_region(klass), str);
}

void Init_guess() {
  rb_define_method(rb_cString, "guess_encoding", guess4r_str__guess_encoding, 0);
  rb_define_method(rb_cString, "guess!", guess4r_str__guess_bang, 0);
  rb_define_method(rb_cString, "guess", guess4r_str__guess, 0);
  rb_define_global_function("guess_open", guess4r_f__guess_open, -1);
  rb_ivar_set(rb_cEncoding, rb_intern("guess_region"), rb_str_new2(GUESS_REGION_DEFAULT));
  rb_define_singleton_method(rb_cEncoding, "guess_region", guess4r_enc__guess_region, 0);
  rb_define_singleton_method(rb_cEncoding, "guess_region=", guess4r_enc__guess_region_set, 1);
}
