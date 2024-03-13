#include "entrypoint.h"
#include <QDebug>

void doOperation(Operation operation, AppContext* context, AppParams params, Node* top, Node* tail, double* arr, CalculatedMetrics* metrics, CheckInput* input){
    switch(operation){
    case Default:
        defaultInitialization(context);
        break;
    case UpdatingFileName:
        updateFileNameContext(context, params);
        break;
    case UpdatingRegionName:
        updateRegionNameContext(context, params);
        break;
    case UpdatingNumberColumn:
        updateNumberColumnContext(context, params);
    case LoadData:
        top = inputAndManageDataFromFile(context, top, input);
        break;
    case CalculatingMetrics:
        metrics->count = newArrayByUser(context, top, arr, tail);
        calculateMetrics(context, arr, metrics, metrics->count);
        break;
    }
}
