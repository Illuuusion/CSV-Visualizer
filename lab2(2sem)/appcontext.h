#ifndef APPCONTEXT_H
#define APPCONTEXT_H
#include "QString"
#include <string>

struct AppContext {
    std::string fileName;
    std::string regionName;
    int numberColumn;
};

#endif // APPCONTEXT_H
