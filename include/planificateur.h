#ifndef Planificateur_H

#define Planificateur_H

#include "objects.h"

PlanificateurList *makePlanificateurList();
void pushPlanificateurToList(PlanificateurList *list, char *nameTache);
Planificateur *getPlanificateurInList(PlanificateurList *list, size_t index);
void removePlanificateurInList(PlanificateurList *list, size_t index);
void destroyPlanificateurList(PlanificateurList *list);
void printPlanificateurList(PlanificateurList *list);

#endif