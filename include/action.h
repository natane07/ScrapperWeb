#ifndef Action_H

#define Action_H

#include "objects.h"

ActionList *makeActionList();
void pushActionToList(ActionList *list, char *action, char *url);
Action *getActionInList(ActionList *list, size_t index);
void removeActionInList(ActionList *list, size_t index);
void destroyActionList(ActionList *list);
void printActionList(ActionList *list);
void pushOptionListToAction(ActionList *list, char *optionId, char *valueOption);

#endif