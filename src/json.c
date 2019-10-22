#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void createFinalJson(JsonData *jsonData, char *finalJson)
{
    int i;
    strcpy(finalJson, "{\"user\":");
    strcat(finalJson, "{");
    sprintf(finalJson, "%s\"firstname\":\"%s\",", finalJson, jsonData->user.firstName);
    sprintf(finalJson, "%s\"lastname\":\"%s\",", finalJson, jsonData->user.lastName);
    sprintf(finalJson, "%s\"address\":\"%s\",", finalJson, jsonData->user.address);
    sprintf(finalJson, "%s\"zipcode\":\"%s\",", finalJson, jsonData->user.zipCode);
    sprintf(finalJson, "%s\"email\":\"%s\",", finalJson, jsonData->user.mail);
    sprintf(finalJson, "%s\"phone\":\"%s\"", finalJson, jsonData->user.phone);
    strcat(finalJson, "}");
    strcat(finalJson, ",\"articles\":[");
    for (i = 0; i < jsonData->jsonArticles->length; i++)
    {
        char *json_result = parseJsonArticle(getArticleInList(jsonData->jsonArticles, i)->content);
        strcat(finalJson, "{\"article\":");
        strcat(finalJson, json_result);
        free(json_result);
        strcat(finalJson, ",\"count\":");
        char count[AMOUNT_MAX];
        sprintf(count, "%d", getArticleInList(jsonData->jsonArticles, i)->amount);
        strcat(finalJson, count);
        strcat(finalJson, "}");
        if (i != jsonData->jsonArticles->length - 1)
            strcat(finalJson, ",");
    }
    strcat(finalJson, "]}");
}

char *parseJsonArticle(const char *jsonArticle)
{
    int numberOfTokens;
    jsmn_parser parser;
    jsmntok_t tokens[MAX_TOKENS];
    char *json_result = NULL;

    jsmn_init(&parser);
    numberOfTokens = jsmn_parse(&parser, jsonArticle, strlen(jsonArticle), tokens, sizeof(tokens) / sizeof(jsmntok_t));
    if (numberOfTokens < 0)
    {
        printf("Failed to parse JSON: %d\n", numberOfTokens);
        return NULL;
    }

    if (numberOfTokens < 1 || tokens[0].type != JSMN_OBJECT)
    {
        printf("Object expected\n");
        return NULL;
    }

    json_result = writeJsonArticle(jsonArticle, numberOfTokens, tokens);

    return json_result;
}

char *writeJsonArticle(const char *json_string, int numberOfTokens, jsmntok_t *tokens)
{
    int i, j;
    char *parameters[] = {JSON_CODE, JSON_NAME, JSON_NAME_ALT, JSON_LABEL, JSON_BRAND, JSON_IMAGE, JSON_STATUS, JSON_INGREDIENTS};
    char *checkedParameters[CUT_PARAMS_AMOUNT];
    char *lastComma = NULL;
    char *json_result = malloc(sizeof(char) * MAX_JSON_ARTICLE);
    verifyPointer(json_result, "Can't allocate memory for jsonResult");

    initArray("0", checkedParameters, CUT_PARAMS_AMOUNT);
    strcpy(json_result, "{");
    for (i = 1; i < numberOfTokens; i++)
    {
        for (j = 0; j < CUT_PARAMS_AMOUNT; j++)
        {
            if (jsoneq(json_string, &tokens[i], parameters[j]) == 0 && inArray(parameters[j], checkedParameters, CUT_PARAMS_AMOUNT) != 0)
            {
                addJsonLineInResult(json_string, parameters[j], json_result, tokens[i + 1]);
                checkedParameters[j] = parameters[j];
            }
        }
    }
    lastComma = strrchr(json_result, ',');
    *lastComma = '}';

    return json_result;
}

int jsoneq(const char *json, jsmntok_t *tok, const char *s)
{
    if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
        strncmp(json + tok->start, s, tok->end - tok->start) == 0)
    {
        return 0;
    }
    return -1;
}

void addJsonLineInResult(const char *json_string, const char *parameter,
                         char *result, jsmntok_t token)
{
    char value[MAX_JSON_VALUE];
    initMemory(value, MAX_JSON_VALUE);
    getJsonTokenValueFromParsedToken(value, token, json_string);
    sprintf(result, "%s\"%s\":\"%s\",", result, parameter, value);
}

void getJsonTokenValueFromParsedToken(char *buffer, jsmntok_t token, const char *json_string)
{
    sprintf(buffer, "%.*s", token.end - token.start, json_string + token.start);
}

void getJsonTokenValueFromRawJson(char *buffer, const char *json_string, char *cmpToken)
{
    int numberOfTokens;
    jsmn_parser parser;
    jsmntok_t tokens[MAX_TOKENS];
    jsmn_init(&parser);
    numberOfTokens = jsmn_parse(&parser, json_string, strlen(json_string), tokens, MAX_TOKENS);
    for (int i = 0; i < numberOfTokens; i++)
    {
        if (jsoneq(json_string, &tokens[i], cmpToken) == 0)
        {
            getJsonTokenValueFromParsedToken(buffer, tokens[i + 1], json_string);
            return;
        }
    }
}