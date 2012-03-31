#include <stdio.h>
#include <ruby.h>
#include <libguess/libguess.h>

VALUE string__guess_encoding(VALUE str) {
  printf("%s\n", libguess_determine_encoding(RSTRING_PTR(str), RSTRING_LEN(str), "Japanese"));
  return Qfalse;
}

void Init_guess() {
  rb_define_method(rb_cString, "guess_encoding", string__guess_encoding, 0);
}
