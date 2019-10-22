#include <windows.h>
#include "common.h"

void createScanMenu(HWND hwnd, HWND *scanMenuControls)
{
    scanMenuControls[0] = CreateWindowEx(WS_EX_CLIENTEDGE, "LISTBOX", VIEW_SCAN_ARTICLE_LIST_MSG, STL_LIST, 30, 30, 400, 400, hwnd, (HMENU)VIEW_SCAN_ARTICLE_LIST_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    scanMenuControls[1] = CreateWindow("STATIC", VIEW_SCAN_ADD_ARTICLE_HINT_MSG, STL_TEXT_CENTER, 690, 30, 100, 24, hwnd, (HMENU)VIEW_SCAN_ADD_ARTICLE_HINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    scanMenuControls[2] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", VIEW_SCAN_ADD_ARTICLE_EDIT_MSG, STL_EDIT, 830, 30, 150, 24, hwnd, (HMENU)VIEW_SCAN_ADD_ARTICLE_EDIT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    scanMenuControls[3] = CreateWindow("BUTTON", VIEW_SCAN_ADD_ARTICLE_BTN_MSG, STL_BUTTON, 1000, 30, 150, 24, hwnd, (HMENU)VIEW_SCAN_ADD_ARTICLE_BTN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    scanMenuControls[4] = CreateWindow("STATIC", VIEW_SCAN_PRD_INFO_TITLE_MSG, STL_TEXT, 500, 100, 300, 24, hwnd, (HMENU)VIEW_SCAN_PRD_INFO_TITLE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    scanMenuControls[5] = CreateWindow("STATIC", VIEW_SCAN_PRD_NAME_HINT_MSG, STL_TEXT, 500, 150, 100, 24, hwnd, (HMENU)VIEW_SCAN_PRD_NAME_HINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    scanMenuControls[6] = CreateWindow("STATIC", VIEW_SCAN_PRD_NAME_VALUE_MSG, STL_TEXT, 650, 150, 600, 24, hwnd, (HMENU)VIEW_SCAN_PRD_NAME_VALUE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    scanMenuControls[7] = CreateWindow("STATIC", VIEW_SCAN_PRD_LABEL_HINT_MSG, STL_TEXT, 500, 200, 100, 24, hwnd, (HMENU)VIEW_SCAN_PRD_LABEL_HINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    scanMenuControls[8] = CreateWindowA("STATIC", VIEW_SCAN_PRD_LABEL_VALUE_MSG, STL_TEXT, 650, 200, 600, 24, hwnd, (HMENU)VIEW_SCAN_PRD_LABEL_VALUE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    scanMenuControls[9] = CreateWindow("STATIC", VIEW_SCAN_PRD_BRAND_HINT_MSG, STL_TEXT, 500, 250, 100, 24, hwnd, (HMENU)VIEW_SCAN_PRD_BRAND_HINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    scanMenuControls[10] = CreateWindow("STATIC", VIEW_SCAN_PRD_BRAND_VALUE_MSG, STL_TEXT, 650, 250, 600, 24, hwnd, (HMENU)VIEW_SCAN_PRD_BRAND_VALUE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    scanMenuControls[11] = CreateWindow("STATIC", VIEW_SCAN_PRD_AMOUNT_HINT_MSG, STL_TEXT, 500, 300, 100, 24, hwnd, (HMENU)VIEW_SCAN_PRD_AMOUNT_HINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    scanMenuControls[12] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", VIEW_SCAN_PRD_AMOUNT_VALUE_MSG, STL_EDIT, 650, 300, 100, 24, hwnd, (HMENU)VIEW_SCAN_PRD_AMOUNT_VALUE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    scanMenuControls[13] = CreateWindow("BUTTON", VIEW_SCAN_PRD_AMOUNT_UPDATE_BTN_MSG, STL_BUTTON, 500, 350, 150, 24, hwnd, (HMENU)VIEW_SCAN_PRD_AMOUNT_UPDATE_BTN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    scanMenuControls[14] = CreateWindow("BUTTON", VIEW_SCAN_PRD_DELETE_BTN_MSG, STL_BUTTON, 700, 350, 150, 24, hwnd, (HMENU)VIEW_SCAN_PRD_DELETE_BTN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    scanMenuControls[15] = CreateWindow("BUTTON", VIEW_SCAN_PUSH_BTN_MSG, STL_BUTTON, 30, 480, 150, 24, hwnd, (HMENU)VIEW_SCAN_PUSH_BTN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
}

void addArticle(HWND hwnd, AppData *appData)
{
    char status[MAX_CODE];
    char barCode[BAR_MAX];
    char url[URL_MAX];
    char buffer[CURL_MAX_WRITE_SIZE];
    char article[MAX_JSON_ARTICLE];
    JsonResponse response = setJsonResponseBuffer(buffer);
    strcpy(url, API_URL);
    getStringFromWin(hwnd, VIEW_SCAN_ADD_ARTICLE_EDIT_ID, barCode, BAR_MAX);
    strcat(url, barCode);
    int code = httpGet(url, (void *)&response, curlCallback);
    if (!code)
    {
        char *temp = parseJsonArticle(buffer);
        strcpy(article, temp);
        free(temp);
        getJsonTokenValueFromRawJson(status, article, JSON_STATUS);
        if (strcmp(status, "1") == 0)
        {
            bindArticle(hwnd, article, 1);
            pushArticleToList(appData->articles, article);
            sendWinText(hwnd, VIEW_SCAN_ADD_ARTICLE_EDIT_ID, "");
            addArticleToListbox(hwnd, article);
        }
        else
        {
            printError(ERR_HTTP_PRD_404);
        }
    }
}

void updateArticleAmount(HWND hwnd, AppData *appData)
{
    char buffer[AMOUNT_MAX];
    getStringFromWin(hwnd, VIEW_SCAN_PRD_AMOUNT_VALUE_ID, buffer, AMOUNT_MAX);
    Article *current = getArticleInList(appData->articles, appData->currentArticleNumber);
    current->amount = atoi(buffer);
}

void bindArticle(HWND hwnd, char *json_string, int productAmount)
{
    char buffer[MAX_JSON_VALUE];
    initMemory(buffer, MAX_JSON_VALUE);
    getJsonTokenValueFromRawJson(buffer, json_string, JSON_BRAND);
    sendWinText(hwnd, VIEW_SCAN_PRD_BRAND_VALUE_ID, buffer);
    getJsonTokenValueFromRawJson(buffer, json_string, JSON_NAME);
    sendWinText(hwnd, VIEW_SCAN_PRD_NAME_VALUE_ID, buffer);
    getJsonTokenValueFromRawJson(buffer, json_string, JSON_LABEL);
    sendWinText(hwnd, VIEW_SCAN_PRD_LABEL_VALUE_ID, buffer);
    fillEmptyFields(hwnd);
    sprintf(buffer, "%d", productAmount);
    sendWinText(hwnd, VIEW_SCAN_PRD_AMOUNT_VALUE_ID, buffer);
}

void loadDefaultArticle(HWND hwnd)
{
    sendWinText(hwnd, VIEW_SCAN_PRD_BRAND_VALUE_ID, "");
    sendWinText(hwnd, VIEW_SCAN_PRD_NAME_VALUE_ID, "");
    sendWinText(hwnd, VIEW_SCAN_PRD_LABEL_VALUE_ID, "");
    fillEmptyFields(hwnd);
    sendWinText(hwnd, VIEW_SCAN_PRD_AMOUNT_VALUE_ID, "");
}

void removeArticle(HWND hwnd, AppData *appData)
{
    removeArticleInList(appData->articles, appData->currentArticleNumber);
    removeStringFromList(hwnd, VIEW_SCAN_ARTICLE_LIST_ID, appData->currentArticleNumber);
    if (appData->currentArticleNumber > 0)
    {
        appData->currentArticleNumber--;
        Article *current = getArticleInList(appData->articles, appData->currentArticleNumber);
        bindArticle(hwnd, current->content, current->amount);
        return;
    }
    loadDefaultArticle(hwnd);
}

void fillEmptyFields(HWND hwnd)
{
    if (getStringLengthFromWin(hwnd, VIEW_SCAN_PRD_BRAND_VALUE_ID) == 0)
    {
        sendWinText(hwnd, VIEW_SCAN_PRD_BRAND_VALUE_ID, JSON_ALT_TEXT);
    }
    if (getStringLengthFromWin(hwnd, VIEW_SCAN_PRD_NAME_VALUE_ID) == 0)
    {
        sendWinText(hwnd, VIEW_SCAN_PRD_NAME_VALUE_ID, JSON_ALT_TEXT);
    }
    if (getStringLengthFromWin(hwnd, VIEW_SCAN_PRD_LABEL_VALUE_ID) == 0)
    {
        sendWinText(hwnd, VIEW_SCAN_PRD_LABEL_VALUE_ID, JSON_ALT_TEXT);
    }
}

void addArticleToListbox(HWND hwnd, char *article)
{
    char buffer[MAX_JSON_VALUE];
    getJsonTokenValueFromRawJson(buffer, article, JSON_NAME);
    addStringToList(hwnd, VIEW_SCAN_ARTICLE_LIST_ID, buffer);
}

int getArticleListCursor(HWND hwnd)
{
    return getListCursor(hwnd, VIEW_SCAN_ARTICLE_LIST_ID);
}

void appDataToJsonData(JsonData *jsonData, AppData *appData)
{
    jsonData->jsonArticles = appData->articles;
    jsonData->user.address = appData->address;
    jsonData->user.firstName = appData->firstName;
    jsonData->user.lastName = appData->lastName;
    jsonData->user.mail = appData->mail;
    jsonData->user.phone = appData->phone;
    jsonData->user.zipCode = appData->zipCode;
}

void submitArticles(AppData *appData)
{
    char buffer[CURL_MAX_WRITE_SIZE];
    char finalJson[FINAL_JSON_SIZE];
    char url[URL_MAX];
    JsonData jsonData;
    JsonResponse response = setJsonResponseBuffer(buffer);
    strcpy(url, POST_URL);
    appDataToJsonData(&jsonData, appData);
    createFinalJson(&jsonData, finalJson);
    int code = httpPost(url, (void *)&response, finalJson, curlCallback);
    if (!code)
    {
        printInfo(FINAL_MSG);
        PostQuitMessage(0);
    }
}

void destroyScanMenu(HWND *scanMenuControls)
{
    destroyMenu(scanMenuControls, VIEW_SCAN_CTRL_NUM);
}