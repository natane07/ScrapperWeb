#include "common.h"

void parseStringConfig(char * content, char *key, char *value){
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
        exit(-1);

    static FileConfig fileConfig;
    fileConfig.actions->first->option->first->next;
    Element *current = settings->first;
    int ok;
    TYPE_MODE_FILE typeModeFile = ACTION;
    char key[MAX_SETTING_LENGTH];
    char value[MAX_SETTING_LENGTH];
    while (current != NULL)
    {
        if(isSymbole(current->content, "=")){
            typeModeFile = ACTION;
        }
        else if (isSymbole(current->content, "+"))
        {
            typeModeFile = OPTION;
        }
        else {
            switch (typeModeFile)
            {
            case ACTION:
                ok = parseIni(current->content, key, value);
                if(ok){
                    printf("Key:%s\n", key);
                    printf("Value:%s\n", value);
                }
                break;
            case OPTION:
                ok = parseIni(current->content, key, value);
                if(ok){
                    printf("Key:%s\n", key);
                    printf("Value:%s\n", value);
                }
                break;
            case TACHE:
                break;
            default:
                break;
            }
        }
        //printElement(current->content);
        current = current->next;
    }
    return 0;
}
