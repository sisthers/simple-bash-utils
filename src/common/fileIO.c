#include "fileIO.h"

int readLine(FILE *file, char *buffer, int *len) {
  int enOfFile = 0;
  if (!fgets(buffer, BUFLENGTH, file)) enOfFile = 1;
  *len = 0;
  int nul = 0;
  int on = 1;
  for (; on && !enOfFile; *len = *len + 1) {
    if (buffer[*len] == '\n')
      nul = 1;
    else if (buffer[*len] == '\0') {
      if (nul)
        on = 0;
      else
        nul = 0;
    }
  }
  return enOfFile;
}

FILE *openFile(char *fileName, int *correctCom) {
  FILE *file;
  if (!(file = fopen(fileName, "r"))) *correctCom = 0;
  return file;
}
void closeFile(FILE *file) { fclose(file); }
