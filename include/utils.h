#ifndef UTILS_H

#define UTILS_H

#define STR_NULL "\0"

#include <windows.h>
#include "objects.h"
#include "curl/curl.h"

void remCrlf(char *);
void stringCopy(char *, char *, int);
char *setString(char *, char *);
char *resetString(char *, char *);
int isStringSafe(char *, char *);
void freeString(char *string);
int convertTimeInSec(int hour, int min, int sec);
int getCurrentTimeSec();
void setNameFileWithVersioning(char *nameFile, char * name);
void setNameFileImageWithVersioning(char *nameFile, char * name, char *extansion);

#endif
