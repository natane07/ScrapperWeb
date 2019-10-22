#ifndef OBJECT_H

#define OBJECT_H

#include <stdbool.h>
#include <stddef.h>
#include "const.h"

typedef struct ArticleList ArticleList;
typedef struct Article Article;
typedef struct AppData AppData;
typedef struct WinPosition WinPosition;
typedef struct JsonData JsonData;
typedef struct ReceivedJson JsonResponse;
typedef struct Infos Infos;

typedef struct Action Action;
typedef struct Option Option;
typedef struct Tache Tache;
typedef struct OptionList OptionList;
typedef struct ActionList ActionList;
typedef struct TacheList TacheList;


struct Action
{
    char name[MAX_JSON_ARTICLE];
    char url[MAX_JSON_ARTICLE];
    OptionList *option;
};

struct ActionList
{
    Action *first;
    size_t length;
};

struct Option
{
    char optionId[MAX_JSON_ARTICLE];
    char valueOption[MAX_JSON_ARTICLE];
    Option *next;
};

struct OptionList
{
    Option *first;
    size_t length;
};

struct Tache
{
    char name[MAX_JSON_ARTICLE];
    int hour;
    int minute;
    int seconde;
};

struct TacheList
{
    Tache *first;
    size_t length;
};

struct FileConfig
{
    ActionList *actions;
    TacheList *taches;
};

//---------

struct AppData
{
    char *phone;
    char *mail;
    char *address;
    char *firstName;
    char *lastName;
    char *zipCode;
    ArticleList *articles;
    size_t currentArticleNumber;
    bool set;
};

struct WinPosition
{
    long x;
    long y;
    long width;
    long height;
};

struct Infos
{
    char *phone;
    char *mail;
    char *address;
    char *lastName;
    char *firstName;
    char *zipCode;
};

struct Article
{
    char content[MAX_JSON_ARTICLE];
    int amount;
    Article *next;
};

struct ArticleList
{
    Article *first;
    size_t length;
};

struct JsonData
{
    ArticleList *jsonArticles;
    Infos user;
};

struct ReceivedJson
{
    char *buffer;
    size_t position;
};

#endif
