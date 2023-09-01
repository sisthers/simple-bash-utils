#include "cat.h"

void cat(FILE *file, int vc, int Tc, int Ec, int sc, int nc, int bc) {
  char buffer[BUFLENGTH] = {'a', '\0'};
  char result[BUFLENGTH] = {'a', '\0'};
  strcpy(buffer, "");
  strcpy(result, "");
  char empty[6] = "     ";
  int i = 1;
  int isEmpty = 0;
  int len;
  int notPrinting = 0;
  while (!readLine(file, buffer, &len)) {
    if (i >= 10 && i < 100)
      strcpy(empty, "    ");
    else if (i >= 100 && i < 1000)
      strcpy(empty, "   ");
    else if (i >= 1000 && i < 10000)
      strcpy(empty, "  ");
    else if (i >= 10000 && i < 100000)
      strcpy(empty, " ");
    else if (i >= 100000 && i < 1000000)
      strcpy(empty, "");
    if (sc) {
      s(buffer, &isEmpty, &notPrinting);
    }
    if (!notPrinting) {
      if (vc) {
        v(buffer, result, len);
        strcpy(buffer, result);
        strcpy(result, "");
      }
      if (Tc) {
        T(buffer, result);
        strcpy(buffer, result);
        strcpy(result, "");
      }
      if (Ec) {
        E(buffer, result);
        strcpy(buffer, result);
        strcpy(result, "");
      }
      if (nc) {
        n(buffer, result, &i, empty);
        strcpy(buffer, result);
        strcpy(result, "");
      }
      if (bc) {
        b(buffer, result, &i, empty);
        strcpy(buffer, result);
        strcpy(result, "");
      }
      printf("%s", buffer);
    }
  }
}
void s(char *buffer, int *isEmpty, int *notPrinting) {
  if (strcmp(buffer, "\n") == 0) {
    if (!*isEmpty)
      *isEmpty = 1;
    else
      *notPrinting = 1;
  } else {
    *notPrinting = 0;
    *isEmpty = 0;
  }
}

void v(char *buffer, char *result, int len) {
  int i = 0;
  for (; i < len; i++) {
    char cp[2];
    cp[0] = buffer[i];
    cp[1] = '\0';
    if ((int)buffer[i] > 0 && (int)buffer[i] < 32 && (int)buffer[i] != 9 &&
        (int)buffer[i] != 10) {
      strcat(result, "^");
      cp[0] = buffer[i] + 64;
      strcat(result, cp);
    } else if ((int)buffer[i] == 127)
      strcat(result, "^?");
    else if (i != len - 1 && buffer[i] == '\0')
      strcat(result, "^@");
    else
      strcat(result, cp);
  }
}

void T(char *buffer, char *result) {
  int i = 0;
  for (; buffer[i] != '\0'; i++) {
    char cp[2] = " \0";
    cp[0] = buffer[i];
    if (buffer[i] == '\t')
      strcat(result, "^I");
    else
      strcat(result, cp);
  }
}

void E(char *buffer, char *result) {
  int i = 0;
  for (; buffer[i] != '\0'; i++) {
    char cp[2] = " \0";
    cp[0] = buffer[i];
    if (buffer[i] == '\n') {
      strcat(result, "$");
      strcat(result, cp);
    } else
      strcat(result, cp);
  }
}

void n(char *buffer, char *result, int *i, char *em) {
  char num[100];
  strcat(result, em);
  sprintf(num, "%d", *i);
  strcat(result, num);
  strcat(result, "\t");
  strcat(result, buffer);
  *i = *i + 1;
}

void b(char *buffer, char *result, int *i, char *em) {
  char num[100];
  if (strcmp(buffer, "\n") != 0 && strcmp(buffer, "$\n") != 0) {
    strcat(result, em);
    sprintf(num, "%d", *i);
    strcat(result, num);
    strcat(result, "\t");
    strcat(result, buffer);
    *i = *i + 1;
  } else {
    strcat(result, buffer);
  }
}
