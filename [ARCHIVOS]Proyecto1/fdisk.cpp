#include "fdisk.h"

bool fdisk::comandoFdisk(vector<string> c){
    string size = "", fit = "wf", unit = "k", path = "", type = "p", dlete = "", name = "", add = "", primero = "", aux;
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
        else if(aux == "-type")
            type = c.at(i).substr(c.at(i).find_first_of("=") + 1, c.at(i).size());
        else if(aux == "-delete")
            dlete = c.at(i).substr(c.at(i).find_first_of("=") + 1, c.at(i).size());
        else if(aux == "-name")
            name = c.at(i).substr(c.at(i).find_first_of("=") + 1, c.at(i).size());
        else if(aux == "-add")
            add = c.at(i).substr(c.at(i).find_first_of("=") + 1, c.at(i).size());
        if(primero == "" && (aux == "-add" || aux == "-delete"))
            primero = aux;
    }
    int i = path.find_first_of("\""), j = path.find_last_of("\"");
    if(j != 0 && j != i) path = path.substr(i + 1, j - 1);
    i = name.find_first_of("\""), j = name.find_last_of("\"");
    if(j != 0 && j != i) name = name.substr(i + 1, j - 1);
    if(path == ""){
        cout << "ERROR EN FDISK!!!" << endl;
        cout << "-path= O -path=\"...\" DEBE DE TENER UN PARAMETRO TIPO RUTA" << endl;
        return false;
    }
    if(name == ""){
        cout << "ERROR EN FDISK!!!" << endl;
        cout << "-name= O -name=\"...\" DEBE DE TENER UN PARAMETRO NO VACIO" << endl;
        return false;
    }
    comandos.clear();
    comandos.push_back(path);
    comandos.push_back(name);
    if(primero == "-add"){
        i = 0;
        try { i = atoi(add.c_str()); }
        catch (exception ex) {
            cout << "ERROR EN FDISK!!!" << endl;
            cout << "-add= DEBE DE TENER UN PARAMETRO NUMERICO" << endl;
            return false; }
        if(i == 0){
            cout << "ERROR EN FDISK!!!" << endl;
            cout << "-add= DEBE DE TENER UN PARAMETRO DISTINTO A 0" << endl;
            return false;
        }
        if(unit != "k" && unit != "m" && unit != "b"){
            cout << "ERROR EN FDISK!!!" << endl;
            cout << "-unit= DEBE DE TENER UN PARAMETRO B, M O K" << endl;
            return false;
        }
        comandos.push_back(add);
        comandos.push_back(unit);
        if(fdiskAdd())
            cout << "TAMANO DE LA PARTICION MODIFICADO CON EXITO" << endl;
        else
            cout << "ERROR AL MODIFICAR EL TAMANO DE LA PARTICION" << endl;
    }
    else if(primero == "-delete"){
        if(dlete != "full" && dlete != "fast"){
            cout << "ERROR EN FDISK!!!" << endl;
            cout << "-delete= DEBE DE TENER UN PARAMETRO FAST O FULL" << endl;
            return false;
        }
        comandos.push_back(dlete);
        if(fdiskDelete())
            cout << "PARTICION ELIMINADA CON EXITO" << endl;
        else
            cout << "ERROR AL ELIMINAR LA PARTICION" << endl;
    }
    else{
        i = 0;
        try { i = atoi(size.c_str()); }
        catch (exception ex) {
            cout << "ERROR EN FDISK!!!" << endl;
            cout << "-size= DEBE DE TENER UN PARAMETRO NUMERICO MAYOR A 0" << endl;
            return false; }
        if(i <= 0){
            cout << "ERROR EN FDISK!!!" << endl;
            cout << "-size= DEBE DE TENER UN PARAMETRO MAYOR A 0" << endl;
            return false;
        }
        if(fit != "ff" && fit != "bf" && fit != "wf"){
            cout << "ERROR EN FDISK!!!" << endl;
            cout << "-fit= DEBE DE TENER UN PARAMETRO FF, BF O WF" << endl;
            return false;
        }
        if(unit != "k" && unit != "m" && unit != "b"){
            cout << "ERROR EN FDISK!!!" << endl;
            cout << "-unit= DEBE DE TENER UN PARAMETRO B, M O K" << endl;
            return false;
        }
        if(type != "p" && type != "e" && type != "l"){
            cout << "ERROR EN FDISK!!!" << endl;
            cout << "-type= DEBE DE TENER UN PARAMETRO P, E O L" << endl;
            return false;
        }
        comandos.push_back(size); //2
        comandos.push_back(fit); //3
        comandos.push_back(unit); //4
        comandos.push_back(type); //5
        if(fdiskCrear())
            cout << "PARTICION CREADA CON EXITO" << endl;
        else
            cout << "ERROR AL CREAR LA PARTICION" << endl;
    }
    return true;
}

