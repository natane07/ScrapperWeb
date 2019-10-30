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

void setFileConfig(FileConfig *fileConfig)
{
    fileConfig->actions = makeActionList();
    fileConfig->taches = makeTacheList();
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
    setFileConfig(&fileConfig);

    Element *current = settings->first;
    int ok;
    TYPE_MODE_FILE typeModeFile = ACTION;
    char key[MAX_SETTING_LENGTH];
    char value[MAX_SETTING_LENGTH];
    char nameAction[MAX_SETTING_LENGTH];
    char urlAction[3000];
    while (current != NULL)
    {
        if(isSymbole(current->content, "=")){
            typeModeFile = ACTION;
        }
        else if (isSymbole(current->content, "+"))
        {
            typeModeFile = typeModeFile == ACTION ? OPTION : TACHE_OPTION;
        }
        else {
            switch (typeModeFile)
            {
            case ACTION:
                ok = parseIni(current->content, key, nameAction);
                current = current->next;
                ok = parseIni(current->content, key, urlAction);
                if(ok){
                    pushActionToList(fileConfig.actions, nameAction, urlAction);
                    //printf("Key:%s\n", nameAction);
                    //printf("Value:%s\n", urlAction);
                }
                break;
            case OPTION:
                ok = parseIni(current->content, key, value);
                if(ok){
                    pushOptionListToAction(fileConfig.actions, key, value);
                    //printf("Key:%s\n", key);
                    //printf("Value:%s\n", value);
                }
                break;
            case TACHE:
                break;
            default:
                break;
            }
        }
        current = current->next;
    }
    printActionList(fileConfig.actions);
    return 0;
}
