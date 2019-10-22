#ifndef MENU_H

#define MENU_H

//controls
#define VIEW_MAIN_CTRL_NUM 16
#define VIEW_MAIN_WELCOME_ID 1
#define VIEW_MAIN_WELCOME_MSG "Welcome to Scannator!"
#define VIEW_MAIN_SCANBTN_ID 2
#define VIEW_MAIN_SCANBTN_MSG "Begin scanning!"
#define VIEW_MAIN_INFOTITLE_ID 3
#define VIEW_MAIN_INFOTITLE_MSG "Your Informations"
#define VIEW_MAIN_ADDRESSTXT_ID 4
#define VIEW_MAIN_ADDRESSTXT_MSG "Address:"
#define VIEW_MAIN_ADDRESSVALUE_ID 5
#define VIEW_MAIN_ADDRESSVALUE_MSG ""
#define VIEW_MAIN_MAILTXT_ID 6
#define VIEW_MAIN_MAILTXT_MSG "Mail:"
#define VIEW_MAIN_MAILVALUE_ID 7
#define VIEW_MAIN_MAILVALUE_MSG ""
#define VIEW_MAIN_PHONETXT_ID 8
#define VIEW_MAIN_PHONETXT_MSG "Phone:"
#define VIEW_MAIN_PHONEVALUE_ID 9
#define VIEW_MAIN_PHONEVALUE_MSG ""
#define VIEW_MAIN_FNAMETXT_ID 10
#define VIEW_MAIN_FNAMETXT_MSG "First Name:"
#define VIEW_MAIN_FNAMEVALUE_ID 11
#define VIEW_MAIN_FNAMEVALUE_MSG ""
#define VIEW_MAIN_LNAMETXT_ID 12
#define VIEW_MAIN_LNAMETXT_MSG "Last Name:"
#define VIEW_MAIN_LNAMEVALUE_ID 13
#define VIEW_MAIN_LNAMEVALUE_MSG ""
#define VIEW_MAIN_ZCODETXT_ID 14
#define VIEW_MAIN_ZCODETXT_MSG "Zip Code:"
#define VIEW_MAIN_ZCODEVALUE_ID 15
#define VIEW_MAIN_ZCODEVALUE_MSG ""
#define VIEW_MAIN_INFOBTN_ID 16
#define VIEW_MAIN_INFOBTN_MSG "Change Informations"

#include <windows.h>

void createMainMenu(HWND, HWND *, AppData *);
void bindAppData(HWND hwnd, HWND *mainMenuControls, AppData *appData);
void destroyMainMenu(HWND *);

#endif