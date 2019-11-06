#include <windows.h>
#include "common.h"

TacheList *makeTacheList()
{
    TacheList *list = malloc(sizeof(TacheList));
    if (list == NULL)
    {
        exit(-1);
    }
    list->first = NULL;
    list->length = 0;
    return list;
}

void pushTacheToList(TacheList *list, char *tache, int hour, int min, int sec)
{
    Tache *new = malloc(sizeof(Tache));
    if (tache == NULL || list == NULL)
    {
        exit(-1);
    }
    strcpy(new->name, tache);
    new->hour = hour;
    new->minute = min;
    new->seconde = sec;
    new->planificateurList = makePlanificateurList();
    new->next = NULL;
    if (list->length > 0)
    {
        Tache *last;
        last = getTacheInList(list, list->length - 1);
        last->next = new;
    }
    else
    {
        list->first = new;
    }
    list->length++;
}

Tache *getTacheInList(TacheList *list, size_t index)
{
    int i;
    if (list == NULL)
    {
        exit(-1);
    }
    Tache *current = list->first;
    if (index >= list->length || index < 0)
    {
        return list->first;
    }
    for (i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current;
}

void removeTacheInList(TacheList *list, size_t index)
{
    if (list == NULL)
    {
        exit(-1);
    }
    if (index >= list->length || index < 0)
    {
        return;
    }
    if (index == list->length - 1)
    {
        Tache *last = getTacheInList(list, list->length - 1);
        if (list->length > 1)
        {
            Tache *nextToLast = getTacheInList(list, list->length - 2);
            nextToLast->next = NULL;
        }
        else
        {
            list->first = NULL;
        }
        free(last);
        list->length--;
        return;
    }
    if (index == 0)
    {
        Tache *first = list->first;
        Tache *second = first->next;
        list->first = second;
        free(first);
        list->length--;
        return;
    }
    Tache *previous = getTacheInList(list, index - 1);
    Tache *current = previous->next;
    Tache *next = current->next;
    previous->next = next;
    free(current);
    list->length--;
}

void destroyTacheList(TacheList *list)
{
    if (list == NULL)
    {
        exit(-1);
    }
    Tache *current = list->first;
    Tache *tmp = NULL;
    while (current != NULL)
    {
        tmp = current->next;
        free(current);
        current = tmp;
    }
    free(list);
}

void printTacheList(TacheList *list)
{
    if (list == NULL)
    {
        exit(-1);
    }
    Tache *current = list->first;
    puts("TacheList {");
    while (current != NULL)
    {
        puts("Tache {");
        printf("name: %s\n", current->name);
        printf("hour: %d\n", current->hour);
        printf("minute: %d\n", current->minute);
        printf("seconde: %d\n", current->seconde);
        printPlanificateurList(current->planificateurList);
        current = current->next;
        puts("}");
    }
    printf("List length: %d\n", list->length);
    puts("};");
}

void pushPlanificateurListToTache(TacheList *list, char *valuePlanificateur){
    if (list == NULL)
    {
        exit(-1);
    }
    Tache *current = list->first;
    while (current->next!= NULL){
        current = current->next;
    }
    pushPlanificateurToList(current->planificateurList, valuePlanificateur);
}