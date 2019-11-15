#include "common.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <io.h>

void initFolders(char *path)
{
    char dirLocation[MAX_PATH_LENGTH];
    sprintf(dirLocation, "%s\\%s", path, MAIN_DIR);
    CreateDirectory(dirLocation, NULL);
}

void createDir(char *nameTache)
{
    char dirLocation[MAX_PATH_LENGTH];
    sprintf(dirLocation, "%s\\%s\\%s", getenv(LOCALSTORAGE), MAIN_DIR, nameTache);
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

void saveHtmlToFile(char *nameDir, char *nameAction, char *buffer, char* extansion)
{
    char fileLocation[MAX_PATH_LENGTH];
    char nameFile[MAX_PATH_LENGTH];
    sprintf(nameFile, "%s.%s", nameAction, extansion);
    sprintf(fileLocation, "%s\\%s\\%s", getenv(LOCALSTORAGE), MAIN_DIR, nameDir);
    FILE *fp = openFile(fileLocation, nameFile, "w");
    if (fp != NULL)
    {
        printHtmlToFile(fp, buffer);
    }
    fclose(fp);
}

void saveBaliseToFile(OptionList *list, char *nameDir, char *nameAction, char *buffer, char* extansion){
    if (list == NULL)
        return;
    
    char fileLocation[MAX_PATH_LENGTH];
    char nameFile[MAX_PATH_LENGTH];
    sprintf(fileLocation, "%s\\%s\\%s", getenv(LOCALSTORAGE), MAIN_DIR, nameDir);
    Option *currentOption = list->first;
    while (currentOption != NULL) //liste des options
    {
        if(strcmp(currentOption->optionId, OPTION_TYPE_BALISE) == 0){
            sprintf(nameFile, "%s_Balise_%s.%s", nameAction, currentOption->valueOption, extansion);
            getStringBetweenDelimiters(buffer, currentOption->valueOption, nameFile, fileLocation);
        }   
        currentOption = currentOption->next;
    }
}

void setFileConfig(FileConfig *fileConfig)
{
    fileConfig->actions = makeActionList();
    fileConfig->taches = makeTacheList();
}

/*void parseStringConfig(char * content, char *key, char *value){
    char * pch;
    pch = strtok (content,"->");
    while (pch != NULL)
    {
        strcpy(key, pch);
        printf("Key:%s\n",key);
        pch = strtok (NULL, "->");
        strncpy(value, content, pch - content);
        value[pch - content] = '\0';
        printf("Value:%s\n",value);
    }
}*/

char *constructStrLeft(char* opt){
  char *construct=malloc(strlen(opt)+2);
  char* str="<";
  strcpy(construct,str);
  strcat(construct,opt);
  return construct;
} 
 
char *constructStrRight(char* opt){
  char *construct=malloc(strlen(opt)+3);
  char* str="<";
  strcpy(construct,str);
  strcat(construct,"/");
  strcat(construct,opt);
  strcat(construct,">");
  return construct;
} 

int getLink(char* string)
{
     char *out;
     char *leftDelimiter="href=\"";
     char *rightDelimiter="\"";
     FILE* fichier = NULL;
     char* beginning = strstr(string, leftDelimiter);
     string = beginning;
     string +=strlen(leftDelimiter);
     if(beginning == NULL){
        return 1; 
     }
     char* end = strstr(string, rightDelimiter);
     if(end == NULL){
       return 2;
     }
     beginning += strlen(leftDelimiter);
 
     while (beginning!=NULL && end!=NULL){
     ptrdiff_t segmentLength = end - beginning;
     out = malloc(segmentLength + 1);
     strncpy(out, beginning, segmentLength);
     out[segmentLength] = 0;
     fichier = fopen("links.txt", "a+"); //specifier variable fichier :)
     if (fichier != NULL){
        fputs(out, fichier);
        fputs("\n", fichier);
        fclose(fichier);
     }
     beginning = strstr(string, leftDelimiter);
     if(beginning == NULL){
        break;
     }
     beginning=beginning+strlen(leftDelimiter);
     string = beginning;
     end = strstr(string, rightDelimiter);
	   if(end == NULL){
        break;
	   }
}
    return 0;
}                              


int getStringBetweenDelimiters(char* string, char* par, char* nameFile, char* fileLocation)
{
     char *rightDelimiter=constructStrRight(par);
     char *leftDelimiter=constructStrLeft(par);
     char* out;
     FILE* fichier = NULL;
     char* beginning = strstr(string, leftDelimiter);
      if(beginning == NULL){
        return 1; 
     }
     string = beginning;
     string +=strlen(leftDelimiter);
    
     char* end = strstr(string, rightDelimiter);
     if(end == NULL){
       return 2;
     }
    beginning = strstr(string, ">");
    beginning += 1; //fermeture chevron
    string = beginning;

    while (beginning!=NULL && end!=NULL){
     ptrdiff_t segmentLength = end - beginning;
     out = malloc(segmentLength + 1);
     strncpy(out, beginning, segmentLength);
     out[segmentLength] = 0;
     fichier = openFile(fileLocation, nameFile, "a+"); //specifier variable fichier :)
     if (fichier != NULL){
        fputs(out, fichier);
        fputs("\n", fichier);
        fclose(fichier);
     }
     beginning = strstr(string, leftDelimiter);
     if(beginning == NULL){
        break;
     }
     beginning=beginning+strlen(leftDelimiter);
     string = beginning;
     
     beginning=strstr(string,">")+1; //fermeture chevron
     string = beginning;
     
     end = strstr(string, rightDelimiter);
	   if(end == NULL){
        break;
	   }
    }
    
    return 0;
}   