#ifndef MENU_H
#define MENU_H

#include "extras.h"
#include "mkdisk.h"
#include "rmdisk.h"
#include "fdisk.h"
#include "mount.h"
#include "unmount.h"
#include "rep.h"

class Menu
{
public:
    Menu();

private:
    extras ext;
    mkdisk mk;
    rmdisk rm;
    fdisk fd;
    mount mt;
    unmount um;
    rep rp;

    string comando, s;
    vector<string> comandosIngresados;
    vector<string> comandosPermitidosLinea;
    vector<vector<string>> comandosPermitidos;
    vector<vector<string>> particionesMontadas;

    void ingresarComandos();

    void setVectorComandosIngresados();
    bool verificarComandosIngresados();

    void setVectorComandosPermitidos();
};

#endif // MENU_H
