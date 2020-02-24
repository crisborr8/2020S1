#include "mkdisk.h"

bool mkdisk::comandoMkdisk(vector<string> c){
    string size = "", fit = "ff", unit = "m", path = "", aux;
    for(int i = 1; i < static_cast<int>(c.size()); i++){
        aux = ext.toLowerS(c.at(i));
        aux = aux.substr(0, aux.find_first_of("="));
        if(aux == "-size")
            size = c.at(i).substr(c.at(i).find_first_of("=") + 1, c.at(i).size());
        else if(aux == "-fit")
            fit = c.at(i).substr(c.at(i).find_first_of("=") + 1, c.at(i).size());
        else if(aux == "-unit")
            unit = c.at(i).substr(c.at(i).find_first_of("=") + 1, c.at(i).size());
        else if(aux == "-path")
            path = c.at(i).substr(c.at(i).find_first_of("=") + 1, c.at(i).size());
    }
    int i = path.find_first_of("\""), j = path.find_last_of("\"");
    if(j != 0 && j != i) path = path.substr(i + 1, j - 1);
    unit = ext.trim(ext.toLowerS(unit));
    fit = ext.trim(ext.toLowerS(fit));
    i = 0;
    try { i = atoi(size.c_str()); }
    catch (exception ex) {
        cout << "ERROR EN MKDISK!!!" << endl;
        cout << "-size= DEBE DE TENER UN PARAMETRO NUMERICO MAYOR A 0" << endl;
        return false; }
    if(i <= 0){
        cout << "ERROR EN MKDISK!!!" << endl;
        cout << "-size= DEBE DE TENER UN PARAMETRO MAYOR A 0" << endl;
        return false;
    }
    if(fit != "ff" && fit != "bf" && fit != "wf"){
        cout << "ERROR EN MKDISK!!!" << endl;
        cout << "-fit= DEBE DE TENER UN PARAMETRO FF, BF O WF" << endl;
        return false;
    }
    if(unit != "k" && unit != "m"){
        cout << "ERROR EN MKDISK!!!" << endl;
        cout << "-unit= DEBE DE TENER UN PARAMETRO M O K" << endl;
        return false;
    }
    if(path == ""){
        cout << "ERROR EN MKDISK!!!" << endl;
        cout << "-path= O -path=\"...\" DEBE DE TENER UN PARAMETRO TIPO RUTA" << endl;
        return false;
    }
    if(ext.toLowerS(path).find_last_of(".disk") != path.size() - 1){
        cout << "ERROR EN MKDISK!!!" << endl;
        cout << "-path= O -path=\"...\" DEBE TERMINAR CON UN .disk" << endl;
        return false;
    }
    comandos.clear();
    comandos.push_back(path.substr(0, path.find_last_of("/")));
    comandos.push_back(path);
    comandos.push_back(size);
    comandos.push_back(fit);
    comandos.push_back(unit);
    signature = ext.getRandom();
    if(crearDisco()){
        comandos.at(1) = comandos.at(1).substr(0, comandos.at(1).find_last_of(".")) + "_RAID.disk";
        if(crearDisco())
            cout << "******SE HA CREADO EL DISCO CON EXITO******" << endl;
        else
            cout << "ERROR INESPERADO AL CREAR EL DISCO" << endl;
    }
    else
        cout << "ERROR INESPERADO AL CREAR EL DISCO" << endl;
    return true;
}

bool mkdisk::crearDisco(){
    if(comandos.at(0) == comandos.at(1))
        comandos.at(0) = "/";
    if (mkdir(comandos.at(0).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
        if(!(errno == EEXIST))
            return false;
    FILE *archivo;
    archivo = fopen(comandos.at(1).c_str(), "w");
    if(archivo == NULL) return false;

    long long size = atoi(comandos.at(2).c_str());
    int unit = 1;
    if(comandos.at(4) == "m") unit = 1024;
    size = unit*size*1024;
    char buffer[size];
    for(int i: buffer)
        buffer[i] = (char)(0);

    fwrite(buffer, sizeof(char), sizeof (buffer), archivo);
    fclose(archivo);
    cout << "ARCHIVO CREADO!!" << endl;
    return escrituraMBR();
}

bool mkdisk::escrituraMBR(){
    FILE *archivo;
    archivo = fopen(comandos.at(1).c_str(), "r+b");
    if(archivo == NULL) return false;
    long long size = atoi(comandos.at(2).c_str());
    int unit = 1;
    if(comandos.at(4) == "m") unit = 1024;
    size = unit*size*1024;
    extras::Particion P;
    P.status = 'N';
    P.type = 0;
    P.fit = 0;
    P.start = 0;
    P.size = 0;
    strcpy(P.name, "0");
    time_t tiempo;
    time(&tiempo);
    extras::MBR mbr;
    mbr.tamano = size;
    mbr.fecha = tiempo;
    mbr.signature = signature;
    if(comandos.at(3) == "ff") mbr.fit = 'F';
    else if(comandos.at(3) == "bf") mbr.fit = 'B';
    else  mbr.fit = 'W';
    mbr.p1 = P;
    mbr.p2 = P;
    mbr.p3 = P;
    mbr.p4 = P;

    fseek(archivo, 0, SEEK_SET);
    fwrite((char*) &mbr, sizeof(mbr), 1, archivo);
    fclose(archivo);
    /*
    archivo = fopen(comandos.at(1).c_str(), "r");
    fread(&mbr, sizeof (mbr), 1, archivo);
    tiempo = mbr.fecha;
    struct tm* timeinfo;
    timeinfo = localtime(&tiempo);
    cout << "--->Tamano:    " << mbr.tamano << endl;
    cout << "--->signature: " << mbr.signature << endl;
    cout << "--->fecha:     " << asctime(timeinfo) << endl;
    cout << "--->fit:       " << mbr.fit << endl;*/

    return true;
}
