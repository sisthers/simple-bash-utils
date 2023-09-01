#include "grep.h"

void grep(char *fileName, int ar, char fileTempls[ar][BUFLENGTH], int ig,
          int vg, int cg, int lg, int ng, int hg, int og, int ec, int fc,
          int ifD) {
  int ifOnce = 0;
  int len = 0;
  int nOfL = 0;
  int fnOfL = 1;
  FILE *file = openFile(fileName, &len);
  char buffer[BUFLENGTH] = {'a', '\0'};
  char namenum[BUFLENGTH] = {'a', '\0'};
  char lastBuf[BUFLENGTH] = {'a', '\0'};
  if (og) len = 1;
  while (!readLine(file, buffer, &len)) {
    OTempl lineOTempl[BUFLENGTH];
    strcpy(namenum, "");
    int valGrep = grepLine(buffer, ar, fileTempls, lineOTempl, ig, vg, og, cg,
                           lg, ec, ifD);
    if (valGrep) {
      ifOnce = 1;
      nOfL++;
      if (fc > 1 && !hg) {
        strcat(namenum, fileName);
        strcat(namenum, ":");
      }
      if (ng && !cg) {
        char num[100];
        sprintf(num, "%d:", fnOfL);
        strcat(namenum, num);
      }
      if (!cg && !lg && !og) printf("%s%s", namenum, buffer);
      if (og && !lg && !cg && !vg) {
        qsort(lineOTempl, valGrep, sizeof(OTempl), OTempl_comparator);
        for (int j = 0; j < valGrep; j++) {
          printf("%s%s\n", namenum, lineOTempl[j].Templ);
          free(lineOTempl[j].Templ);
        }
      }
      strcpy(lastBuf, buffer);
    }
    fnOfL++;
  }
  if (lg && nOfL != 0)
    printf("%s\n", fileName);
  else if (!lg && cg) {
    if (hg || fc == 1)
      printf("%d\n", nOfL);
    else
      printf("%s:%d\n", fileName, nOfL);
  } else if (lastBuf[strlen(lastBuf) - 1] != '\n' && !og && ifOnce)
    printf("\n");
  closeFile(file);
}

int grepLine(char *buffer, int ar, char templs[ar][BUFLENGTH],
             OTempl lineOTempl[BUFLENGTH], int ig, int vg, int og, int cg,
             int lg, int ec, int ifD) {
  regex_t regex;
  int val = 0;
  if (vg && (!og || cg || lg)) val = 1;
  int igCase = ig;
  if (ifD)
    igCase = REG_NEWLINE;
  else if (ig == 1)
    igCase = REG_ICASE;
  for (int j = 0; j < ec; j++) {
    regcomp(&regex, templs[j], igCase);
    if (!og || cg || lg) {
      int fval = regexec(&regex, buffer, 0, NULL, 0) == 0;
      if (!vg && fval)
        val = 1;
      else if (vg && fval)
        val = 0;
    } else if (!vg) {
      regmatch_t pmatch[1];
      regoff_t off;
      char *s = buffer;
      int fval = 1;
      while (fval) {
        fval = regexec(&regex, s, (sizeof((pmatch)) / sizeof((pmatch)[0])),
                       pmatch, 0) == 0;
        if (fval) {
          off = pmatch[0].rm_so + (s - buffer);
          OTempl OTempl;
          OTempl.offset = (int)off;
          OTempl.Templ = malloc(BUFLENGTH);
          sprintf(OTempl.Templ, "%.*s",
                  (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
                  s + pmatch[0].rm_so);
          lineOTempl[val] = OTempl;
          s += pmatch[0].rm_eo;
          val++;
        }
      }
    }
    regfree(&regex);
  }
  return val;
}

int OTempl_comparator(const void *v1, const void *v2) {
  int res = 0;
  const OTempl *p1 = (OTempl *)v1;
  const OTempl *p2 = (OTempl *)v2;
  if (p1->offset < p2->offset)
    res = -1;
  else if (p1->offset > p2->offset)
    res = +1;
  return res;
}
