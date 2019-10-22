#include "common.h"
#include <string.h>
#include <stdio.h>

int parseIni(char *content, char *key, char *value)
{
    char *pch;
    pch = strchr(content, '=');
    if (pch == NULL)
    {
        return 0;
    }
    strcpy(value, pch + 1);
    strncpy(key, content, pch - content);
    key[pch - content] = '\0';
    return 1;
}

void printIniToFile(FILE *file, char *key, char *value)
{
    fprintf(file, "%s=%s\n", key, value);
}

void printIniToString(char *str, char *key, char *value)
{
    sprintf(str, "%s=%s", key, value);
}