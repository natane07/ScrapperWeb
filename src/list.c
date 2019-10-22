#include "common.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List *listInit()
{
    List *list = malloc(sizeof(List));
    if (list == NULL)
    {
        exit(-1);
    }
    list->first = NULL;
    list->length = 0;
    return list;
}

void push(List *list, char *content)
{
    Element *new = malloc(sizeof(Element));
    if (list == NULL || new == NULL)
    {
        exit(-1);
    }
    new->content = malloc((strlen(content) + 1) * sizeof(char));
    if (new->content == NULL)
    {
        exit(-1);
    }
    strcpy(new->content, content);
    new->next = NULL;
    if (list->length > 0)
    {
        Element *last;
        last = getElement(list, list->length - 1);
        last->next = new;
    }
    else
    {
        list->first = new;
    }
    list->length++;
}

void unshift(List *list, char *content)
{
    Element *new = malloc(sizeof(Element));
    if (list == NULL || new == NULL)
    {
        exit(-1);
    }

    if (list->length > 0)
    {
        Element *first;
        first = getElement(list, 0);
        new->next = first;
    }
    else
    {
        new->next = NULL;
    }
    new->content = malloc((strlen(content) + 1) * sizeof(char));
    if (new->content == NULL)
    {
        exit(-1);
    }
    strcpy(new->content, content);
    list->first = new;
    list->length++;
}

void pop(List *list)
{
    Element *last;
    char *content;
    if (list == NULL || list->length <= 0)
    {
        exit(-1);
    }
    last = getElement(list, list->length - 1);
    if (list->length > 1)
    {
        Element *nextToLast;
        nextToLast = getElement(list, list->length - 2);
        nextToLast->next = NULL;
    }
    else
    {
        list->first = NULL;
    }
    content = last->content;
    free(content);
    free(last);
    list->length--;
}

void shift(List *list)
{
    Element *first;
    char *content;
    if (list == NULL || list->length <= 0)
    {
        exit(-1);
    }
    first = getElement(list, 0);
    if (list->length > 1)
    {
        Element *second;
        second = getElement(list, 1);
        list->first = second;
    }
    else
    {
        list->first = NULL;
    }
    content = first->content;
    free(content);
    free(first);
    list->length--;
}

int has(List *list, char *comparator)
{
    if (list == NULL)
    {
        exit(-1);
    }
    Element *current = list->first;
    while (current != NULL)
    {
        if (strcmp(current->content, comparator) == 0)
            return 1;
        current = current->next;
    }
    return 0;
}

int hasClone(List *list)
{
    if (list == NULL)
    {
        exit(-1);
    }
    int i, j;
    for (i = 0; i < list->length; i++)
        for (j = 0; j < list->length; j++)
            if (strcmp(getElement(list, i)->content, getElement(list, j)->content) == 0 && i != j)
                return 1;
    return 0;
}

void removeClones(List *list)
{
    if (list == NULL)
    {
        exit(-1);
    }
    int value;
    while (value = findFirstClone(list), value != -1)
    {
        removeElement(list, value);
    }
}

int findFirstClone(List *list)
{
    if (list == NULL)
    {
        exit(-1);
    }
    int i, j;
    for (i = 0; i < list->length; i++)
        for (j = 0; j < list->length; j++)
            if (strcmp(getElement(list, i)->content, getElement(list, j)->content) == 0 && i != j)
                return i;
    return -1;
}

void forEach(List *list, void (*func)(char *, void *), void *data)
{
    if (list == NULL)
    {
        exit(-1);
    }

    Element *current = list->first;
    while (current != NULL)
    {
        func(current->content, data);
        current = current->next;
    }
}

int findIndex(List *list, int (*func)(char *, char *), char *comparator)
{
    int i = 0;

    if (list == NULL)
    {
        exit(-1);
    }

    Element *current = NULL;
    for (i = 0; i < list->length; i++)
    {
        current = getElement(list, i);
        if (func(current->content, comparator))
            return i;
    }
    return -1;
}

void destroyList(List *list)
{
    if (list == NULL)
    {
        exit(-1);
    }

    Element *current = list->first;
    Element *tmp = NULL;
    while (current != NULL)
    {
        tmp = current->next;
        free(current->content);
        free(current);
        current = tmp;
    }
    free(list);
}

void printList(List *list)
{
    if (list == NULL)
    {
        exit(-1);
    }

    Element *current = list->first;

    while (current != NULL)
    {
        printElement(current->content);
        current = current->next;
    }
    printf("NULL\n");
    printf("%d\n", list->length);
}

void writeListToFile(List *list, FILE *fp)
{
    if (list == NULL || fp == NULL)
    {
        exit(-1);
    }
    Element *current = list->first;
    while (current != NULL)
    {
        fprintf(fp, "%s\n", current->content);
        current = current->next;
    }
    fclose(fp);
}

void printElement(char *content)
{
    printf("%s", content);
    printf(" -> ");
}

Element *getElement(List *list, int index)
{
    int i;
    Element *element = list->first;

    if (list == NULL)
    {
        exit(-1);
    }

    if (index >= list->length || index < 0)
    {
        return list->first;
    }

    for (i = 0; i < index; i++)
    {
        element = element->next;
    }

    return element;
}

void setElement(List *list, int index, char *content)
{
    Element *element = getElement(list, index);
    if (element != NULL)
    {
        free(element->content);
        element->content = malloc((strlen(content) + 1) * sizeof(char));
        if (element->content == NULL)
        {
            exit(-1);
        }
        strcpy(element->content, content);
    }
}

void removeElement(List *list, int index)
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
        pop(list);
        return;
    }

    if (index == 0)
    {
        shift(list);
        return;
    }

    Element *previous = getElement(list, index - 1);
    Element *current = previous->next;
    Element *next = current->next;
    previous->next = next;
    free(current->content);
    free(current);
    list->length--;
}