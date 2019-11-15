#include <windows.h>
#include "common.h"

ActionList *makeActionList()
{
    ActionList *list = malloc(sizeof(ActionList));
    if (list == NULL)
    {
        exit(-1);
    }
    list->first = NULL;
    list->length = 0;
    return list;
}


void pushActionToList(ActionList *list, char *action, char *url)
{
    Action *new = malloc(sizeof(Action));
    if (action == NULL || url == NULL || list == NULL)
    {
        exit(-1);
    }
    strcpy(new->name, action);
    strcpy(new->url, url);
    new->option = makeOptionList();
    new->next = NULL;
    if (list->length > 0)
    {
        Action *last;
        last = getActionInList(list, list->length - 1);
        last->next = new;
    }
    else
    {
        list->first = new;
    }
    list->length++;
}

Action *getActionInList(ActionList *list, size_t index)
{
    int i;
    if (list == NULL)
    {
        exit(-1);
    }
    Action *current = list->first;
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

void removeActionInList(ActionList *list, size_t index)
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
        Action *last = getActionInList(list, list->length - 1);
        if (list->length > 1)
        {
            Action *nextToLast = getActionInList(list, list->length - 2);
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
        Action *first = list->first;
        Action *second = first->next;
        list->first = second;
        free(first);
        list->length--;
        return;
    }
    Action *previous = getActionInList(list, index - 1);
    Action *current = previous->next;
    Action *next = current->next;
    previous->next = next;
    free(current);
    list->length--;
}

void destroyActionList(ActionList *list)
{
    if (list == NULL)
    {
        exit(-1);
    }
    Action *current = list->first;
    Action *tmp = NULL;
    while (current != NULL)
    {
        destroyOptionList(current->option);
        tmp = current->next;
        free(current);
        current = tmp;
    }
    free(list);
}

void printActionList(ActionList *list)
{
    if (list == NULL)
    {
        exit(-1);
    }
    Action *current = list->first;
    puts("ActionList {");
    while (current != NULL)
    {
        puts("Action {");
        printf("name: %s\n", current->name);
        printf("url: %s\n", current->url);
        printOptionList(current->option);
        current = current->next;
        puts("}");
    }
    printf("List length: %d\n", list->length);
    puts("};");
}

void pushOptionListToAction(ActionList *list, char *optionId, char *valueOption){
    if (list == NULL)
    {
        exit(-1);
    }
    Action *current = list->first;
    while (current->next!= NULL){
        current = current->next;
    }
    pushOptionToList(current->option, optionId, valueOption);
}