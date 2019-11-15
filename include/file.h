#ifndef FILE_H

#define FILE_H

#include <stdio.h>
#include <windows.h>
#include "objects.h"
#include "list.h"

//Option
#define OPTION_VERSIONING "versioning"
#define OPTION_VERSIONING_ON "on"
#define OPTION_TYPE_BALISE "type"

//PATHS
#define LOCALSTORAGE "APPDATA"
#define MAIN_DIR "scrapperWeb"
#define CONFIG_FILE "scrapperWeb\\scrapperWeb.sconf"


void initFolders(char *);
void createDir(char *);
void initConfigFile(char *, List *);
int fileExists(char *, char *);
FILE *openFile(char *, char *, char *);
void getFileContent(List *, int, int, FILE *);
void saveHtmlToFile(char *, char *, char *, char*);
void saveBaliseToFile(OptionList *list, char *nameDir, char *nameAction, char *buffer, char* extansion);
void removeChar(char *, char);
void removeSpaces(char *);
void removeComment(char *str, char garbage);
char *constructStrLeft(char* opt);
char *constructStrRight(char* opt);
int getLink(char* string);
int getStringBetweenDelimiters(char* string, char* par, char* nameFile, char* fileLocation);
void setFileConfig(FileConfig *fileConfig);
#endif