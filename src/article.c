#include <windows.h>
#include "common.h"

ArticleList *makeArticleList()
{
    ArticleList *list = malloc(sizeof(ArticleList));
    if (list == NULL)
    {
        exit(-1);
    }
    list->first = NULL;
    list->length = 0;
    return list;
}

void pushArticleToList(ArticleList *list, char *article)
{
    Article *new = malloc(sizeof(Article));
    if (article == NULL || list == NULL)
    {
        exit(-1);
    }
    strcpy(new->content, article);
    new->amount = 1;
    new->next = NULL;
    if (list->length > 0)
    {
        Article *last;
        last = getArticleInList(list, list->length - 1);
        last->next = new;
    }
    else
    {
        list->first = new;
    }
    list->length++;
}

Article *getArticleInList(ArticleList *list, size_t index)
{
    int i;
    if (list == NULL)
    {
        exit(-1);
    }
    Article *current = list->first;
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

void removeArticleInList(ArticleList *list, size_t index)
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
        Article *last = getArticleInList(list, list->length - 1);
        if (list->length > 1)
        {
            Article *nextToLast = getArticleInList(list, list->length - 2);
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
        Article *first = list->first;
        Article *second = first->next;
        list->first = second;
        free(first);
        list->length--;
        return;
    }
    Article *previous = getArticleInList(list, index - 1);
    Article *current = previous->next;
    Article *next = current->next;
    previous->next = next;
    free(current);
    list->length--;
}

void destroyArticleList(ArticleList *list)
{
    if (list == NULL)
    {
        exit(-1);
    }
    Article *current = list->first;
    Article *tmp = NULL;
    while (current != NULL)
    {
        tmp = current->next;
        free(current);
        current = tmp;
    }
    free(list);
}

void printArticleList(ArticleList *list)
{
    if (list == NULL)
    {
        exit(-1);
    }
    Article *current = list->first;
    puts("ArticleList {");
    while (current != NULL)
    {
        puts("Article {");
        printf("content: %s\n", current->content);
        printf("amount: %d\n", current->amount);
        current = current->next;
        puts("}");
    }
    printf("List length: %d\n", list->length);
    puts("};");
}