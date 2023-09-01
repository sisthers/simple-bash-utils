#include "cat.h"
int main(int argc, char *argv[]) {
  int corCom = 1;
  char fNs[argc][BUFLENGTH];
  int v = 0, T = 0, E = 0, s = 0, n = 0, b = 0;
  int fc = 0;
  if (argc >= 2) {
    for (int k = 1; k < argc; k++) {
      char *option = argv[k];
      if (strcmp(option, "--number-nonblank") == 0) {
        b = 1;
      } else if (strcmp(option, "--number") == 0) {
        n = 1;
      } else if (strcmp(option, "--squeeze-blank") == 0) {
        s = 1;
      } else if (option[0] == '-') {
        for (int j = 1; (unsigned)j < strlen(option); j++) {
          if (option[j] == 'e') {
            v = 1;
            E = 1;
          } else if (option[j] == 'v') {
            v = 1;
          } else if (option[j] == 's') {
            s = 1;
          } else if (option[j] == 't') {
            v = 1;
            T = 1;
          } else if (option[j] == 'T') {
            T = 1;
          } else if (option[j] == 'E') {
            E = 1;
          } else if (option[j] == 'n') {
            n = 1;
          } else if (option[j] == 'b') {
            b = 1;
          } else {
            corCom = 0;
          }
        }
      } else {
        strcpy(fNs[fc++], option);
      }
    }
    if (n && b) {
      n = 0;
    }
    if (corCom) {
      for (int j = 0; j < fc; j++) {
        corCom = 1;
        FILE *file = openFile(fNs[j], &corCom);
        if (corCom) {
          cat(file, v, T, E, s, n, b);
          closeFile(file);
        } else if (!s) {
          fprintf(stderr, "s21_cat: %s: No such file or directory\n", fNs[j]);
        }
      }
    } else {
      fprintf(stderr, "s21_cat: Incorrect format\n");
    }
  } else {
    fprintf(stderr, "s21_cat: Incorrect format\n");
  }
  return 0;
}
