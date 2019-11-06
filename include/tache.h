#ifndef Tache_H

#define Tache_H

#include "objects.h"

TacheList *makeTacheList();
void pushTacheToList(TacheList *list, char *tache, int hour, int min, int sec);
Tache *getTacheInList(TacheList *list, size_t index);
void removeTacheInList(TacheList *list, size_t index);
void destroyTacheList(TacheList *list);
void printTacheList(TacheList *list);
void pushPlanificateurListToTache(TacheList *list, char *valuePlanificateur);

#endif