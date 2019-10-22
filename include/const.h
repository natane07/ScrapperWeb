#ifndef CONST_H

#define CONST_H

#include "curl/curl.h"

//files
#define MAX_SETTING_LENGTH 256
#define MIN_SETTING_LENGTH 2
#define MAX_PATH_LENGTH MAX_PATH

//json
#define MAX_TOKENS 20480
#define MAX_ARTICLES 60
#define MAX_CODE 5
#define MAX_JSON_VALUE 1024
#define MAX_JSON_ARTICLE (MAX_JSON_VALUE * CUT_PARAMS_AMOUNT)
#define FINAL_JSON_SIZE ((MAX_JSON_ARTICLE * MAX_ARTICLES) + (INFO_NUM * INFO_MAX))
#define CUT_PARAMS_AMOUNT 8
#define JSON_ALT_TEXT "n/a"

//scan
#define URL_MAX 2084
#define BAR_MAX 17
#define AMOUNT_MAX 17

#ifdef CURL_MAX_WRITE_SIZE
#undef CURL_MAX_WRITE_SIZE
#define CURL_MAX_WRITE_SIZE 65536
#endif


#endif