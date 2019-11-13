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

void initMemory(char *str, int length)
{
    memset(str, '\0', length);
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

int containsCharNTimes(char *str, char c, int amount)
{
    char *ptr = strchr(str, c);
    int counter = 0;
    while (ptr != NULL)
    {
        ptr = strchr(ptr + 1, c);
        counter++;
    }
    return counter == amount;
}

int compareKey(char *ini, char *comparator)
{
    int ok;
    char key[MAX_SETTING_LENGTH];
    char value[MAX_SETTING_LENGTH];
    ok = parseIni(ini, key, value);
    if (ok)
    {
        return strcmp(comparator, key) == 0;
    }
    return 0;
}

int simpleCompare(char *lstr, char *comparator)
{
    return strcmp(comparator, lstr) == 0;
}

void printError(const char *error)
{
    MessageBox(NULL, error, "Error!", MB_ICONERROR | MB_OK);
}

void printInfo(const char *info)
{
    MessageBox(NULL, info, "Infomation", MB_ICONINFORMATION | MB_OK);
}

int addStringToCombo(HWND hwnd, int controlId, char *content)
{
    return SendDlgItemMessage(hwnd, controlId, CB_ADDSTRING, (WPARAM)0, (LPARAM)content);
}

void addStringToComboDir(HWND combo, char *content)
{
    SendMessage(combo, CB_ADDSTRING, (WPARAM)0, (LPARAM)content);
}

int addStringToList(HWND hwnd, int controlId, char *content)
{
    return SendDlgItemMessage(hwnd, controlId, LB_ADDSTRING, (WPARAM)0, (LPARAM)content);
}

void removeStringFromList(HWND hwnd, int controlId, int position)
{
    return SendDlgItemMessage(hwnd, controlId, LB_DELETESTRING, (WPARAM)position, (LPARAM)0);
}

int findStringIndexInCombo(HWND hwnd, int controlId, char *content)
{
    return SendDlgItemMessage(hwnd, controlId, CB_FINDSTRING, (WPARAM)1, (LPARAM)content);
}

int findStringIndexInComboDir(HWND hwnd, char *content)
{
    return SendMessage(hwnd, CB_FINDSTRING, (WPARAM)1, (LPARAM)content);
}

void setComboCursor(HWND hwnd, int controlId, int position)
{
    SendDlgItemMessage(hwnd, controlId, CB_SETCURSEL, (WPARAM)position, (LPARAM)0);
}

void setComboCursorDir(HWND combo, int position)
{
    SendMessage(combo, CB_SETCURSEL, (WPARAM)position, (LPARAM)0);
}

int getComboCursor(HWND hwnd, int controlId)
{
    return SendDlgItemMessage(hwnd, controlId, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
}

int getComboCursorDir(HWND combo)
{
    return SendMessage(combo, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
}

void destroyComboContentDir(HWND combo)
{
    SendMessage(combo, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
}

void destroyComboContent(HWND hwnd, int controlId)
{
    SendDlgItemMessage(hwnd, controlId, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
}

void sendWinText(HWND hwnd, int controlId, char *text)
{
    SendDlgItemMessage(hwnd, controlId, WM_SETTEXT, (WPARAM)0, (LPARAM)text);
}

void sendWinTextDir(HWND hwnd, char *text)
{
    SendMessage(hwnd, WM_SETTEXT, (WPARAM)0, (LPARAM)text);
}

void getStringFromCombo(HWND hwnd, int controlId, int index, char *destination)
{
    SendDlgItemMessage(hwnd, controlId, CB_GETLBTEXT, (WPARAM)index, (LPARAM)destination);
}

void getStringFromComboDir(HWND combo, int index, char *destination)
{
    SendMessage(combo, CB_GETLBTEXT, (WPARAM)index, (LPARAM)destination);
}

void getStringFromWin(HWND hwnd, int controlId, char *destination, int maxLength)
{
    SendDlgItemMessage(hwnd, controlId, WM_GETTEXT, (WPARAM)maxLength, (LPARAM)destination);
}

void getStringFromWinDir(HWND win, char *destination, int maxLength)
{
    SendMessage(win, WM_GETTEXT, (WPARAM)maxLength, (LPARAM)destination);
}

int getStringLengthFromWin(HWND hwnd, int controlId)
{
    return SendDlgItemMessage(hwnd, controlId, WM_GETTEXTLENGTH, (WPARAM)0, (LPARAM)0);
}

void getCurrentStringFromComboDir(HWND combo, char *destination)
{
    getStringFromComboDir(combo, getComboCursorDir(combo), destination);
}

void getCurrentStringFromCombo(HWND hwnd, int controlId, char *destination)
{
    getStringFromCombo(hwnd, controlId, getComboCursor(hwnd, controlId), destination);
}

void clearListBox(HWND hwnd, int controlId)
{
    SendDlgItemMessage(hwnd, controlId, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
}

int getRadioState(HWND hwnd)
{
    return SendMessage(hwnd, BM_GETCHECK, (WPARAM)0, (LPARAM)0);
}

void enableRadio(HWND hwnd)
{
    SendMessage(hwnd, BM_SETCHECK, (WPARAM)BST_CHECKED, (LPARAM)0);
}

void disableRadio(HWND hwnd)
{
    SendMessage(hwnd, BM_SETCHECK, (WPARAM)BST_UNCHECKED, (LPARAM)0);
}

void changeRadioState(HWND hwnd)
{
    int checked = SendMessage(hwnd, BM_GETCHECK, (WPARAM)0, (LPARAM)0);
    if (checked)
    {
        SendMessage(hwnd, BM_SETCHECK, (WPARAM)BST_UNCHECKED, (LPARAM)0);
    }
    else
    {
        SendMessage(hwnd, BM_SETCHECK, (WPARAM)BST_CHECKED, (LPARAM)0);
    }
}

void setRadioState(HWND hwnd, int checked)
{
    if (checked)
    {
        SendMessage(hwnd, BM_SETCHECK, (WPARAM)BST_CHECKED, (LPARAM)0);
    }
    else
    {
        SendMessage(hwnd, BM_SETCHECK, (WPARAM)BST_UNCHECKED, (LPARAM)0);
    }
}

void enableEdit(HWND edit)
{
    SendMessage(edit, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
}

void disableEdit(HWND edit)
{
    SendMessage(edit, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
}

int getListCursor(HWND hwnd, int controlId)
{
    return SendDlgItemMessage(hwnd, controlId, LB_GETCARETINDEX, (WPARAM)0, (LPARAM)0);
}

void createClass(WNDCLASSEX *wc, HINSTANCE hInstance, const char *className, LRESULT(CALLBACK *wndProc)(HWND, UINT, WPARAM, LPARAM))
{
    wc->cbSize = sizeof(WNDCLASSEX);
    wc->style = 0;
    wc->lpfnWndProc = wndProc;
    wc->cbClsExtra = 0;
    wc->cbWndExtra = 0;
    wc->hInstance = hInstance;
    wc->hIcon = NULL;
    wc->hCursor = LoadCursor(NULL, IDC_ARROW);
    wc->hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc->lpszMenuName = NULL;
    wc->lpszClassName = className;
    wc->hIconSm = NULL;
}

WinPosition getChildWindowPosition(HWND hwnd)
{
    RECT winCoo;
    WinPosition winPos;
    GetWindowRect(hwnd, &winCoo);
    MapWindowPoints(HWND_DESKTOP, GetParent(hwnd), (LPPOINT)&winCoo, 2);
    winPos.x = winCoo.left;
    winPos.y = winCoo.top;
    winPos.width = winCoo.right - winCoo.left;
    winPos.height = winCoo.bottom - winCoo.top;
    return winPos;
}

void moveWindowBy(HWND hwnd, int x, int y)
{
    WinPosition winPos = getChildWindowPosition(hwnd);
    MoveWindow(hwnd, winPos.x + x, winPos.y + y, winPos.width, winPos.height, TRUE);
}

void destroyMenu(HWND *controls, int size)
{
    int i;
    for (i = 0; i < size; i++)
        DestroyWindow(controls[i]);
}

void debugAppData(AppData *appData)
{
    puts("AppData {");
    printf("address: %s\n", appData->address);
    printf("phone: %s\n", appData->phone);
    printf("mail: %s\n", appData->mail);
    printf("firstName: %s\n", appData->firstName);
    printf("lastName: %s\n", appData->lastName);
    printf("zipCode: %s\n", appData->zipCode);
    puts("};");
}

void debugInfos(Infos *infos)
{
    puts("Infos {");
    printf("address: %s\n", infos->address);
    printf("phone: %s\n", infos->phone);
    printf("mail: %s\n", infos->mail);
    printf("firstName: %s\n", infos->firstName);
    printf("lastName: %s\n", infos->lastName);
    printf("zipCode: %s\n", infos->zipCode);
    puts("};");
}

void freeString(char *string)
{
    if (strlen(string) > 0)
    {
        free(string);
    }
    string = STR_NULL;
}

void verifyPointer(void *pointer, const char *message)
{
    if (pointer == NULL)
    {
        printf("%s\n", message);
        exit(EXIT_FAILURE);
    }
}

void initArray(char *value, char **array, int arraySize)
{
    int i;

    for (i = 0; i < arraySize; i++)
    {
        array[i] = value;
    }
}

int inArray(const char *value, char **array, int arraySize)
{
    int i;

    for (i = 0; i < arraySize; i++)
    {
        if (strcmp(array[i], value) == 0)
        {
            return 0;
        }
    }

    return 1;
}

JsonResponse setJsonResponseBuffer(char *buffer)
{
    JsonResponse response;
    response.buffer = buffer;
    response.position = 0;
    return response;
}

void curlSetDefaultOptions(CURL *curl, void *response, size_t (*callback)(char *, size_t, size_t, void *))
{
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
}

size_t curlCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    JsonResponse *response = (JsonResponse *)userdata;
    size_t bytes = nmemb * size;
    size_t initialPosition = response->position;
    memcpy(response->buffer + response->position, ptr, bytes);
    response->position += bytes;
    memset(response->buffer + response->position, 0, 1);
    return strlen(response->buffer) - initialPosition;
}

int httpGet(char *url, void *buffer, size_t (*callback)(char *, size_t, size_t, void *))
{
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (!curl)
    {
        printError(ERR_HTTP_INIT);
        return -1;
    }
    curlSetDefaultOptions(curl, buffer, callback);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        printError(curl_easy_strerror(res));
        return res;
    }
    curl_easy_cleanup(curl);
    return CURLE_OK;
}

int httpPost(char *url, void *responseBuffer, char *body, size_t (*callback)(char *, size_t, size_t, void *))
{
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (!curl)
    {
        printError(ERR_HTTP_INIT);
        return -1;
    }
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curlSetDefaultOptions(curl, responseBuffer, callback);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        printError(curl_easy_strerror(res));
        return res;
    }
    curl_easy_cleanup(curl);
    return CURLE_OK;
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
    sprintf(nameFile, "%dh%dm%ds_%s%s",hourTime, minTime, secTime, name, ".html");
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

