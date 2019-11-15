#ifndef OBJECT_H

#define OBJECT_H

#include <stdbool.h>
#include <stddef.h>
#include "const.h"

typedef struct Action Action;
typedef struct Option Option;
typedef struct Tache Tache;
typedef struct Planificateur Planificateur;
typedef struct OptionList OptionList;
typedef struct ActionList ActionList;
typedef struct TacheList TacheList;
typedef struct PlanificateurList PlanificateurList;
typedef struct FileConfig FileConfig;
typedef struct ReceivedHtml HttpResponse;


struct Action
{
    char name[MAX_STRING];
    char url[MAX_STRING];
    OptionList *option;
    Action *next;
};

struct ActionList
{
    Action *first;
    size_t length;
};

struct Option
{
    char optionId[MAX_STRING];
    char valueOption[MAX_STRING];
    Option *next;
};

struct OptionList
{
    Option *first;
    size_t length;
};

struct Planificateur
{
    char nameTache[MAX_STRING];
    Planificateur *next;
};

struct PlanificateurList
{
    Planificateur *first;
    size_t length;
};

struct Tache
{
    char name[MAX_STRING];
    int hour;
    int minute;
    int seconde;
    int currentTime;
    PlanificateurList *planificateurList;
    Tache *next;
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

struct ReceivedHtml
{
    char *buffer;
    size_t position;
};

typedef enum {
    ACTION,
    OPTION,
    TACHE,
    TACHE_OPTION
}TYPE_MODE_FILE;

#endif
