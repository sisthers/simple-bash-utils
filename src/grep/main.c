#include "grep.h"

int main(int argc, char *argv[]) {
  int corCom = 1;
  char fTls[argc][BUFLENGTH];
  char fNs[argc][BUFLENGTH];
  char templs[argc][BUFLENGTH];
  int e = 0, i = 0, v = 0, c = 0, l = 0, n = 0, h = 0, s = 0, f = 0, o = 0;
  int ec = 0, tc = 0, fc = 0;
  int ifT = 1;
  if (argc >= 3) {
    for (int k = 1; k < argc; k++)
      if (strcmp(argv[k], "-e") == 0)
        ifT = 0;
      else if ((argv[k][0] == '-' &&
                (argv[k][1] == 'e' || strstr(argv[k], "e") != NULL ||
                 argv[k][1] == 'f')) ||
               (argv[k][strlen(argv[k]) - 2] == '-' &&
                argv[k][strlen(argv[k]) - 1] == 'e'))
        ifT = 0;
    for (int k = 1; k < argc; k++) {
      char *option = argv[k];
      if (e) {
        templs[ec][0] = 'q';
        strcpy(templs[ec++], option);
        e = 0;
      } else if (f) {
        strcpy(fTls[tc++], option);
        f = 0;
      } else if (strcmp(option, "-e") == 0) {
        e = 1;
      } else if (strcmp(option, "-f") == 0) {
        f = 1;
      } else if (option[0] == '-') {
        int ifOp = 0;
        for (int j = 1; (unsigned)j < strlen(option); j++) {
          if (option[j] == 'i') {
            i = 1;
            ifOp = 1;
          } else if (option[j] == 'v') {
            v = 1;
            ifOp = 1;
          } else if (option[j] == 'c') {
            c = 1;
            ifOp = 1;
          } else if (option[j] == 'l') {
            l = 1;
            ifOp = 1;
          } else if (option[j] == 'n') {
            n = 1;
            ifOp = 1;
          } else if (option[j] == 'h') {
            h = 1;
            ifOp = 1;
          } else if (option[j] == 's') {
            s = 1;
            ifOp = 1;
          } else if (option[j] == 'o') {
            o = 1;
            ifOp = 1;
          } else if (option[j] == 'e') {
            ifT = 0;
            if ((unsigned)j == strlen(option) - 1) {
              e = 1;
            } else {
              char temE[BUFLENGTH];
              int h = 0;
              int jD = j;
              for (; (unsigned)h < strlen(option) - j; h++)
                temE[h] = option[++jD];
              j = strlen(option);
              temE[h] = '\0';
              ifOp = 1;
              strcpy(templs[ec++], temE);
            }
          }
        }
        if (!ifOp) corCom = 0;
      } else if (ifT) {
        strcpy(templs[ec++], option);
        ifT = 0;
      } else {
        strcpy(fNs[fc++], option);
      }
    }
    if (corCom) {
      for (int j = 0; j < tc; j++) {
        int corComf = 1;
        FILE *file = openFile(fTls[j], &corComf);
        if (corComf) {
          int len = 0;
          while (!readLine(file, templs[ec++], &len)) {
            char cop[BUFLENGTH];
            int k = 0;
            for (; (unsigned)k < strlen(templs[ec - 1]) &&
                   templs[ec - 1][k] != '\n';
                 k++)
              cop[k] = templs[ec - 1][k];
            cop[k] = '\0';
            strcpy(templs[ec - 1], cop);
          }
          ec--;
          closeFile(file);
        } else {
          fprintf(stderr, "s21_grep: %s: No such file or directory\n", fTls[j]);
          corCom = 0;
        }
      }
      if (corCom) {
        int ifD = 0;
        for (int j = 0; j < ec; j++)
          if (strcmp(templs[j], ".") == 0) ifD = 1;
        for (int j = 0; j < fc; j++) {
          corCom = 1;
          FILE *file = openFile(fNs[j], &corCom);
          if (corCom) {
            closeFile(file);
            grep(fNs[j], argc, templs, i, v, c, l, n, h, o, ec, fc, ifD);
          } else if (!s) {
            fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                    fNs[j]);
          }
        }
      }
    } else {
      fprintf(stderr, "s21_grep: Incorrect format\n");
    }

  } else {
    fprintf(stderr, "s21_grep: Incorrect format\n");
  }
  return 0;
}
