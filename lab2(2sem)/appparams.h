#ifndef APPPARAMS
#define APPPARAMS

#include "QString"
#include <string>

struct AppParams {
    std::string fileName;
    std::string regionName;
    int numberColumn;
};

struct CheckInput {
    int countOk;
    int countError;
};

#endif // APPPARAMS

