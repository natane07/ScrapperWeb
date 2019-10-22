#ifndef ARTICLE_H

#define ARTICLE_H

#include "objects.h"

ArticleList *makeArticleList();
void pushArticleToList(ArticleList *list, char *article);
Article *getArticleInList(ArticleList *list, size_t index);
void removeArticleInList(ArticleList *list, size_t index);
void destroyArticleList(ArticleList *list);
void printArticleList(ArticleList *list);

#endif