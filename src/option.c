#include <windows.h>
#include "common.h"

OptionList *makeOptionList()
{
    OptionList *list = malloc(sizeof(OptionList));
    if (list == NULL)
    {
        exit(-1);
    }
    list->first = NULL;
    list->length = 0;
    return list;
}

void pushOptionToList(OptionList *list, char *optionId, char *valueOption)
{
    Option *new = malloc(sizeof(Option));
    if (optionId == NULL || list == NULL)
    {
        exit(-1);
    }
    strcpy(new->optionId, optionId);
    strcpy(new->valueOption, valueOption);
    new->next = NULL;
    if (list->length > 0)
    {
        Option *last;
        last = getOptionInList(list, list->length - 1);
        last->next = new;
    }
    else
    {
        list->first = new;
    }
    list->length++;
}

Option *getOptionInList(OptionList *list, size_t index)
{
    int i;
    if (list == NULL)
    {
        exit(-1);
    }
    Option *current = list->first;
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

void removeOptionInList(OptionList *list, size_t index)
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
        Option *last = getOptionInList(list, list->length - 1);
        if (list->length > 1)
        {
            Option *nextToLast = getOptionInList(list, list->length - 2);
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
        Option *first = list->first;
        Option *second = first->next;
        list->first = second;
        free(first);
        list->length--;
        return;
    }
    Option *previous = getOptionInList(list, index - 1);
    Option *current = previous->next;
    Option *next = current->next;
    previous->next = next;
    free(current);
    list->length--;
}

void destroyOptionList(OptionList *list)
{
    if (list == NULL)
    {
        exit(-1);
    }
    Option *current = list->first;
    Option *tmp = NULL;
    while (current != NULL)
    {
        tmp = current->next;
        free(current);
        current = tmp;
    }
    free(list);
}

void printOptionList(OptionList *list)
{
    if (list == NULL)
    {
        exit(-1);
    }
    Option *current = list->first;
    puts("OptionList {");
    while (current != NULL)
    {
        puts("Option {");
        printf("optionId: %s\n", current->optionId);
        printf("valueOption: %d\n", current->valueOption);
        current = current->next;
        puts("}");
    }
    printf("List length: %d\n", list->length);
    puts("};");
}