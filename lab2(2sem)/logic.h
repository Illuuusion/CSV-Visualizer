#ifndef LOGIC_H
#define LOGIC_H


#include "appcontext.h"
#include "appparams.h"


#define SEPARATOR ","
#define MIN_ARRAY 7
#define MIN_SYMBOLS 60
#define MIN_REGIONS 27
#define POPULATION 3
#define BIRTH_RATE 4
#define DEATH_RATE 5
#define DEMOGRAPHIC 6
#define URBANIZATION 7



struct Region{
    unsigned year;
    std::string regionName;
    double populationGrowth, birthRate, deathRate, demographicWeight, urbanization;
};

struct Node{
    Region data;
    Node* next;
};

struct CalculatedMetrics{
    double min, medium, max;
    unsigned count;
};

Node* inputAndManageDataFromFile(AppContext* context, Node* top, CheckInput* input);
void addToStructFromArr(Region* region, char** arr);
void freeArr(char** arr);
size_t parseWords(std::string str, char** dictionary);
unsigned newArrayByUser(AppContext* context, Node* top, double* arr, Node* tail);
void calculateMetrics(AppContext* context, double* arr, CalculatedMetrics* metrics, unsigned count);
void sortArr(double* arr, AppContext* context, unsigned count);
void updateMetrics(double* arr, AppContext* context, CalculatedMetrics* metrics, unsigned count);
void swapElement(double* adress1, Region* adress2);
void sortByPopulation(double* arr, unsigned count);
void sortByBirth(double* arr, unsigned count);
void sortByDeath(double* arr, unsigned count);
void sortByDemographic(double* arr, unsigned count);
void sortByUrbanization(double* arr, unsigned count);
void updateFileNameContext(AppContext* context, AppParams params);
void updateRegionNameContext(AppContext* context, AppParams params);
void updateNumberColumnContext(AppContext* context, AppParams params);
void defaultInitialization(AppContext* context);

#endif // LOGIC_H
