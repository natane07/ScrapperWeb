#ifndef INFO_H

#define INFO_H

#include "utils.h"

//validation rules
#define MAIL_FORMAT ALPHA_NUM"@."
#define MAIL_MAX 256
#define MAIL_MIN 3
#define MAIL_AT '@'
#define MAIL_AT_AMOUNT 1
#define MAIL_DOT '.'
#define MAIL_DOT_MIN 1
#define MAIL_DOT_MAX 2
#define ADDRESS_FORMAT ALPHA_NUM"-,() "
#define ADDRESS_MAX 256
#define ADDRESS_MIN 3
#define PHONE_FORMAT "+-0123456789() "
#define PHONE_MIN 2
#define PHONE_MAX 10
#define FNAME_FORMAT ALPHA_NUM
#define FNAME_MAX 256
#define FNAME_MIN 2
#define LNAME_FORMAT ALPHA_NUM
#define LNAME_MAX 256
#define LNAME_MIN 2
#define ZCODE_FORMAT "0123456789"
#define ZCODE_MAX 6
#define ZCODE_MIN 2
#define INFO_MAX 256
#define INFO_NUM 6

//controls
#define VIEW_INFO_CTRL_NUM 14
#define VIEW_INFO_TITLE_ID 100
#define VIEW_INFO_TITLE_MSG "Please fill your informations!"
#define VIEW_INFO_ADDRESSHINT_ID 101
#define VIEW_INFO_ADDRESSHINT_MSG "Address:"
#define VIEW_INFO_ADDRESSFIELD_ID 102
#define VIEW_INFO_ADDRESSFIELD_MSG ""
#define VIEW_INFO_MAILHINT_ID 103
#define VIEW_INFO_MAILHINT_MSG "Mail:"
#define VIEW_INFO_MAILFIELD_ID 104
#define VIEW_INFO_MAILFIELD_MSG ""
#define VIEW_INFO_PHONEHINT_ID 105
#define VIEW_INFO_PHONEHINT_MSG "Phone:"
#define VIEW_INFO_PHONEFIELD_ID 106
#define VIEW_INFO_PHONEFIELD_MSG ""
#define VIEW_INFO_FNAMEHINT_ID 107
#define VIEW_INFO_FNAMEHINT_MSG "First Name:"
#define VIEW_INFO_FNAMEFIELD_ID 108
#define VIEW_INFO_FNAMEFIELD_MSG ""
#define VIEW_INFO_LNAMEHINT_ID 109
#define VIEW_INFO_LNAMEHINT_MSG "Last Name:"
#define VIEW_INFO_LNAMEFIELD_ID 110
#define VIEW_INFO_LNAMEFIELD_MSG ""
#define VIEW_INFO_ZCODEHINT_ID 111
#define VIEW_INFO_ZCODEHINT_MSG "Zip Code:"
#define VIEW_INFO_ZCODEFIELD_ID 112
#define VIEW_INFO_ZCODEFIELD_MSG ""
#define VIEW_INFO_SAVEBTN_ID 113
#define VIEW_INFO_SAVEBTN_MSG "Save Informations"

void createInfoMenu(HWND hwnd, HWND *infoControls);
bool validateAddress(char *address, bool pError);
bool validateMail(char *mail, bool pError);
bool validatePhone(char *phone, bool pError);
bool validateFirstName(char *firstName, bool pError);
bool validateLastName(char *lastName, bool pError);
bool validateZipCode(char *zipCode, bool pError);
bool validateInfo(char *mail, char *phone, char *address, char *firstName, char *lastName, char *zipCode, bool pError);
void displayErrorOrNot(const char *error, bool pError);
bool saveInfo(HWND hwnd, AppData *appData);
void saveInfoToAppdata(Infos *infos, AppData *appData);
void setInfos(Infos *infos);
void freeInfos(Infos *infos);
void destroyInfoMenu(HWND *infoControls);

#endif