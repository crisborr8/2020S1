#ifndef FDISK_H
#define FDISK_H

#include "extras.h"

class fdisk
{
public:
    bool comandoFdisk(vector<string> c);
private:
    extras ext;
    vector<string> comandos;
    bool fdiskAdd();
    bool fdiskCrear();
    bool fdiskDelete();
    bool ver();
};

#endif // FDISK_H
