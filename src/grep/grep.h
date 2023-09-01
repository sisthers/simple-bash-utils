#ifndef GREP_GREP_H_
#define GREP_GREP_H_

#include <regex.h>
#include <stdlib.h>

#include "../common/fileIO.h"

typedef struct OTempl {
  char *Templ;
  int offset;
} OTempl;

void grep(char *fileName, int ar, char fileTempls[ar][BUFLENGTH], int ig,
          int vg, int cg, int lg, int ng, int hg, int og, int ec, int fc,
          int ifD);
int grepLine(char *buffer, int ar, char templs[ar][BUFLENGTH],
             OTempl lineOTempl[BUFLENGTH], int ig, int vg, int og, int cg,
             int lg, int ec, int ifD);
int OTempl_comparator(const void *v1, const void *v2);

#endif  // GREP_GREP_H_
