#include "mount.h"

vector<string> mount::comandoMount(vector<string> c){
    vector<string> mount;
    string name = "", path = "", aux;
    for(int i = 1; i < static_cast<int>(c.size()); i++){
        aux = ext.toLowerS(c.at(i));
        aux = aux.substr(0, aux.find_first_of("="));
        if(aux == "-name")
            name = c.at(i).substr(c.at(i).find_first_of("=") + 1, c.at(i).size());
        else if(aux == "-path")
            path = c.at(i).substr(c.at(i).find_first_of("=") + 1, c.at(i).size());
    }
    int i = path.find_first_of("\""), j = path.find_last_of("\"");
    if(j != 0 && j != i) path = path.substr(i + 1, j - 1);
    i = name.find_first_of("\""), j = name.find_last_of("\"");
    if(j != 0 && j != i) name = name.substr(i + 1, j - 1);
    if(path == ""){
        cout << "ERROR EN MOUNT!!!" << endl;
        cout << "-path= O -path=\"...\" DEBE DE TENER UN PARAMETRO TIPO RUTA" << endl;
        return mount;
    }
    if(name == ""){
        cout << "ERROR EN MOUNT!!!" << endl;
        cout << "-name= O -name=\"...\" DEBE DE TENER UN PARAMETRO NO VACIO" << endl;
        return mount;
    }
    FILE *archivo;
    extras::MBR mbr;
    archivo = fopen(path.c_str(), "r");
    if(archivo == NULL){
        cout << "ERROR EN MOUNT!!!" << endl;
        cout << "EL ARCHIVO A MONTAR NO EXISTE!!" << endl;
    }
    fread(&mbr, sizeof (mbr), 1, archivo);
    if(mbr.p1.name == name){
        mount.push_back(path);
        mount.push_back(name);
        return mount;
    }
    else if(mbr.p2.name == name){
        mount.push_back(path);
        mount.push_back(name);
        return mount;
    }
    else if(mbr.p3.name == name){
        mount.push_back(path);
        mount.push_back(name);
        return mount;
    }
    else if(mbr.p4.name == name){
        mount.push_back(path);
        mount.push_back(name);
        return mount;
    }
    else if(mbr.p1.type == 'E'){
        extras::Particion P = mbr.p1;
        extras::EBR ebr;
        fseek(archivo, P.start, SEEK_SET);
        fread(&ebr, sizeof (ebr), 1, archivo);
        while(ebr.size > 0){
            if(ebr.name == name){
                mount.push_back(path);
                mount.push_back(name);
                return mount;
            }
            if(ebr.next != -1){
                fseek(archivo, ebr.next, SEEK_SET);
                fread(&ebr, sizeof (ebr), 1, archivo);
            }
            else break;
        }
    }
    else if(mbr.p2.type == 'E'){
        extras::Particion P = mbr.p2;
        extras::EBR ebr;
        fseek(archivo, P.start, SEEK_SET);
        fread(&ebr, sizeof (ebr), 1, archivo);
        while(ebr.size > 0){
            if(ebr.name == name){
                mount.push_back(path);
                mount.push_back(name);
                return mount;
            }
            if(ebr.next != -1){
                fseek(archivo, ebr.next, SEEK_SET);
                fread(&ebr, sizeof (ebr), 1, archivo);
            }
            else break;
        }
    }
    else if(mbr.p3.type == 'E'){
        extras::Particion P = mbr.p3;
        extras::EBR ebr;
        fseek(archivo, P.start, SEEK_SET);
        fread(&ebr, sizeof (ebr), 1, archivo);
        while(ebr.size > 0){
            if(ebr.name == name){
                mount.push_back(path);
                mount.push_back(name);
                return mount;
            }
            if(ebr.next != -1){
                fseek(archivo, ebr.next, SEEK_SET);
                fread(&ebr, sizeof (ebr), 1, archivo);
            }
            else break;
        }
    }
    else if(mbr.p4.type == 'E'){
        extras::Particion P = mbr.p4;
        extras::EBR ebr;
        fseek(archivo, P.start, SEEK_SET);
        fread(&ebr, sizeof (ebr), 1, archivo);
        while(ebr.size > 0){
            if(ebr.name == name){
                mount.push_back(path);
                mount.push_back(name);
                return mount;
            }
            if(ebr.next != -1){
                fseek(archivo, ebr.next, SEEK_SET);
                fread(&ebr, sizeof (ebr), 1, archivo);
            }
            else break;
        }
    }
    cout << "ERROR EN MOUNT!!!" << endl;
    cout << "EL NOMBRE DE LA PARTICION NO EXISTE!!!" << endl;
    return mount;
}
