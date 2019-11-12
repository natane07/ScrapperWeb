#include "common.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void curlSetDefaultOptionsHtml(CURL *curl, void *response, size_t (*callback)(char *, size_t, size_t, void *))
{
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
}

size_t curlCallbackHtml(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    HttpResponse *response = (HttpResponse *)userdata;
    size_t bytes = nmemb * size;
    size_t initialPosition = response->position;
    memcpy(response->buffer + response->position, ptr, bytes);
    response->position += bytes;
    memset(response->buffer + response->position, 0, 1);
    return strlen(response->buffer) - initialPosition;
}

int httpGetHtml(char *url, char *mimeType, void *buffer, size_t (*callback)(char *, size_t, size_t, void *))
{
    CURL *curl;
    CURLcode res;
    CURLcode resContentType;

    curl = curl_easy_init();
    if (!curl)
    {
        printf(ERR_HTTP_INIT);
        return -1;
    }
    curlSetDefaultOptionsHtml(curl, buffer, callback);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    res = curl_easy_perform(curl);
    char *ct = NULL;
    resContentType = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
    if(!resContentType && ct) {
        //printf("Content-Type: %s\n", ct);
        strcpy(mimeType, ct);
    }
    if (res != CURLE_OK)
    {
        printf(curl_easy_strerror(res));
        return res;
    }
    curl_easy_cleanup(curl);
    return CURLE_OK;
}

HttpResponse setHttpResponseBuffer(char *buffer)
{
    HttpResponse response;
    response.buffer = buffer;
    response.position = 0;
    return response;
}