#include "common.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>

void remCrlf(char *str)
{
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}

void stringCopy(char *destination, char *source, int length)
{
    strncpy(destination, source, length - 1);
    remCrlf(destination);
}

char *setString(char *destination, char *source)
{
    destination = malloc((strlen(source) + 1) * sizeof(char));
    if (destination == NULL)
        exit(-1);
    strcpy(destination, source);
    return destination;
}

char *resetString(char *destination, char *source)
{
    free(destination);
    return setString(destination, source);
}

int isStringSafe(char *str, char *allowedChars)
{
    char *match;
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        match = strpbrk(str + i, allowedChars);
        if (match != str + i)
        {
            return 0;
        }
    }
    return 1;
}

void freeString(char *string)
{
    if (strlen(string) > 0)
    {
        free(string);
    }
    string = STR_NULL;
}

int convertTimeInSec(int hour, int min, int sec){
    return (hour * 3600) + (min * 60) + sec;
}

int getCurrentTimeSec(){
    time_t now;
    struct tm *nowTm;
    int hourTime = 0;
    int minTime = 0;
    int secTime = 0;

    now = time(NULL);
    nowTm = localtime(&now);
    hourTime = nowTm->tm_hour;
    minTime = nowTm->tm_min;
    secTime = nowTm->tm_sec;
    return convertTimeInSec(hourTime, minTime, secTime);
}

void setNameFileWithVersioning(char *nameFile, char * name){
    time_t now;
    struct tm *nowTm;
    int hourTime = 0;
    int minTime = 0;
    int secTime = 0;

    now = time(NULL);
    nowTm = localtime(&now);
    hourTime = nowTm->tm_hour;
    minTime = nowTm->tm_min;
    secTime = nowTm->tm_sec;
    sprintf(nameFile, "%dh%dm%ds_%s",hourTime, minTime, secTime, name);
}

void setNameFileImageWithVersioning(char *nameFile, char * name, char *extansion){
    time_t now;
    struct tm *nowTm;
    int hourTime = 0;
    int minTime = 0;
    int secTime = 0;

    now = time(NULL);
    nowTm = localtime(&now);
    hourTime = nowTm->tm_hour;
    minTime = nowTm->tm_min;
    secTime = nowTm->tm_sec;
    sprintf(nameFile, "%dh%dm%ds_%s.%s",hourTime, minTime, secTime, name, extansion);
}

