#ifndef CAT_CAT_H_
#define CAT_CAT_H_

#include "../common/fileIO.h"

void cat(FILE *file, int v, int T, int E, int s, int n, int b);
void s(char *buffer, int *isEmpty, int *notPrinting);
void v(char *buffer, char *result, int len);
void T(char *buffer, char *result);
void E(char *buffer, char *result);
void n(char *buffer, char *result, int *i, char *em);
void b(char *buffer, char *result, int *i, char *em);

#endif  // CAT_CAT_H_
