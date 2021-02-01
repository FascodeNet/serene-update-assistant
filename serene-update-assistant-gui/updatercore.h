#ifndef UPDATERCORE_H
#define UPDATERCORE_H

#include <string>
#include<fstream>
#include <regex>
#include<iostream>

class UpdaterCore
{
public:
    UpdaterCore();
    std::string check_current_ver();

};

#endif // UPDATERCORE_H
