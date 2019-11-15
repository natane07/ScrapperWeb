#ifndef CONST_H

#define CONST_H

#include "curl/curl.h"

//files
#define MAX_SETTING_LENGTH 256
#define MIN_SETTING_LENGTH 0
#define MAX_PATH_LENGTH MAX_PATH

//String
#define MAX_STRINGS 60
#define MAX_STRING_VALUE 1024
#define MAX_STRING (MAX_STRING_VALUE * CUT_PARAMS_AMOUNT)
#define CUT_PARAMS_AMOUNT 8

#ifdef CURL_MAX_WRITE_SIZE
#undef CURL_MAX_WRITE_SIZE
#define CURL_MAX_WRITE_SIZE 65536
#endif


#endif