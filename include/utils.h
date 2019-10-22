#ifndef UTILS_H

#define UTILS_H

#define ALPHA_NUM "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define STR_NULL "\0"

#include <windows.h>
#include "objects.h"
#include "curl/curl.h"

void remCrlf(char *);
void initMemory(char *, int);
void stringCopy(char *, char *, int);
char *setString(char *, char *);
char *resetString(char *, char *);
int isStringSafe(char *, char *);
int containsCharNTimes(char *str, char c, int amount);
int compareKey(char *, char *);
int simpleCompare(char *, char *);
void printError(const char *);
void printInfo(const char *);
int addStringToCombo(HWND, int, char *);
void addStringToComboDir(HWND, char *);
int addStringToList(HWND, int, char *);
void removeStringFromList(HWND hwnd, int controlId, int position);
int findStringIndexInCombo(HWND, int, char *);
int findStringIndexInComboDir(HWND, char *);
void setComboCursor(HWND, int, int);
void setComboCursorDir(HWND, int);
int getComboCursor(HWND, int);
int getComboCursorDir(HWND);
void destroyComboContentDir(HWND);
void destroyComboContent(HWND, int);
void sendWinText(HWND, int, char *);
void sendWinTextDir(HWND, char *);
void getStringFromCombo(HWND, int, int, char *);
void getStringFromComboDir(HWND, int, char *);
void getStringFromWin(HWND, int, char *, int);
void getStringFromWinDir(HWND, char *, int);
int getStringLengthFromWin(HWND hwnd, int controlId);
void getCurrentStringFromComboDir(HWND, char *);
void getCurrentStringFromCombo(HWND, int, char *);
void clearListBox(HWND, int);
int getRadioState(HWND);
void enableRadio(HWND);
void disableRadio(HWND);
void changeRadioState(HWND);
void setRadioState(HWND, int);
void enableEdit(HWND);
void disableEdit(HWND);
int getListCursor(HWND, int);
void createClass(WNDCLASSEX *, HINSTANCE, const char *, LRESULT(CALLBACK *)(HWND, UINT, WPARAM, LPARAM));
WinPosition getChildWindowPosition(HWND);
void moveWindowBy(HWND, int, int);
void destroyMenu(HWND *, int);
void debugAppData(AppData *appData);
void debugInfos(Infos *infos);
void freeString(char *string);
void verifyPointer(void *pointer, const char *message);
int inArray(const char* value, char **array, int arraySize);
void initArray(char *value, char **array, int arraySize);
JsonResponse setJsonResponseBuffer(char *buffer);
void curlSetDefaultOptions(CURL *curl, void *, size_t (*callback)(char *, size_t, size_t, void *));
size_t curlCallback(char *ptr, size_t size, size_t nmemb, void *userdata);
int httpGet(char *url, void *buffer, size_t (*callback)(char *, size_t, size_t, void *));
int httpPost(char *url, void *responseBuffer, char *body, size_t (*callback)(char *, size_t, size_t, void *));

#endif
