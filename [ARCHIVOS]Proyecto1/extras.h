#ifndef EXTRAS_H
#define EXTRAS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <ctime>

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class extras
{
public:
    string trim(string s);
    string trimL(string s);
    string trimR(string s);
    string c_toString(char c[]);
    string c_toStringC(char c);
    string toLowerS(string s);
    char toLowerC(char c);
    int getRandom();
    struct EBR{
        char status;
        char fit;
        int start;
        int size;
        int next;
        char name[16];
    };
    struct Particion{
        char status;
        char type;
        char fit;
        int start;
        int size;
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
};

#endif // EXTRAS_H
