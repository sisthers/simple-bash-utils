#ifndef COMMON_FILEIO_H_
#define COMMON_FILEIO_H_

#include <stdio.h>
#include <string.h>

#define BUFLENGTH 4096

FILE *openFile(char *fileName, int *correctCom);
void closeFile(FILE *file);
int readLine(FILE *file, char *buffer, int *len);

#endif  // COMMON_FILEIO_H_
