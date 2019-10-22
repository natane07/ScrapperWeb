#include <windows.h>
#include "common.h"

void createMainMenu(HWND hwnd, HWND *mainMenuControls, AppData *appData)
{
    mainMenuControls[0] = CreateWindow("STATIC", VIEW_MAIN_WELCOME_MSG, STL_TEXT_CENTER, 425, 75, 600, 24, hwnd, (HMENU)VIEW_MAIN_WELCOME_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[1] = CreateWindow("BUTTON", VIEW_MAIN_SCANBTN_MSG, STL_BUTTON, 575, 150, 300, 100, hwnd, (HMENU)VIEW_MAIN_SCANBTN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[2] = CreateWindow("STATIC", VIEW_MAIN_INFOTITLE_MSG, STL_TEXT_CENTER, 425, 300, 600, 24, hwnd, (HMENU)VIEW_MAIN_INFOTITLE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[3] = CreateWindow("STATIC", VIEW_MAIN_ADDRESSTXT_MSG, STL_TEXT_CENTER, 300, 350, 100, 24, hwnd, (HMENU)VIEW_MAIN_ADDRESSTXT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[4] = CreateWindow("STATIC", VIEW_MAIN_ADDRESSVALUE_MSG, STL_TEXT_CENTER, 425, 350, 600, 24, hwnd, (HMENU)VIEW_MAIN_ADDRESSVALUE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[5] = CreateWindow("STATIC", VIEW_MAIN_MAILTXT_MSG, STL_TEXT_CENTER, 300, 400, 100, 24, hwnd, (HMENU)VIEW_MAIN_MAILTXT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[6] = CreateWindow("STATIC", VIEW_MAIN_MAILVALUE_MSG, STL_TEXT_CENTER, 425, 400, 600, 24, hwnd, (HMENU)VIEW_MAIN_MAILVALUE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[7] = CreateWindow("STATIC", VIEW_MAIN_PHONETXT_MSG, STL_TEXT_CENTER, 300, 450, 100, 24, hwnd, (HMENU)VIEW_MAIN_PHONETXT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[8] = CreateWindow("STATIC", VIEW_MAIN_PHONEVALUE_MSG, STL_TEXT_CENTER, 425, 450, 600, 24, hwnd, (HMENU)VIEW_MAIN_PHONEVALUE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[9] = CreateWindow("STATIC", VIEW_MAIN_FNAMETXT_MSG, STL_TEXT_CENTER, 300, 500, 100, 24, hwnd, (HMENU)VIEW_MAIN_FNAMETXT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[10] = CreateWindow("STATIC", VIEW_MAIN_FNAMEVALUE_MSG, STL_TEXT_CENTER, 425, 500, 600, 24, hwnd, (HMENU)VIEW_MAIN_FNAMEVALUE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[11] = CreateWindow("STATIC", VIEW_MAIN_LNAMETXT_MSG, STL_TEXT_CENTER, 300, 550, 100, 24, hwnd, (HMENU)VIEW_MAIN_LNAMETXT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[12] = CreateWindow("STATIC", VIEW_MAIN_LNAMEVALUE_MSG, STL_TEXT_CENTER, 425, 550, 600, 24, hwnd, (HMENU)VIEW_MAIN_LNAMEVALUE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[13] = CreateWindow("STATIC", VIEW_MAIN_ZCODETXT_MSG, STL_TEXT_CENTER, 300, 600, 100, 24, hwnd, (HMENU)VIEW_MAIN_ZCODETXT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[14] = CreateWindow("STATIC", VIEW_MAIN_ZCODEVALUE_MSG, STL_TEXT_CENTER, 425, 600, 600, 24, hwnd, (HMENU)VIEW_MAIN_ZCODEVALUE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[15] = CreateWindow("BUTTON", VIEW_MAIN_INFOBTN_MSG, STL_BUTTON, 575, 650, 300, 24, hwnd, (HMENU)VIEW_MAIN_INFOBTN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    bindAppData(hwnd, mainMenuControls, appData);
}

void bindAppData(HWND hwnd, HWND *mainMenuControls, AppData *appData)
{
    sendWinText(hwnd, VIEW_MAIN_ADDRESSVALUE_ID, appData->address);
    sendWinText(hwnd, VIEW_MAIN_MAILVALUE_ID, appData->mail);
    sendWinText(hwnd, VIEW_MAIN_PHONEVALUE_ID, appData->phone);
    sendWinText(hwnd, VIEW_MAIN_FNAMEVALUE_ID, appData->firstName);
    sendWinText(hwnd, VIEW_MAIN_LNAMEVALUE_ID, appData->lastName);
    sendWinText(hwnd, VIEW_MAIN_ZCODEVALUE_ID, appData->zipCode);
}

void destroyMainMenu(HWND *mainMenuControls)
{
    destroyMenu(mainMenuControls, VIEW_MAIN_CTRL_NUM);
}