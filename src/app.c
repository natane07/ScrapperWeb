#include "common.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

void initAppdata(AppData *appData)
{
    setAppData(appData);
    initFs(appData);
}

void setAppData(AppData *appData)
{
    appData->articles = makeArticleList();
    appData->address = STR_NULL;
    appData->mail = STR_NULL;
    appData->phone = STR_NULL;
    appData->firstName = STR_NULL;
    appData->lastName = STR_NULL;
    appData->zipCode = STR_NULL;
    appData->currentArticleNumber = 0;
    appData->set = false;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND mainMenuControls[VIEW_MAIN_CTRL_NUM];
    static HWND infoMenuControls[VIEW_INFO_CTRL_NUM];
    static HWND scanMenuControls[VIEW_SCAN_CTRL_NUM];
    static int currentMenu = VIEW_MAIN;
    static HMENU hMenu;
    static AppData appData;
    switch (msg)
    {
    case WM_CREATE:
        loadIcon(hwnd, APP_ICON);
        createWindowBar(hwnd, &hMenu);
        initAppdata(&appData);
        checkInfo(&appData);
        routeFirstView(hwnd, mainMenuControls, infoMenuControls, &appData, appData.set);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case EXIT_ID:
            destroy(&appData);
            PostMessage(hwnd, WM_CLOSE, 0, 0);
            break;
        case GTMENU_ID:
            EnableMenuItem(hMenu, GTMENU_ID, MF_GRAYED);
            switch (currentMenu)
            {
            case VIEW_INFO:
                destroyInfoMenu(infoMenuControls);
                break;
            case VIEW_SCAN:
                destroyScanMenu(scanMenuControls);
                break;
            }
            createMainMenu(hwnd, mainMenuControls, &appData);
            currentMenu = VIEW_MAIN;
            break;
        case VIEW_MAIN_INFOBTN_ID:
            if (currentMenu == VIEW_MAIN)
            {
                currentMenu = VIEW_INFO;
                destroyMainMenu(mainMenuControls);
                createInfoMenu(hwnd, infoMenuControls);
                EnableMenuItem(hMenu, GTMENU_ID, MF_ENABLED);
            }
            break;
        case VIEW_MAIN_SCANBTN_ID:
            if (currentMenu == VIEW_MAIN)
            {
                currentMenu = VIEW_SCAN;
                destroyMainMenu(mainMenuControls);
                createScanMenu(hwnd, scanMenuControls);
                EnableMenuItem(hMenu, GTMENU_ID, MF_ENABLED);
            }
            break;
        case VIEW_INFO_SAVEBTN_ID:
        {
            bool ok = saveInfo(hwnd, &appData);
            if (ok)
            {
                EnableMenuItem(hMenu, GTMENU_ID, MF_GRAYED);
                destroyInfoMenu(infoMenuControls);
                createMainMenu(hwnd, mainMenuControls, &appData);
            }
            break;
        }
        case VIEW_SCAN_ARTICLE_LIST_ID:
        {
            if (HIWORD(wParam) == LBN_SELCHANGE)
            {
                appData.currentArticleNumber = getArticleListCursor(hwnd);
                Article *selected = getArticleInList(appData.articles, appData.currentArticleNumber);
                bindArticle(hwnd, selected->content, selected->amount);
            }
            break;
        }
        case VIEW_SCAN_ADD_ARTICLE_BTN_ID:
            if (appData.articles->length < 60)
            {
                addArticle(hwnd, &appData);
            }
            break;
        case VIEW_SCAN_PRD_AMOUNT_UPDATE_BTN_ID:
            updateArticleAmount(hwnd, &appData);
            break;
        case VIEW_SCAN_PRD_DELETE_BTN_ID:
            removeArticle(hwnd, &appData);
            break;
        case VIEW_SCAN_PUSH_BTN_ID:
            submitArticles(&appData);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void loadIcon(HWND hwnd, const char *icon)
{
    HICON hIcon, hIconSm;
    hIcon = (HICON)LoadImage(NULL, icon, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
    if (hIcon)
    {
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    }
    hIconSm = (HICON)LoadImage(NULL, icon, IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
    if (hIconSm)
    {
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
    }
}

void createWindowBar(HWND hwnd, HMENU *hMenu)
{
    HMENU hSubMenu;
    *hMenu = CreateMenu();
    hSubMenu = CreatePopupMenu();
    AppendMenu(*hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "Menu");
    AppendMenu(hSubMenu, MF_STRING, GTMENU_ID, GTMENU_MSG);
    EnableMenuItem(*hMenu, GTMENU_ID, MF_GRAYED);
    AppendMenu(hSubMenu, MF_STRING, EXIT_ID, EXIT_MSG);
    SetMenu(hwnd, *hMenu);
}

void checkInfo(AppData *appData)
{
    if (validateInfo(appData->mail, appData->phone, appData->address, appData->firstName, appData->lastName, appData->zipCode, false))
    {
        appData->set = true;
    }
}

void routeFirstView(HWND hwnd, HWND *mainMenuControls, HWND *infoMenuControls, AppData *appData, bool set)
{
    if (set)
    {
        createMainMenu(hwnd, mainMenuControls, appData);
    }
    else
    {
        createInfoMenu(hwnd, infoMenuControls);
    }
}

void destroy(AppData *appData)
{
    freeAppdata(appData);
    curl_global_cleanup();
}

void freeAppdata(AppData *appData)
{
    destroyArticleList(appData->articles);
    freeString(appData->address);
    freeString(appData->mail);
    freeString(appData->phone);
    freeString(appData->zipCode);
    freeString(appData->firstName);
    freeString(appData->lastName);
}