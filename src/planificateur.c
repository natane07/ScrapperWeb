#include <windows.h>
#include "common.h"

PlanificateurList *makePlanificateurList()
{
    PlanificateurList *list = malloc(sizeof(PlanificateurList));
    if (list == NULL)
    {
        exit(-1);
    }
    list->first = NULL;
    list->length = 0;
    return list;
}

void pushPlanificateurToList(PlanificateurList *list, char *nameTache)
{
    Planificateur *new = malloc(sizeof(Planificateur));
    if (nameTache == NULL || list == NULL)
    {
        exit(-1);
    }
    strcpy(new->nameTache, nameTache);
    new->next = NULL;
    if (list->length > 0)
    {
        Planificateur *last;
        last = getPlanificateurInList(list, list->length - 1);
        last->next = new;
    }
    else
    {
        list->first = new;
    }
    list->length++;
}

Planificateur *getPlanificateurInList(PlanificateurList *list, size_t index)
{
    int i;
    if (list == NULL)
    {
        exit(-1);
    }
    Planificateur *current = list->first;
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

void removePlanificateurInList(PlanificateurList *list, size_t index)
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
        Planificateur *last = getPlanificateurInList(list, list->length - 1);
        if (list->length > 1)
        {
            Planificateur *nextToLast = getPlanificateurInList(list, list->length - 2);
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
        Planificateur *first = list->first;
        Planificateur *second = first->next;
        list->first = second;
        free(first);
        list->length--;
        return;
    }
    Planificateur *previous = getPlanificateurInList(list, index - 1);
    Planificateur *current = previous->next;
    Planificateur *next = current->next;
    previous->next = next;
    free(current);
    list->length--;
}

void destroyPlanificateurList(PlanificateurList *list)
{
    if (list == NULL)
    {
        exit(-1);
    }
    Planificateur *current = list->first;
    Planificateur *tmp = NULL;
    while (current != NULL)
    {
        tmp = current->next;
        free(current);
        current = tmp;
    }
    free(list);
}

void printPlanificateurList(PlanificateurList *list)
{
    if (list == NULL)
    {
        exit(-1);
    }
    Planificateur *current = list->first;
    puts("PlanificateurList {");
    while (current != NULL)
    {
        puts("Planificateur {");
        printf("value: %s\n", current->nameTache);
        current = current->next;
        puts("}");
    }
    printf("List length: %d\n", list->length);
    puts("};");
}