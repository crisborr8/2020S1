#include "rmdisk.h"

bool rmdisk::comandoRmdisk(vector<string> c){
    string path = "", e = "", aux;
    for(int i = 1; i < static_cast<int>(c.size()); i++){
        aux = ext.toLowerS(c.at(i));
        aux = aux.substr(0, aux.find_first_of("="));
        if(aux == "-path")
            path = c.at(i).substr(c.at(i).find_first_of("=") + 1, c.at(i).size());
    }
    int i = path.find_first_of("\""), j = path.find_last_of("\"");
    if(j != 0 && j != i) path = path.substr(i + 1, j - 1);
    if(path == ""){
        cout << "ERROR EN RMDISK!!!" << endl;
        cout << "-path= O -path=\"...\" DEBE DE TENER UN PARAMETRO TIPO RUTA" << endl;
        return false;
    }
    FILE *archivo;
    archivo = fopen(path.c_str(), "r");
    if(archivo == NULL){
        cout << "ERROR EN MKDISK!!!" << endl;
        cout << "path NO EXISTE" << endl;
        return false;
    }
    cout << "¿¿¿DESEA ELIMINAR EL ARCHIVO PERMANENTEMENTE???" << endl;
    cout << "    -> Y / N" << endl;
    getline(cin, e);
    if(e == "Y" || e == "y"){
        if(remove(path.c_str()) != 0)
            cout << "Error al eliminar el archivo" << endl;
        else{
            path = path.substr(0, path.find_last_of(".")) + "_RAID.disk";
            if(remove(path.c_str()) != 0)
                cout << "Error al eliminar el RAID del archivo" << endl;
            else
                cout << "Archivos eliminados con exito" << endl;
        }
    }
    return true;
}
