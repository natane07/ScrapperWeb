#include "common.h"

void removeSpaces(char *str) 
{ 
    int count = 0; 

    for (int i = 0; str[i]; i++){
        if (str[i] != ' ') 
            str[count++] = str[i];
    }
    str[count] = '\0'; 
} 

int main()
{
    char path[MAX_PATH_LENGTH];
    List *settings = listInit();
    sprintf(path, "%s", getenv(LOCALSTORAGE));
    initFolders(path);
    initConfigFile(path, settings);
    printList(settings);
        if (settings == NULL)
    {
        exit(-1);
    }

    Element *current = settings->first;

    while (current != NULL)
    {
        removeSpaces(current->content);
        printElement(current->content);
        current = current->next;
    }
    return 0;
}
