#ifndef ERROR_H

#define ERROR_H

//main
#define ERR_WIN_REG "Window Registration Failed!"
#define ERR_WIN_CR "Window Creation Failed!"

//validations rules error
#define ERR_INFO_MAIL_NULL "Mail unset!"
#define ERR_INFO_MAIL_LENGTH "Mail too short or too long!"
#define ERR_INFO_MAIL_UNSAFE "Mail contains wrong characters!"
#define ERR_INFO_MAIL_LACK_AT "Mail must contain @!"
#define ERR_INFO_MAIL_LACK_DOT "Mail must contain at least one and not more than 2 dots!"
#define ERR_INFO_PHONE_NULL "Phone number unset!"
#define ERR_INFO_PHONE_LENGTH "Phone number too short or too long!"
#define ERR_INFO_PHONE_UNSAFE "Phone number contains wrong characters!"
#define ERR_INFO_ADDRESS_NULL "Address unset!"
#define ERR_INFO_ADDRESS_LENGTH "Address length too short or too long!"
#define ERR_INFO_ADDRESS_UNSAFE "Address contains wrong characters!"
#define ERR_INFO_FNAME_NULL "First Name unset!"
#define ERR_INFO_FNAME_LENGTH "First Name length too short or too long!"
#define ERR_INFO_FNAME_UNSAFE "First Name contains wrong characters!"
#define ERR_INFO_LNAME_NULL "Last Name unset!"
#define ERR_INFO_LNAME_LENGTH "Last Name length too short or too long!"
#define ERR_INFO_LNAME_UNSAFE "Last name contains wrong characters!"
#define ERR_INFO_ZCODE_NULL "Zip Code unset!"
#define ERR_INFO_ZCODE_LENGTH "Zip Code length too short or too long!"
#define ERR_INFO_ZCODE_UNSAFE "Zip Code contains wrong characters!"

//curl errors
#define ERR_HTTP_INIT "Http Request initialization failed!"
#define ERR_HTTP_PRD_404 "Product not found (likely invalid barcode)"

#endif