#include "common.h"

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
    char urlAction[MAX_STRING];
    int sec =0;
    int min =0;
    int hour = 0;
    char buffer[CURL_MAX_WRITE_SIZE];
    char mimeType[CURL_MAX_WRITE_SIZE];
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
    printf("\n\n");
    printf("\n\n");

    // HTTP REQUEST
    if (fileConfig.taches == NULL)
    {
        printf("Liste des taches vide");
        exit(-1);
    }
    Tache *currentTache = fileConfig.taches->first;
    Planificateur *currentPlanificateur = currentTache->planificateurList->first;
    Action *currentAction = fileConfig.actions->first;
    int currentTimeTache = 0;
    int sommeTimeTache = 0;
    int LOOP =0;
    bool versioning = false;
    char nameFile[MAX_PATH_LENGTH];
    while (LOOP == 0){ // LOOP
    while (currentTache != NULL) //liste des taches
    {
        while (currentPlanificateur != NULL) //liste des planificateurs
        {
            while (currentAction != NULL) //liste des Actions
            {
                if(strcmp(currentAction->name, currentPlanificateur->nameTache) == 0){
                    currentTimeTache = getCurrentTimeSec();
                    sommeTimeTache = convertTimeInSec(currentTache->hour, currentTache->minute, currentTache->seconde) + currentTache->currentTime;
                    if(currentTimeTache >= sommeTimeTache){
                        printf("\nNom Tache %s \n",currentTache->name);
                        printf("%s \n",currentAction->url);
                        HttpResponse response = setHttpResponseBuffer(buffer);
                        int code = httpGetHtml(currentAction->url, mimeType, (void *)&response, curlCallbackHtml);
                        printf("Mime-type: %s\n", mimeType);
                        char mimeTypeName[MAX_PATH_LENGTH];
                        char extensionFile[MAX_PATH_LENGTH];
                        parseMimeType(mimeType, mimeTypeName, extensionFile);

                        if(strcmp(mimeTypeName, "image") == 0){
                            createDir(currentTache->name);
                            versioning = isVersioning(currentAction->option);
                            if(versioning == true){
                                setNameFileImageWithVersioning(nameFile, currentAction->name, extensionFile);
                                downloadImage(currentAction->url, nameFile, currentTache->name, mimeType);
                            }
                            else{
                                sprintf(nameFile, "%s%s%s", currentAction->name, ".", extensionFile);
                                downloadImage(currentAction->url, nameFile, currentTache->name, mimeType);
                            }
                        }
                        else{
                            if (!code)
                            {
                                createDir(currentTache->name);
                                versioning = isVersioning(currentAction->option);
                                if(versioning == true){
                                    setNameFileWithVersioning(nameFile, currentAction->name);
                                    saveHtmlToFile(currentTache->name, nameFile, buffer, extensionFile);
                                    if(strcmp(extensionFile, "html") == 0)
                                        saveBaliseToFile(currentAction->option, currentTache->name, nameFile, buffer, extensionFile);
                                }
                                else{
                                    saveHtmlToFile(currentTache->name, currentAction->name, buffer, extensionFile);
                                    if(strcmp(extensionFile, "html") == 0)
                                        saveBaliseToFile(currentAction->option, currentTache->name, currentAction->name, buffer, extensionFile);
                                }
                                //printf("Buffer : %s", buffer);
                            }
                            else {
                                printf("fail HTPP");
                            }
                        }
                        memset(nameFile, 0, sizeof (nameFile));
                        memset(buffer, 0, sizeof (buffer));
                        memset(mimeType, 0, sizeof (mimeType));
                    }
                }
                currentAction = currentAction->next;
            }
            currentPlanificateur = currentPlanificateur->next;
            currentAction = fileConfig.actions->first;
        }
        currentTimeTache = getCurrentTimeSec();
        sommeTimeTache = convertTimeInSec(currentTache->hour, currentTache->minute, currentTache->seconde) + currentTache->currentTime;
        if(currentTimeTache >= sommeTimeTache)
            currentTache->currentTime = getCurrentTimeSec();

        currentTache = currentTache->next;
        if(currentTache != NULL)
            currentPlanificateur = currentTache->planificateurList->first;
    }
    currentTache = fileConfig.taches->first;
    currentPlanificateur = currentTache->planificateurList->first;
    sleep(1);
    }
    freeFileconfig(fileConfig);
    return 0;
}