bool fdisk::fdiskAdd(){
    return false;
}

bool fdisk::fdiskCrear(){
    ver();
    FILE *archivo;
    archivo = fopen(comandos.at(0).c_str(), "r+b");
    if(archivo == NULL){
        cout << "EL ARCHIVO BUSCADO NO EXISTE" << endl;
        return false;
    }
    extras::MBR mbr;
    extras::Particion P;
    extras::EBR ebr;
    fread(&mbr, sizeof (mbr), 1, archivo);
    long long size = atoi(comandos.at(2).c_str());
    int unit = 1, i = 0;
    if(comandos.at(4) == "k") unit = 1024;
    else if(comandos.at(4) == "m") unit = 1024*1024;
    size = unit*size;
    if(comandos.at(5) == "p"){
        if(mbr.p1.status == 'N'){
            if(mbr.p4.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 4" << endl;
                return false;
            }
            else if(mbr.p2.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 2" << endl;
                return false;
            }
            else if(mbr.p3.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 3" << endl;
                return false;
            }
            if((size + sizeof (mbr) + mbr.p2.size + mbr.p3.size + mbr.p4.size) > mbr.tamano){
                cout << "EL TAMANO ASIGNADO ES DEMASIADO GRANDE" << endl;
                return false;
            }
            P.type = 'P';
            P.status = 'A';
            P.size = size;
            strcpy(P.name, comandos.at(1).c_str());
            if(comandos.at(3) == "ff") P.fit = 'F';
            else if(comandos.at(3) == "bf") P.fit = 'B';
            else P.fit = 'W';
            P.start = sizeof (mbr);
            mbr.p1 = P;
        }
        else if(mbr.p2.status == 'N'){
            if(mbr.p1.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 1" << endl;
                return false;
            }
            else if(mbr.p4.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 4" << endl;
                return false;
            }
            else if(mbr.p3.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 3" << endl;
                return false;
            }
            if((size + sizeof (mbr) + mbr.p1.size + mbr.p3.size + mbr.p4.size) > mbr.tamano){
                cout << "EL TAMANO ASIGNADO ES DEMASIADO GRANDE" << endl;
                return false;
            }
            P.type = 'P';
            P.status = 'A';
            P.size = size;
            strcpy(P.name, comandos.at(1).c_str());
            if(comandos.at(3) == "ff") P.fit = 'F';
            else if(comandos.at(3) == "bf") P.fit = 'B';
            else P.fit = 'W';
            P.start = sizeof(mbr) + mbr.p1.size;
            mbr.p2 = P;
        }
        else if(mbr.p3.status == 'N'){
            if(mbr.p1.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 1" << endl;
                return false;
            }
            else if(mbr.p2.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 2" << endl;
                return false;
            }
            else if(mbr.p4.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 4" << endl;
                return false;
            }
            if((size + sizeof (mbr) + mbr.p2.size + mbr.p1.size + mbr.p4.size) > mbr.tamano){
                cout << "EL TAMANO ASIGNADO ES DEMASIADO GRANDE" << endl;
                return false;
            }
            P.type = 'P';
            P.status = 'A';
            P.size = size;
            strcpy(P.name, comandos.at(1).c_str());
            if(comandos.at(3) == "ff") P.fit = 'F';
            else if(comandos.at(3) == "bf") P.fit = 'B';
            else P.fit = 'W';
            P.start = sizeof (mbr) + mbr.p1.size + mbr.p2.size;
            mbr.p3 = P;
        }
        else if(mbr.p4.status == 'N'){
            if(mbr.p1.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 1" << endl;
                return false;
            }
            else if(mbr.p2.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 2" << endl;
                return false;
            }
            else if(mbr.p3.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 3" << endl;
                return false;
            }
            if((size + sizeof (mbr) + mbr.p2.size + mbr.p3.size + mbr.p1.size) > mbr.tamano){
                cout << "EL TAMANO ASIGNADO ES DEMASIADO GRANDE" << endl;
                return false;
            }
            P.type = 'P';
            P.status = 'A';
            P.size = size;
            strcpy(P.name, comandos.at(1).c_str());
            if(comandos.at(3) == "ff") P.fit = 'F';
            else if(comandos.at(3) == "bf") P.fit = 'B';
            else P.fit = 'W';
            P.start = sizeof (mbr) + mbr.p1.size + mbr.p2.size + mbr.p3.size;
            mbr.p4 = P;
        }
        else{
            cout << "NO EXISTEN PARTICIONES DISPONIBLES PARA CREAR UNA PRIMARIA" << endl;
            return false;
        }

    }
    else if(comandos.at(5) == "e"){
        if(mbr.p1.type == 'E' || mbr.p2.type == 'E' || mbr.p3.type == 'E' || mbr.p4.type == 'E'){
            cout << "YA EXISTE UNA PARTICION EXTENDIDA" << endl;
            return false;
        }
        else if(mbr.p1.status == 'N'){
            if(mbr.p4.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 4" << endl;
                return false;
            }
            else if(mbr.p2.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 2" << endl;
                return false;
            }
            else if(mbr.p3.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 3" << endl;
                return false;
            }
            if((size + sizeof (mbr) + mbr.p2.size + mbr.p3.size + mbr.p4.size) > mbr.tamano){
                cout << "EL TAMANO ASIGNADO ES DEMASIADO GRANDE" << endl;
                return false;
            }
            P.type = 'E';
            P.status = 'A';
            P.size = size;
            strcpy(P.name, comandos.at(1).c_str());
            if(comandos.at(3) == "ff") P.fit = 'F';
            else if(comandos.at(3) == "bf") P.fit = 'B';
            else P.fit = 'W';
            P.start = sizeof (mbr);
            mbr.p1 = P;
        }
        else if(mbr.p2.status == 'N'){
            if(mbr.p4.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 4" << endl;
                return false;
            }
            else if(mbr.p2.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 2" << endl;
                return false;
            }
            else if(mbr.p3.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 3" << endl;
                return false;
            }
            if((size + sizeof (mbr) + mbr.p2.size + mbr.p3.size + mbr.p4.size) > mbr.tamano){
                cout << "EL TAMANO ASIGNADO ES DEMASIADO GRANDE" << endl;
                return false;
            }
            P.type = 'E';
            P.status = 'A';
            P.size = size;
            strcpy(P.name, comandos.at(1).c_str());
            if(comandos.at(3) == "ff") P.fit = 'F';
            else if(comandos.at(3) == "bf") P.fit = 'B';
            else P.fit = 'W';
            P.start = sizeof(mbr) + mbr.p1.size;
            mbr.p2 = P;
        }
        else if(mbr.p3.status == 'N'){
            if(mbr.p4.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 4" << endl;
                return false;
            }
            else if(mbr.p2.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 2" << endl;
                return false;
            }
            else if(mbr.p3.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 3" << endl;
                return false;
            }
            if((size + sizeof (mbr) + mbr.p2.size + mbr.p3.size + mbr.p4.size) > mbr.tamano){
                cout << "EL TAMANO ASIGNADO ES DEMASIADO GRANDE" << endl;
                return false;
            }
            P.type = 'E';
            P.status = 'A';
            P.size = size;
            strcpy(P.name, comandos.at(1).c_str());
            if(comandos.at(3) == "ff") P.fit = 'F';
            else if(comandos.at(3) == "bf") P.fit = 'B';
            else P.fit = 'W';
            P.start = sizeof(mbr) + mbr.p1.size + mbr.p2.size;
            mbr.p3 = P;
        }
        else if(mbr.p4.status == 'N'){
            if(mbr.p4.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 4" << endl;
                return false;
            }
            else if(mbr.p2.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 2" << endl;
                return false;
            }
            else if(mbr.p3.name == comandos.at(1).c_str()){
                cout << "EL NOMBRE YA EXISTE EN LA PARTICION 3" << endl;
                return false;
            }
            if((size + sizeof (mbr) + mbr.p2.size + mbr.p3.size + mbr.p4.size) > mbr.tamano){
                cout << "EL TAMANO ASIGNADO ES DEMASIADO GRANDE" << endl;
                return false;
            }
            P.type = 'E';
            P.status = 'A';
            P.size = size;
            strcpy(P.name, comandos.at(1).c_str());
            if(comandos.at(3) == "ff") P.fit = 'F';
            else if(comandos.at(3) == "bf") P.fit = 'B';
            else P.fit = 'W';
            P.start = sizeof(mbr) + mbr.p1.size + mbr.p2.size + mbr.p3.size;
            mbr.p4 = P;
        }
        else{
            cout << "NO EXISTEN PARTICIONES DISPONIBLES PARA CREAR UNA EXTENDIDA" << endl;
            return false;
        }
    }
    else{
        if(mbr.p1.type == 'E'){
            extras::EBR ebrAnterior;
            fseek(archivo, mbr.p1.start, SEEK_SET);
            fread(&ebrAnterior,sizeof (ebrAnterior), 1, archivo);
            int next = mbr.p1.start;
            while(ebrAnterior.size > 0){
                next = ebrAnterior.start + ebrAnterior.size;
                if(ebrAnterior.next != -1){
                    fseek(archivo, ebrAnterior.next, SEEK_SET);
                    fread(&ebrAnterior,sizeof (ebrAnterior), 1, archivo);
                }
                else break;
            }
            if(sizeof (ebr) + next + size > mbr.p1.start + mbr.p1.size){
                cout << "EL TAMANO DE LA PARTICION LOGICA ES MAYOR AL DE LA PARTCION EXTENDIDA" << endl;
                return false;
            }
            if(next != mbr.p1.start){
                cout <<"aqui:" << next << endl;
                ebrAnterior.next = next;
                fseek(archivo, ebrAnterior.start - sizeof(ebrAnterior), SEEK_SET);
                fwrite((char*) &ebrAnterior, sizeof(ebrAnterior), 1, archivo);
            }
            ebr.status = 'A';
            if(comandos.at(3) == "ff") ebr.fit = 'F';
            else if(comandos.at(3) == "bf") ebr.fit = 'B';
            else ebr.fit = 'W';
            ebr.size = size;
            ebr.next = -1;
            ebr.start = sizeof (ebrAnterior) + next;
            strcpy(ebr.name, comandos.at(1).c_str());
            i = next;
        }
        else if(mbr.p2.type == 'E'){
            extras::EBR ebrAnterior;
            fseek(archivo, mbr.p1.start, SEEK_SET);
            fread(&ebrAnterior,sizeof (ebrAnterior), 1, archivo);
            int next = mbr.p1.start;
            while(ebrAnterior.size > 0){
                next = ebrAnterior.start + ebrAnterior.size;
                if(ebrAnterior.next != -1){
                    fseek(archivo, ebrAnterior.next, SEEK_SET);
                    fread(&ebrAnterior,sizeof (ebrAnterior), 1, archivo);
                }
                else break;
            }
            if(sizeof (ebr) + next + size > mbr.p1.start + mbr.p1.size){
                cout << "EL TAMANO DE LA PARTICION LOGICA ES MAYOR AL DE LA PARTCION EXTENDIDA" << endl;
                return false;
            }
            if(next != mbr.p1.start){
                cout <<"aqui:" << next << endl;
                ebrAnterior.next = next;
                fseek(archivo, ebrAnterior.start - sizeof(ebrAnterior), SEEK_SET);
                fwrite((char*) &ebrAnterior, sizeof(ebrAnterior), 1, archivo);
            }
            ebr.status = 'A';
            if(comandos.at(3) == "ff") ebr.fit = 'F';
            else if(comandos.at(3) == "bf") ebr.fit = 'B';
            else ebr.fit = 'W';
            ebr.size = size;
            ebr.next = -1;
            ebr.start = sizeof (ebrAnterior) + next;
            strcpy(ebr.name, comandos.at(1).c_str());
            i = next;
        }
        else if(mbr.p3.type == 'E'){
            extras::EBR ebrAnterior;
            fseek(archivo, mbr.p1.start, SEEK_SET);
            fread(&ebrAnterior,sizeof (ebrAnterior), 1, archivo);
            int next = mbr.p1.start;
            while(ebrAnterior.size > 0){
                next = ebrAnterior.start + ebrAnterior.size;
                if(ebrAnterior.next != -1){
                    fseek(archivo, ebrAnterior.next, SEEK_SET);
                    fread(&ebrAnterior,sizeof (ebrAnterior), 1, archivo);
                }
                else break;
            }
            if(sizeof (ebr) + next + size > mbr.p1.start + mbr.p1.size){
                cout << "EL TAMANO DE LA PARTICION LOGICA ES MAYOR AL DE LA PARTCION EXTENDIDA" << endl;
                return false;
            }
            if(next != mbr.p1.start){
                cout <<"aqui:" << next << endl;
                ebrAnterior.next = next;
                fseek(archivo, ebrAnterior.start - sizeof(ebrAnterior), SEEK_SET);
                fwrite((char*) &ebrAnterior, sizeof(ebrAnterior), 1, archivo);
            }
            ebr.status = 'A';
            if(comandos.at(3) == "ff") ebr.fit = 'F';
            else if(comandos.at(3) == "bf") ebr.fit = 'B';
            else ebr.fit = 'W';
            ebr.size = size;
            ebr.next = -1;
            ebr.start = sizeof (ebrAnterior) + next;
            strcpy(ebr.name, comandos.at(1).c_str());
            i = next;
        }
        else if(mbr.p4.type == 'E'){
            extras::EBR ebrAnterior;
            fseek(archivo, mbr.p1.start, SEEK_SET);
            fread(&ebrAnterior,sizeof (ebrAnterior), 1, archivo);
            int next = mbr.p1.start;
            while(ebrAnterior.size > 0){
                next = ebrAnterior.start + ebrAnterior.size;
                if(ebrAnterior.next != -1){
                    fseek(archivo, ebrAnterior.next, SEEK_SET);
                    fread(&ebrAnterior,sizeof (ebrAnterior), 1, archivo);
                }
                else break;
            }
            if(sizeof (ebr) + next + size > mbr.p1.start + mbr.p1.size){
                cout << "EL TAMANO DE LA PARTICION LOGICA ES MAYOR AL DE LA PARTCION EXTENDIDA" << endl;
                return false;
            }
            if(next != mbr.p1.start){
                cout <<"aqui:" << next << endl;
                ebrAnterior.next = next;
                fseek(archivo, ebrAnterior.start - sizeof(ebrAnterior), SEEK_SET);
                fwrite((char*) &ebrAnterior, sizeof(ebrAnterior), 1, archivo);
            }
            ebr.status = 'A';
            if(comandos.at(3) == "ff") ebr.fit = 'F';
            else if(comandos.at(3) == "bf") ebr.fit = 'B';
            else ebr.fit = 'W';
            ebr.size = size;
            ebr.next = -1;
            ebr.start = sizeof (ebrAnterior) + next;
            strcpy(ebr.name, comandos.at(1).c_str());
            i = next;
        }
        else{
            cout << "NO EXISTEN PARTICIONES EXTENDIDAS PARA CREAR LA LOGICA" << endl;
            return false;
        }
    }
    fseek(archivo, i, SEEK_SET);
    if(i == 0)
        fwrite((char*) &mbr, sizeof(mbr), 1, archivo);
    else
        fwrite((char*) &ebr, sizeof(ebr), 1, archivo);
    fclose(archivo);
    ver();
    return true;
}

