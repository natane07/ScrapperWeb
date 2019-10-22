#ifndef JSON_H

#define JSON_H

#include "jsmn.h"
#include "objects.h"

#define JSON_STATUS "status"
#define JSON_BRAND "brands"
#define JSON_NAME "product_name"
#define JSON_CODE "code"
#define JSON_NAME_ALT "generic_name"
#define JSON_LABEL "labels"
#define JSON_IMAGE "image_url"
#define JSON_INGREDIENTS "ingredients_text"

void createFinalJson(JsonData *jsonData, char *finalJson);
char *parseJsonArticle(const char *jsonArticle);
char *writeJsonArticle(const char *json_string, int numberOfTokens, jsmntok_t *tokens);
int jsoneq(const char *json, jsmntok_t *tok, const char *s);
void addJsonLineInResult(const char *json_string, const char *parameter, char *result, jsmntok_t token);
void getJsonTokenValueFromParsedToken(char *buffer, jsmntok_t token, const char *json_string);
void getJsonTokenValueFromRawJson(char *buffer, const char *json_string, char *cmpToken);

#endif
