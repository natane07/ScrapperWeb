#ifndef Option_H

#define Option_H

#include "objects.h"

OptionList *makeOptionList();
void pushOptionToList(OptionList *list, char *optionId, char *valueOption);
Option *getOptionInList(OptionList *list, size_t index);
void removeOptionInList(OptionList *list, size_t index);
void destroyOptionList(OptionList *list);
void printOptionList(OptionList *list);
bool isVersioning(OptionList *list);

#endif