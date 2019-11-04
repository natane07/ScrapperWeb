#include "common.h"
#include <string.h>
#include <stdio.h>

int parseIni(char *content, char *key, char *value)
{
    char *pch;
    pch = strchr(content, '-');
    if (pch == NULL)
    {
        return 0;
    }
    strcpy(value, pch + 2);
    strncpy(key, content, pch - content);
    key[pch - content] = '\0';
    return 1;
}

void parsePlanificateur(char *content){
    removeChar(content, '(');
    removeChar(content, ')'); 
    char *token = strtok(content, ",");

    while (token != NULL) 
    { 
        printf("%s\n", token); 
        token = strtok(NULL, "-"); 
    } 
}

void printIniToFile(FILE *file, char *key, char *value)
{
    fprintf(file, "%s=%s\n", key, value);
}

void printIniToString(char *str, char *key, char *value)
{
    sprintf(str, "%s=%s", key, value);
}

bool isSymbole(char *str, char *comparator){
    if (strcmp(str, comparator) == 0){
        return 1;
    }
    return 0;
}