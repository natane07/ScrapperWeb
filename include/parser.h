#ifndef PARSER_H

#define PARSER_H

#include <stdio.h>

int parseIni(char *, char *, char *);
void parsePlanificateur(FileConfig *, char *);
void printIniToFile(FILE *, char *, char *);
void printHtmlToFile(FILE *, char *);
void printIniToString(char *, char *, char *);
bool isSymbole(char *, char *);
int parseMimeType(char *content, char* key, char *value);

#endif