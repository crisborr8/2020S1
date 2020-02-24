#ifndef MKDISK_H
#define MKDISK_H

#include "extras.h"

class mkdisk
{
public:
    bool comandoMkdisk(vector<string> c);
private:
    extras ext;
    int signature;
    vector<string> comandos;
    bool crearDisco();
    bool escrituraMBR();
};

#endif // MKDISK_H
