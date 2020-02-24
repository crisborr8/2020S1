#ifndef UNMOUNT_H
#define UNMOUNT_H

#include "extras.h"

class unmount
{
public:
    int comandoUnmount(vector<vector<string>> particiones, string id);
private:
    extras ext;
};

#endif // UNMOUNT_H
