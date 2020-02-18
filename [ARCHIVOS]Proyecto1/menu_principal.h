#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

#include "mkdisk.h"
#include "rmdisk.h"

#include <iostream>
#include <vector>

using namespace std;

class Menu_Principal
{
public:
    Menu_Principal();
private:
    mkdisk mk;
    rmdisk rm;
    string mensajeError;
    vector<string> comandos;
    vector<string> vectorComandos;
    vector <vector <string>> comandosExistentes;
    //***************** VALIDADORES DE COMANDOS ****************
    void validador(string comando);
    void dividirComando(string comando);
    void obtenerVectorComandos(string comando);
    bool validarSubComandosPermitidos();
    bool validarSubComandosParametros();
    //************************* ERRORES ************************
    void mostrarMensajeError();
    //************************* EXTRAS *************************
    void LlenarVariables();
    string toLowerString(string s);
    char toLowerChar(char c);
    string Ltrim(string s);
    string Rtrim(string s);
    string trim(string s);
};

#endif // MENU_PRINCIPAL_H
