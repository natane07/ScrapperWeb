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
    char nameTache[MAX_SETTING_LENGTH];
    char urlAction[3000];
    int sec =0;
    int min =0;
    int hour = 0;
    while (current != NULL)
    {
        printf("Current Element:%s \n", current->content);
        if(isSymbole(current->content, "=")){
            typeModeFile = ACTION;
        }
        else if (isSymbole(current->content, "+"))
        {
            typeModeFile = typeModeFile == ACTION ? OPTION : TACHE_OPTION;
        }
        else if (isSymbole(current->content, "=="))
        {
            typeModeFile = TACHE;
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
                }
                break;
            case OPTION:
                ok = parseIni(current->content, key, value);
                if(ok){
                    pushOptionListToAction(fileConfig.actions, key, value);
                }
                break;
            case TACHE:
                while(!isSymbole(current->content, "+")){
                    ok = parseIni(current->content, key, value);
                    if(ok){
                        if(isSymbole(key, "name")){
                            parseIni(current->content, key, nameTache);
                        }
                        else if(isSymbole(key, "hour")){
                            parseIni(current->content, key, value);
                            hour = atoi(value);
                        }
                        else if(isSymbole(key, "minute")){
                            parseIni(current->content, key, value);
                            min = atoi(value);
                        }
                        else if(isSymbole(key, "second")){
                            parseIni(current->content, key, value);
                            sec = atoi(value);
                        }
                    }
                    current = current->next;
                }
                pushTacheToList(fileConfig.taches, nameTache, hour, min, sec);
                hour = min = sec = 0;
                continue;
            case TACHE_OPTION:
                parsePlanificateur(&fileConfig, current->content);
                //printf("Element TACHE_OPTION:%s \n", current->content);
                break;
            default:
                break;
            }
        }
        printf("typeModeFile: %d\n",typeModeFile);
        current = current->next;
    }
    printf("\n\n");
    printActionList(fileConfig.actions);
    printf("\n\n");
    printTacheList(fileConfig.taches);
    return 0;
}
