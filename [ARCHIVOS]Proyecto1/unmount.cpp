#include "unmount.h"

int unmount::comandoUnmount(vector<vector<string> > particiones, string id){
    string aux, id_s = "";
    int id_i = -1, i;
    aux = ext.toLowerS(id);
    aux = aux.substr(0, aux.find_first_of("="));
    if(aux == "-id")
        id_s = id.substr(id.find_first_of("=") + 1, id.size());
    if(id_s == ""){
        cout << "ERROR EN ID!!!" << endl;
        cout << "-id DEBE DE TENER UN PARAMETRO TIPO ID -> VD+LETRA+NUMERO" << endl;
        return id_i;
    }
    for(i = 0; i < static_cast<int>(particiones.size()); i++){
        if(id_s == ext.toLowerS(particiones.at(i).at(2))){
            id_i = i;
            break;
        }
    }
    return id_i;
}
