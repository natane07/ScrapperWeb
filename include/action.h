#ifndef Action_H

#define Action_H

#include "objects.h"

ActionList *makeActionList();
void pushActionToList(ActionList *list, char *action, char *url, OptionList *optionList);
Action *getActionInList(ActionList *list, size_t index);
void removeActionInList(ActionList *list, size_t index);
void destroyActionList(ActionList *list);
void printActionList(ActionList *list);

#endif