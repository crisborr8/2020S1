#include "rmdisk.h"

void rmdisk::comandoRmdisk(string path){
    path = path.substr(path.find_first_of("=") + 1, path.size());
    string path_ = path.substr(0, path.find_last_of(".")) + "_RAID.disk";
    if (FILE *file = fopen(path.c_str(), "r")) {
        fclose(file);
        cout << "¿Deseas eliminar el archivo? Y/N" << endl;
        string e;
        getline(cin, e);
        if(e == "Y" || e == "y"){
            if(remove(path.c_str()) != 0)
                cout << "Error al eliminar el archivo" << endl;
            else{
                if(remove(path_.c_str()) != 0)
                    cout << "Error al eliminar el RAID del archivo" << endl;
                else
                    cout << "Archivos eliminados con exito" << endl;
            }
        }
    } else
        cout << "Error, el archivo no existe" << endl;
}