bool fdisk::fdiskDelete(){
    return true;
}


bool fdisk::ver(){
    FILE *archivo;
    extras::MBR mbr;
    extras::Particion P;
    extras::EBR ebr;
    archivo = fopen(comandos.at(0).c_str(), "r");
    if(archivo == NULL) return false;
    fread(&mbr, sizeof (mbr), 1, archivo);
    time_t tiempo = mbr.fecha;
    struct tm* timeinfo;
    timeinfo = localtime(&tiempo);
    cout << "*********************************" << endl;
    cout << "--->Tamano:    " << mbr.tamano << endl;
    cout << "--->signature: " << mbr.signature << endl;
    cout << "--->fecha:     " << asctime(timeinfo) << endl;
    cout << "--->fit:       " << mbr.fit << endl;
    P = mbr.p1;
    cout << "--->P1:" << endl;
    cout << "    -->status: " << P.status << endl;
    cout << "    -->type:   " << P.type << endl;
    cout << "    -->fit:    " << P.fit << endl;
    cout << "    -->start:  " << P.start << endl;
    cout << "    -->size:   " << P.size << endl;
    cout << "    -->name:   " << P.name << endl;
    if(P.type == 'E'){
        fseek(archivo, P.start, SEEK_SET);
        fread(&ebr, sizeof (ebr), 1, archivo);
        while(ebr.size > 0){
            cout << "    -->EBR:"<< endl;
            cout << "       -->status: " << ebr.status << endl;
            cout << "       -->fit:    " << ebr.fit << endl;
            cout << "       -->start:  " << ebr.start << endl;
            cout << "       -->size:   " << ebr.size << endl;
            cout << "       -->next:   " << ebr.next << endl;
            cout << "       -->name:   " << ebr.name << endl;
            if(ebr.next != -1){
                fseek(archivo, ebr.next, SEEK_SET);
                fread(&ebr, sizeof (ebr), 1, archivo);
            }
            else break;
        }
    }
    P = mbr.p2;
    cout << "--->P2:" << endl;
    cout << "    -->status: " << P.status << endl;
    cout << "    -->type:   " << P.type << endl;
    cout << "    -->fit:    " << P.fit << endl;
    cout << "    -->start:  " << P.start << endl;
    cout << "    -->size:   " << P.size << endl;
    cout << "    -->name:   " << P.name << endl;
    if(P.type == 'E'){
        fseek(archivo, P.start, SEEK_SET);
        fread(&ebr, sizeof (ebr), 1, archivo);
        while(ebr.size > 0){
            cout << "    -->EBR:"<< endl;
            cout << "       -->status: " << ebr.status << endl;
            cout << "       -->fit:    " << ebr.fit << endl;
            cout << "       -->start:  " << ebr.start << endl;
            cout << "       -->size:   " << ebr.size << endl;
            cout << "       -->next:   " << ebr.next << endl;
            cout << "       -->name:   " << ebr.name << endl;
            if(ebr.next != -1){
                fseek(archivo, ebr.next, SEEK_SET);
                fread(&ebr, sizeof (ebr), 1, archivo);
            }
            else break;
        }
    }
    P = mbr.p3;
    cout << "--->P3:" << endl;
    cout << "    -->status: " << P.status << endl;
    cout << "    -->type:   " << P.type << endl;
    cout << "    -->fit:    " << P.fit << endl;
    cout << "    -->start:  " << P.start << endl;
    cout << "    -->size:   " << P.size << endl;
    cout << "    -->name:   " << P.name << endl;
    if(P.type == 'E'){
        fseek(archivo, P.start, SEEK_SET);
        fread(&ebr, sizeof (ebr), 1, archivo);
        while(ebr.size > 0){
            cout << "    -->EBR:"<< endl;
            cout << "       -->status: " << ebr.status << endl;
            cout << "       -->fit:    " << ebr.fit << endl;
            cout << "       -->start:  " << ebr.start << endl;
            cout << "       -->size:   " << ebr.size << endl;
            cout << "       -->next:   " << ebr.next << endl;
            cout << "       -->name:   " << ebr.name << endl;
            if(ebr.next != -1){
                fseek(archivo, ebr.next, SEEK_SET);
                fread(&ebr, sizeof (ebr), 1, archivo);
            }
            else break;
        }
    }
    P = mbr.p4;
    cout << "--->P4:" << endl;
    cout << "    -->status: " << P.status << endl;
    cout << "    -->type:   " << P.type << endl;
    cout << "    -->fit:    " << P.fit << endl;
    cout << "    -->start:  " << P.start << endl;
    cout << "    -->size:   " << P.size << endl;
    cout << "    -->name:   " << P.name << endl;
    if(P.type == 'E'){
        fseek(archivo, P.start, SEEK_SET);
        fread(&ebr, sizeof (ebr), 1, archivo);
        while(ebr.size > 0){
            cout << "    -->EBR:"<< endl;
            cout << "       -->status: " << ebr.status << endl;
            cout << "       -->fit:    " << ebr.fit << endl;
            cout << "       -->start:  " << ebr.start << endl;
            cout << "       -->size:   " << ebr.size << endl;
            cout << "       -->next:   " << ebr.next << endl;
            cout << "       -->name:   " << ebr.name << endl;
            if(ebr.next != -1){
                fseek(archivo, ebr.next, SEEK_SET);
                fread(&ebr, sizeof (ebr), 1, archivo);
            }
            else break;
        }
    }
    cout << "*********************************" << endl;
    return true;
}

