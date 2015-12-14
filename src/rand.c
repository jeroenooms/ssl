#include <R.h>
#include <Rinternals.h>
#include "utils.h"
#include <openssl/rand.h>

SEXP R_RAND_bytes(SEXP n, SEXP pseudo) {
  int use_pseudo = asLogical(pseudo);
  int length = asInteger(n);
  if(length <= 0)
    return allocVector(RAWSXP, 0);
  int result;
  unsigned char buf[length];
  if(use_pseudo){
    result = RAND_pseudo_bytes(buf, length);
  } else {
    result = RAND_bytes(buf, length);
  }
  if(!result) {
    error("Failed to generated pseudo random bytes.");
  }

  SEXP out = PROTECT(allocVector(RAWSXP, length));
  memcpy(RAW(out), buf, length);
  UNPROTECT(1);
  return out;
}
