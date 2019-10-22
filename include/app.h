#ifndef APP_H

#define APP_H

#include <windows.h>
#include "objects.h"

#define APP_NAME "Scannator"
#define APP_ICON ".\\..\\ico\\logo.ico"
#define MAINWIN_CLASS "WinClass"
#define DEF_SCREEN_WIDTH 1920
#define DEF_SCREEN_HEIGHT 1080
#define FINAL_MSG "Thanks for submitting your products!"

//views
#define VIEW_MAIN -1
#define VIEW_INFO 0
#define VIEW_SCAN 1

//hmenu
#define EXIT_ID 1000
#define EXIT_MSG "Exit"
#define GTMENU_ID 1001
#define GTMENU_MSG "Go to Menu"

void initAppdata(AppData *);
void setAppData(AppData *);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void loadIcon(HWND, const char *);
void createWindowBar(HWND, HMENU *);
void checkInfo(AppData *appData);
void routeFirstView(HWND hwnd, HWND *mainMenuControls, HWND *infoMenuControls, AppData *, bool set);
void destroy(AppData *);
void freeAppdata(AppData *appData);

#endif