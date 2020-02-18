#ifndef MKDISK_H
#define MKDISK_H

#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

using namespace std;

class mkdisk
{
public:
    void comandoMkdisk(vector<string> comandos);
private:
    //*************************ESCRIBIR BYTES*******************
    bool escribirBytes(vector<string> comandos);
    //*************************CREAR DIRECTORIO*****************
    bool crearDirectorio(string path);
    //*************************ESTRUCTURAS**********************
    struct Particion{
        char status;
        char type; //SOLO PARA PARTICION
        char fit;
        int start;
        int size;
        int next; //SOLO PARA EXT
        char name[16];
    };
    struct MBR{
        int tamano;
        time_t fecha;
        int signature;
        char fit;
        Particion p1;
        Particion p2;
        Particion p3;
        Particion p4;
    };
    //************************* EXTRAS *************************
    bool probarBytesEscritos(string path);
    int getRandom();
    string toLowerString(string s);
    char toLowerChar(char c);
};

#endif // MKDISK_H
