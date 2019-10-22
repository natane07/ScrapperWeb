#ifndef SCAN_H

#define SCAN_H

#include <windows.h>
#include "objects.h"

//api
#define API_URL "https://ssl-api.openfoodfacts.org/api/v0/product/"
#define POST_URL "http://api.ffw-mission.org/register/donateur"

//controls
#define VIEW_SCAN_CTRL_NUM 16
#define VIEW_SCAN_ARTICLE_LIST_ID 200
#define VIEW_SCAN_ARTICLE_LIST_MSG ""
#define VIEW_SCAN_ADD_ARTICLE_HINT_ID 201
#define VIEW_SCAN_ADD_ARTICLE_HINT_MSG "Enter Barcode:"
#define VIEW_SCAN_ADD_ARTICLE_EDIT_ID 202
#define VIEW_SCAN_ADD_ARTICLE_EDIT_MSG ""
#define VIEW_SCAN_ADD_ARTICLE_BTN_ID 203
#define VIEW_SCAN_ADD_ARTICLE_BTN_MSG "Add Product"
#define VIEW_SCAN_PRD_INFO_TITLE_ID 204
#define VIEW_SCAN_PRD_INFO_TITLE_MSG "Product Informations:"
#define VIEW_SCAN_PRD_NAME_HINT_ID 205
#define VIEW_SCAN_PRD_NAME_HINT_MSG "Name:"
#define VIEW_SCAN_PRD_NAME_VALUE_ID 206
#define VIEW_SCAN_PRD_NAME_VALUE_MSG JSON_ALT_TEXT
#define VIEW_SCAN_PRD_LABEL_HINT_ID 207
#define VIEW_SCAN_PRD_LABEL_HINT_MSG "Label:"
#define VIEW_SCAN_PRD_LABEL_VALUE_ID 208
#define VIEW_SCAN_PRD_LABEL_VALUE_MSG JSON_ALT_TEXT
#define VIEW_SCAN_PRD_BRAND_HINT_ID 209
#define VIEW_SCAN_PRD_BRAND_HINT_MSG "Brand:"
#define VIEW_SCAN_PRD_BRAND_VALUE_ID 210
#define VIEW_SCAN_PRD_BRAND_VALUE_MSG JSON_ALT_TEXT
#define VIEW_SCAN_PRD_AMOUNT_HINT_ID 211
#define VIEW_SCAN_PRD_AMOUNT_HINT_MSG "Amount:"
#define VIEW_SCAN_PRD_AMOUNT_VALUE_ID 212
#define VIEW_SCAN_PRD_AMOUNT_VALUE_MSG ""
#define VIEW_SCAN_PRD_AMOUNT_UPDATE_BTN_ID 213
#define VIEW_SCAN_PRD_AMOUNT_UPDATE_BTN_MSG "Update Amount"
#define VIEW_SCAN_PRD_DELETE_BTN_ID 214
#define VIEW_SCAN_PRD_DELETE_BTN_MSG "Delete Product"
#define VIEW_SCAN_PUSH_BTN_ID 215
#define VIEW_SCAN_PUSH_BTN_MSG "Submit Articles"

void createScanMenu(HWND hwnd, HWND *scanMenuControls);
void addArticle(HWND hwnd, AppData *);
void updateArticleAmount(HWND hwnd, AppData *appData);
void bindArticle(HWND hwnd, char *json_string, int productAmount);
void loadDefaultArticle(HWND hwnd);
void removeArticle(HWND hwnd, AppData *appData);
void fillEmptyFields(HWND hwnd);
void addArticleToListbox(HWND hwnd, char *article);
int getArticleListCursor(HWND hwnd);
void appDataToJsonData(JsonData *jsonData, AppData *appData);
void submitArticles(AppData *appData);
void destroyScanMenu(HWND *infoControls);

#endif