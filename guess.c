#include <stdio.h>
#include <ruby.h>
#include <ruby/encoding.h>
#include <libguess/libguess.h>

static rb_encoding* _guess_encoding(VALUE str) {
  rb_encoding *enc;
  const char *encname;

  encname = libguess_determine_encoding(RSTRING_PTR(str), RSTRING_LEN(str), "Japanese");
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

void Init_guess() {
  rb_define_method(rb_cString, "guess_encoding", guess4r_str__guess_encoding, 0);
  rb_define_method(rb_cString, "guess!", guess4r_str__guess_bang, 0);
  rb_define_method(rb_cString, "guess", guess4r_str__guess, 0);
}
