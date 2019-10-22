#include <windows.h>
#include "common.h"

void createInfoMenu(HWND hwnd, HWND *infoControls)
{
    infoControls[0] = CreateWindow("STATIC", VIEW_INFO_TITLE_MSG, STL_TEXT_CENTER, 425, 75, 600, 24, hwnd, (HMENU)VIEW_INFO_TITLE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    infoControls[1] = CreateWindow("STATIC", VIEW_INFO_ADDRESSHINT_MSG, STL_TEXT_CENTER, 300, 200, 100, 24, hwnd, (HMENU)VIEW_INFO_ADDRESSHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    infoControls[2] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", VIEW_INFO_ADDRESSFIELD_MSG, STL_EDIT, 425, 200, 600, 24, hwnd, (HMENU)VIEW_INFO_ADDRESSFIELD_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    infoControls[3] = CreateWindow("STATIC", VIEW_INFO_MAILHINT_MSG, STL_TEXT_CENTER, 300, 250, 100, 24, hwnd, (HMENU)VIEW_INFO_MAILHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    infoControls[4] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", VIEW_INFO_MAILFIELD_MSG, STL_EDIT, 425, 250, 600, 24, hwnd, (HMENU)VIEW_INFO_MAILFIELD_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    infoControls[5] = CreateWindow("STATIC", VIEW_INFO_PHONEHINT_MSG, STL_TEXT_CENTER, 300, 300, 100, 24, hwnd, (HMENU)VIEW_INFO_PHONEHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    infoControls[6] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", VIEW_INFO_PHONEFIELD_MSG, STL_EDIT, 425, 300, 600, 24, hwnd, (HMENU)VIEW_INFO_PHONEFIELD_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    infoControls[7] = CreateWindow("STATIC", VIEW_INFO_FNAMEHINT_MSG, STL_TEXT_CENTER, 300, 350, 100, 24, hwnd, (HMENU)VIEW_INFO_FNAMEHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    infoControls[8] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", VIEW_INFO_FNAMEFIELD_MSG, STL_EDIT, 425, 350, 600, 24, hwnd, (HMENU)VIEW_INFO_FNAMEFIELD_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    infoControls[9] = CreateWindow("STATIC", VIEW_INFO_LNAMEHINT_MSG, STL_TEXT_CENTER, 300, 400, 100, 24, hwnd, (HMENU)VIEW_INFO_LNAMEHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    infoControls[10] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", VIEW_INFO_LNAMEFIELD_MSG, STL_EDIT, 425, 400, 600, 24, hwnd, (HMENU)VIEW_INFO_LNAMEFIELD_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    infoControls[11] = CreateWindow("STATIC", VIEW_INFO_ZCODEHINT_MSG, STL_TEXT_CENTER, 300, 450, 100, 24, hwnd, (HMENU)VIEW_INFO_ZCODEHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    infoControls[12] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", VIEW_INFO_ZCODEFIELD_MSG, STL_EDIT, 425, 450, 600, 24, hwnd, (HMENU)VIEW_INFO_ZCODEFIELD_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    infoControls[13] = CreateWindow("BUTTON", VIEW_INFO_SAVEBTN_MSG, STL_BUTTON, 575, 600, 300, 24, hwnd, (HMENU)VIEW_INFO_SAVEBTN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
}

bool validateAddress(char *address, bool pError)
{
    if (address == NULL)
    {
        displayErrorOrNot(ERR_INFO_ADDRESS_NULL, pError);
        return false;
    }

    if (!isStringSafe(address, ADDRESS_FORMAT))
    {
        displayErrorOrNot(ERR_INFO_ADDRESS_UNSAFE, pError);
        return false;
    }

    if (strlen(address) > ADDRESS_MAX || strlen(address) < ADDRESS_MIN)
    {
        displayErrorOrNot(ERR_INFO_ADDRESS_LENGTH, pError);
        return false;
    }

    return true;
}

bool validateMail(char *mail, bool pError)
{
    if (mail == NULL)
    {
        displayErrorOrNot(ERR_INFO_MAIL_NULL, pError);
        return false;
    }

    if (!isStringSafe(mail, MAIL_FORMAT))
    {
        displayErrorOrNot(ERR_INFO_MAIL_UNSAFE, pError);
        return false;
    }

    if (strlen(mail) > MAIL_MAX || strlen(mail) < MAIL_MIN)
    {
        displayErrorOrNot(ERR_INFO_MAIL_LENGTH, pError);
        return false;
    }

    if (!containsCharNTimes(mail, MAIL_AT, 1))
    {
        displayErrorOrNot(ERR_INFO_MAIL_LACK_AT, pError);
        return false;
    }

    if (!containsCharNTimes(mail, MAIL_DOT, 1) && !containsCharNTimes(mail, MAIL_DOT, 2))
    {
        displayErrorOrNot(ERR_INFO_MAIL_LACK_DOT, pError);
        return false;
    }

    return true;
}

bool validatePhone(char *phone, bool pError)
{
    if (phone == NULL)
    {
        displayErrorOrNot(ERR_INFO_PHONE_NULL, pError);
        return false;
    }

    if (!isStringSafe(phone, PHONE_FORMAT))
    {
        displayErrorOrNot(ERR_INFO_PHONE_UNSAFE, pError);
        return false;
    }

    if (strlen(phone) > PHONE_MAX || strlen(phone) < PHONE_MIN)
    {
        displayErrorOrNot(ERR_INFO_PHONE_LENGTH, pError);
        return false;
    }

    return true;
}

bool validateFirstName(char *firstName, bool pError)
{
    if (firstName == NULL)
    {
        displayErrorOrNot(ERR_INFO_FNAME_NULL, pError);
        return false;
    }

    if (!isStringSafe(firstName, FNAME_FORMAT))
    {
        displayErrorOrNot(ERR_INFO_FNAME_UNSAFE, pError);
        return false;
    }

    if (strlen(firstName) > FNAME_MAX || strlen(firstName) < FNAME_MIN)
    {
        displayErrorOrNot(ERR_INFO_FNAME_LENGTH, pError);
        return false;
    }

    return true;
}

bool validateLastName(char *lastName, bool pError)
{
    if (lastName == NULL)
    {
        displayErrorOrNot(ERR_INFO_LNAME_NULL, pError);
        return false;
    }

    if (!isStringSafe(lastName, LNAME_FORMAT))
    {
        displayErrorOrNot(ERR_INFO_LNAME_UNSAFE, pError);
        return false;
    }

    if (strlen(lastName) > LNAME_MAX || strlen(lastName) < LNAME_MIN)
    {
        displayErrorOrNot(ERR_INFO_LNAME_LENGTH, pError);
        return false;
    }

    return true;
}

bool validateZipCode(char *zipCode, bool pError)
{
    if (zipCode == NULL)
    {
        displayErrorOrNot(ERR_INFO_ZCODE_NULL, pError);
        return false;
    }

    if (!isStringSafe(zipCode, ZCODE_FORMAT))
    {
        displayErrorOrNot(ERR_INFO_ZCODE_UNSAFE, pError);
        return false;
    }

    if (strlen(zipCode) > ZCODE_MAX || strlen(zipCode) < ZCODE_MIN)
    {
        displayErrorOrNot(ERR_INFO_ZCODE_LENGTH, pError);
        return false;
    }

    return true;
}

bool validateInfo(char *mail, char *phone, char *address, char *firstName, char *lastName, char *zipCode, bool pError)
{
    if (validatePhone(phone, pError) && validateAddress(address, pError) && validateMail(mail, pError) &&
        validateFirstName(firstName, pError) && validateLastName(lastName, pError) && validateZipCode(zipCode, pError))
    {
        return true;
    }
    return false;
}

void displayErrorOrNot(const char *error, bool pError)
{
    if (pError)
    {
        printError(error);
    }
}

bool saveInfo(HWND hwnd, AppData *appData)
{
    Infos infos;
    char buffer[INFO_MAX];
    setInfos(&infos);
    getStringFromWin(hwnd, VIEW_INFO_ADDRESSFIELD_ID, buffer, INFO_MAX);
    infos.address = setString(infos.address, buffer);
    getStringFromWin(hwnd, VIEW_INFO_MAILFIELD_ID, buffer, INFO_MAX);
    infos.mail = setString(infos.mail, buffer);
    getStringFromWin(hwnd, VIEW_INFO_PHONEFIELD_ID, buffer, INFO_MAX);
    infos.phone = setString(infos.phone, buffer);
    getStringFromWin(hwnd, VIEW_INFO_FNAMEFIELD_ID, buffer, INFO_MAX);
    infos.firstName = setString(infos.firstName, buffer);
    getStringFromWin(hwnd, VIEW_INFO_LNAMEFIELD_ID, buffer, INFO_MAX);
    infos.lastName = setString(infos.lastName, buffer);
    getStringFromWin(hwnd, VIEW_INFO_ZCODEFIELD_ID, buffer, INFO_MAX);
    infos.zipCode = setString(infos.zipCode, buffer);
    if (validateInfo(infos.mail, infos.phone, infos.address, infos.firstName, infos.lastName, infos.zipCode, true))
    {
        saveInfoToAppdata(&infos, appData);
        saveConfigToFile(appData);
        freeInfos(&infos);
        return true;
    }
    return false;
}

void saveInfoToAppdata(Infos *infos, AppData *appData)
{
    freeAppdata(appData);
    appData->address = setString(appData->address, infos->address);
    appData->mail = setString(appData->mail, infos->mail);
    appData->phone = setString(appData->phone, infos->phone);
    appData->firstName = setString(appData->firstName, infos->firstName);
    appData->lastName = setString(appData->lastName, infos->lastName);
    appData->zipCode = setString(appData->zipCode, infos->zipCode);
}

void setInfos(Infos *infos)
{
    infos->address = STR_NULL;
    infos->firstName = STR_NULL;
    infos->mail = STR_NULL;
    infos->lastName = STR_NULL;
    infos->phone = STR_NULL;
    infos->zipCode = STR_NULL;
}

void freeInfos(Infos *infos)
{
    free(infos->address);
    free(infos->mail);
    free(infos->phone);
    free(infos->firstName);
    free(infos->lastName);
    free(infos->zipCode);
}

void destroyInfoMenu(HWND *infoControls)
{
    destroyMenu(infoControls, VIEW_INFO_CTRL_NUM);
}