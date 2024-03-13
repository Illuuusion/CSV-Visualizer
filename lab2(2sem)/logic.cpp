#include "logic.h"
#include <QDebug>

Node* inputAndManageDataFromFile(AppContext* context, Node* top, CheckInput* input){
    char* buffer = 0;
    char** dictionary = (char**)malloc(sizeof(char*) * MIN_ARRAY);
    input->countOk = 0;
    input->countError = 0;
    top->next = (Node*)calloc(1, sizeof(Node));
    Node* curr = top->next;
    FILE* file = fopen((context->fileName).c_str(), "r");
    if (file){
        buffer = (char*) malloc(sizeof(char) * MIN_SYMBOLS);
        while (fgets(buffer, MIN_SYMBOLS, file)){
            buffer[strcspn(buffer, "\n")] = '\0';
            if (parseWords(buffer, dictionary) == 7){
                addToStructFromArr(&(curr->data), dictionary);
                ++input->countOk;
                curr->next = (Node*)calloc(1, sizeof(Node));
                curr = curr->next;
            }
            else ++input->countError;
        }
    }
    return top;
}

unsigned newArrayByUser(AppContext* context, Node* top, double* arr, Node* tail){
    unsigned i = 0;
    tail = top->next;
    while (tail->next){
        if (tail->data.regionName != context->regionName) tail = tail->next;
        else{
            switch(context->numberColumn){
                case POPULATION:
                    arr[i] = tail->data.populationGrowth;
                    tail = tail->next;
                    ++i;
                    break;
                case BIRTH_RATE:
                    arr[i] = tail->data.birthRate;
                    tail = tail->next;
                    ++i;
                    break;
                case DEATH_RATE:
                    arr[i] = tail->data.deathRate;
                    tail = tail->next;
                    ++i;
                    break;
                case DEMOGRAPHIC:
                    arr[i] = tail->data.demographicWeight;
                    tail = tail->next;
                    ++i;
                    break;
                case URBANIZATION:
                    arr[i] = tail->data.urbanization;
                    tail = tail->next;
                    ++i;
                    break;
            }
        }
    }
    return i;
}

void calculateMetrics(AppContext* context, double* arr, CalculatedMetrics* metrics, unsigned count){
    sortArr(arr, context, count);
    updateMetrics(arr, context, metrics, count);
}

void sortArr(double* arr, AppContext* context, unsigned count){
    switch(context->numberColumn){
        case POPULATION:
            sortByPopulation(arr, count);
            break;
        case BIRTH_RATE:
            sortByBirth(arr, count);
            break;
        case DEATH_RATE:
            sortByDeath(arr, count);
            break;
        case DEMOGRAPHIC:
            sortByDemographic(arr, count);
            break;
        case URBANIZATION:
            sortByUrbanization(arr, count);
            break;
    }

}

void updateMetrics(double* arr, AppContext* context, CalculatedMetrics* metrics, unsigned count){
    switch(context->numberColumn){
        case POPULATION:
            metrics->min = arr[0];
            metrics->medium = arr[count/2];
            metrics->max = arr[count - 1];
            break;
        case BIRTH_RATE:
            metrics->min = arr[0];
            metrics->medium = arr[count/2];
            metrics->max = arr[count - 1];
            break;
        case DEATH_RATE:
            metrics->min = arr[0];
            metrics->medium = arr[count/2];
            metrics->max = arr[count - 1];
            break;
        case DEMOGRAPHIC:
            metrics->min = arr[0];
            metrics->medium = arr[count/2];
            metrics->max = arr[count - 1];
            break;
        case URBANIZATION:
            metrics->min = arr[0];
            metrics->medium = arr[count/2];
            metrics->max = arr[count - 1];
            break;
    }

}

void swapElement(double* adress1, double* adress2){
    double save = *adress1;
    *adress1 = *adress2;
    *adress2 = save;
}

void sortByPopulation(double* arr, unsigned count){
    for (unsigned i = 0; i < count; ++i){
        for (unsigned j = i + 1; j < count; ++j){
            if (arr[i] > arr[j]){
                swapElement(arr + i, arr + j);
            }
        }
    }
}

void sortByBirth(double* arr, unsigned count){
    for (unsigned i = 0; i < count; ++i){
        for (unsigned j = i + 1; j < count; ++j){
            if (arr[i] > arr[j]){
                swapElement(arr + i, arr + j);
            }
        }
    }
}

void sortByDeath(double* arr, unsigned count){
    for (unsigned i = 0; i < count; ++i){
        for (unsigned j = i + 1; j < count; ++j){
            if (arr[i] > arr[j]){
                swapElement(arr + i, arr + j);
            }
        }
    }
}

void sortByDemographic(double* arr, unsigned count){
    for (unsigned i = 0; i < count; ++i){
        for (unsigned j = i + 1; j < count; ++j){
            if (arr[i] > arr[j]){
                swapElement(arr + i, arr + j);
            }
        }
    }
}

void sortByUrbanization(double* arr, unsigned count){
    for (unsigned i = 0; i < count; ++i){
        for (unsigned j = i + 1; j < count; ++j){
            if (arr[i] > arr[j]){
                swapElement(arr + i, arr + j);
            }
        }
    }
}

void addToStructFromArr(Region* region, char** arr){
    region->year = QString(arr[0]).toInt();
    region->regionName = QString(arr[1]).toStdString();
    region->populationGrowth = QString(arr[2]).toDouble();
    region->birthRate = QString(arr[3]).toDouble();
    region->deathRate = QString(arr[4]).toDouble();
    region->demographicWeight = QString(arr[5]).toDouble();
    region->urbanization = QString(arr[6]).toDouble();
}

size_t parseWords(std::string str, char** arr){
    size_t i = 0;
    const char* p = str.c_str();
    for (char* pSpr; pSpr = strpbrk(p, SEPARATOR); ++p) {
        if (p != pSpr) {
            long len = strlen(p) - strlen(pSpr);
            arr[i] = (char*)malloc((len + 1) * sizeof(char));
            strncpy(arr[i], p, len + 1);
            arr[i][len] = '\0';
            ++i;
            p = pSpr;
        }
    }
    if (strlen(p)) {
        arr[i] = (char*)malloc((strlen(p)) * sizeof(char));
        strcpy(arr[i], p);
        ++i;
    }
    return i;
}

void updateFileNameContext(AppContext* context, AppParams params){
    context->fileName = params.fileName;
}

void updateRegionNameContext(AppContext* context, AppParams params){
    context->regionName = params.regionName;
}

void updateNumberColumnContext(AppContext* context, AppParams params){
    context->numberColumn = params.numberColumn;
}

void defaultInitialization(AppContext* context){
    context->numberColumn = 3;
}
