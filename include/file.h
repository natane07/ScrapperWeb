#ifndef FILE_H

#define FILE_H

#include <stdio.h>
#include <windows.h>
#include "objects.h"
#include "list.h"

//settings
#define SETT_PHONE "phone"
#define SETT_MAIL "mail"
#define SETT_ADDR "address"
#define SETT_FIRSTNAME "firstName"
#define SETT_LASTNAME "lastName"
#define SETT_ZIPCODE "zipCode"

//PATHS
#define LOCALSTORAGE "APPDATA"
#define MAIN_DIR "scrapperWeb"
#define CONFIG_FILE "scrapperWeb\\scrapperWeb.cfg"

void initFs(AppData *);
void initFolders(char *);
void initConfigFile(char *, List *, AppData *);
int fileExists(char *, char *);
FILE *openFile(char *, char *, char *);
void applySettings(List *, AppData *);
void applySetting(char *, void *);
void getFileContent(List *, int, int, FILE *);
void saveConfigToFile(AppData *appData);
void printConfigFile(FILE *, AppData *);

#endif