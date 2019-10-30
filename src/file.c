#include "common.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

void initFs(AppData *appData)
{
    char path[MAX_PATH_LENGTH];
    List *settings = listInit();
    sprintf(path, "%s", getenv(LOCALSTORAGE));
    initFolders(path);
    initConfigFile(path, settings);
    applySettings(settings, appData);
    destroyList(settings);
}

void initFolders(char *path)
{
    char dirLocation[MAX_PATH_LENGTH];
    sprintf(dirLocation, "%s\\%s", path, MAIN_DIR);
    CreateDirectory(dirLocation, NULL);
}

void initConfigFile(char *path, List *settings)
{
    FILE *config = NULL;
    if (fileExists(path, CONFIG_FILE) == 1)
    {
        config = openFile(path, CONFIG_FILE, "r");
        if (config != NULL)
        {
            getFileContent(settings, MAX_SETTING_LENGTH, MIN_SETTING_LENGTH, config);
        }
    }
    /*else
    {
        config = openFile(path, CONFIG_FILE, "w");
        if (config != NULL)
        {
            printConfigFile(config, NULL);
        }
    }*/
}

int fileExists(char *basePath, char *filePath)
{
    char fileLocation[MAX_PATH_LENGTH];
    sprintf(fileLocation, "%s\\%s", basePath, filePath);
    if (_access(fileLocation, 0) != -1)
        return 1;
    return 0;
}

FILE *openFile(char *basePath, char *filePath, char *mode)
{
    char fileLocation[MAX_PATH_LENGTH];
    FILE *file = NULL;
    sprintf(fileLocation, "%s\\%s", basePath, filePath);
    file = fopen(fileLocation, mode);
    return file;
}

void applySettings(List *settings, AppData *appData)
{
    forEach(settings, applySetting, appData);
}

void applySetting(char *content, void *data)
{
    AppData *appData = data;
    char key[MAX_SETTING_LENGTH];
    char value[MAX_SETTING_LENGTH];
    int ok;
    ok = parseIni(content, key, value);
    if (ok)
    {
        if (strcmp(key, SETT_ADDR) == 0)
        {
            appData->address = setString(appData->address, value);
        }
        else if (strcmp(key, SETT_MAIL) == 0)
        {
            appData->mail = setString(appData->mail, value);
        }
        else if (strcmp(key, SETT_PHONE) == 0)
        {
            appData->phone = setString(appData->phone, value);
        }
        else if (strcmp(key, SETT_FIRSTNAME) == 0)
        {
            appData->firstName = setString(appData->firstName, value);
        }
        else if (strcmp(key, SETT_LASTNAME) == 0)
        {
            appData->lastName = setString(appData->lastName, value);
        }
        else if (strcmp(key, SETT_ZIPCODE) == 0)
        {
            appData->zipCode = setString(appData->zipCode, value);
        }
    }
}
void removeChar(char *str, char garbage) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

void removeComment(char *str, char garbage){
    char *ptr;
    ptr = strchr(str, garbage);
    if (ptr != NULL) {
        *ptr = '\0';
    }
}

void removeSpaces(char *str) 
{ 
    int count = 0; 

    for (int i = 0; str[i]; i++){
        if (str[i] != ' ') 
            str[count++] = str[i];
    }
    str[count] = '\0'; 
}

void getFileContent(List *storage, int bufferSize, int minLength, FILE *fp)
{
    char *buffer = malloc(bufferSize * sizeof(char));
    if (buffer == NULL)
        exit(-1);
    while (fgets(buffer, bufferSize, fp) != NULL)
    {
        remCrlf(buffer);
        if (strlen(buffer) > minLength){
            removeComment(buffer, '#');
            removeChar(buffer, '{');
            removeChar(buffer, '}');
            removeSpaces(buffer);
            push(storage, buffer);
        }
    }
    fclose(fp);
    free(buffer);
}

void saveConfigToFile(AppData *appData)
{
    FILE *fp = openFile(getenv(LOCALSTORAGE), CONFIG_FILE, "w");
    if (fp != NULL)
    {
        printConfigFile(fp, appData);
    }
}

void printConfigFile(FILE *fp, AppData *appData)
{
    if (appData == NULL)
    {
        printIniToFile(fp, SETT_ADDR, "");
        printIniToFile(fp, SETT_MAIL, "");
        printIniToFile(fp, SETT_PHONE, "");
        printIniToFile(fp, SETT_FIRSTNAME, "");
        printIniToFile(fp, SETT_LASTNAME, "");
        printIniToFile(fp, SETT_ZIPCODE, "");
    }
    else
    {
        printIniToFile(fp, SETT_ADDR, appData->address);
        printIniToFile(fp, SETT_MAIL, appData->mail);
        printIniToFile(fp, SETT_PHONE, appData->phone);
        printIniToFile(fp, SETT_FIRSTNAME, appData->firstName);
        printIniToFile(fp, SETT_LASTNAME, appData->lastName);
        printIniToFile(fp, SETT_ZIPCODE, appData->zipCode);
    }
    fclose(fp);
}