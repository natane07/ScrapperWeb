#ifndef HTTP_SCRAPPER_H

#define HTTP_SCRAPPER_H

#include <windows.h>
#include "objects.h"
#include "curl/curl.h"

size_t curlCallbackHtml(char *ptr, size_t size, size_t nmemb, void *userdata);
int httpGetHtml(char *url, void *buffer, size_t (*callback)(char *, size_t, size_t, void *));
void curlSetDefaultOptionsHtml(CURL *curl, void *, size_t (*callback)(char *, size_t, size_t, void *));
HttpResponse setHttpResponseBuffer(char *buffer);

#endif
