#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "logic.h"

enum Operation {
    UpdatingFileName,
    UpdatingRegionName,
    UpdatingNumberColumn,
    LoadData,
    CalculatingMetrics,
    Default
};


void doOperation(Operation operation, AppContext* context, AppParams params, Node* top, Node* tail, double* arr, CalculatedMetrics* metrics, CheckInput* input);

#endif
