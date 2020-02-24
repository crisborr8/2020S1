#include "rep.h"

bool rep::comandoRep(vector<string> c, vector<vector<string> > particiones){
    string id = "", path = "", name = "",aux;
    for(int i = 1; i < static_cast<int>(c.size()); i++){
        aux = ext.toLowerS(c.at(i));
        aux = aux.substr(0, aux.find_first_of("="));
        if(aux == "-id")
            id = c.at(i).substr(c.at(i).find_first_of("=") + 1, c.at(i).size());
        else if(aux == "-path")
            path = c.at(i).substr(c.at(i).find_first_of("=") + 1, c.at(i).size());
        else if(aux == "-name")
            name = c.at(i).substr(c.at(i).find_first_of("=") + 1, c.at(i).size());
    }
    int i = path.find_first_of("\""), j = path.find_last_of("\"");
    if(j != 0 && j != i) path = path.substr(i + 1, j - 1);
    i = name.find_first_of("\""), j = name.find_last_of("\"");
    if(j != 0 && j != i) name = name.substr(i + 1, j - 1);
    if(path == ""){
        cout << "ERROR EN REP!!!" << endl;
        cout << "-path= O -path=\"...\" DEBE DE TENER UN PARAMETRO TIPO RUTA" << endl;
        return false;
    }
    if(id == ""){
        cout << "ERROR EN REP!!!" << endl;
        cout << "-id= DEBE DE TENER UN PARAMETRO TIPO ID" << endl;
        return false;
    }
    if(name == ""){
        cout << "ERROR EN REP!!!" << endl;
        cout << "-name= O -name=\"...\" DEBE DE TENER UN PARAMETRO NO VACIO" << endl;
        return false;
    }
    if(name != "disk" && name != "mbr"){
        cout << "ERROR EN REP!!!" << endl;
        cout << "-name= O -name=\"...\" DEBE DE SER disk O mbr" << endl;
        return false;
    }
    for(i = 0; i < static_cast<int>(particiones.size()); i++){
        cout << "-->" << particiones.at(i).at(2) << "," << id << "<--" << endl;
        if(ext.toLowerS(id) == ext.toLowerS(particiones.at(i).at(2)))
            break;
    }
    if(i == static_cast<int>(particiones.size())){
        cout << "ERROR EN REP!!!" << endl;
        cout << "id NO EXISTE MONTADO" << endl;
        return false;
    }
    aux = path.substr(0, path.find_last_of("/"));
    if(path == aux)
        aux = "/" + path;
    if (mkdir(aux.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
        if(!(errno == EEXIST))
            return false;
    string codigo = "";
    aux = path.substr(path.find_last_of(".") + 1, path.size());
    if(name == "disk") codigo = nameMbr(particiones.at(i).at(0));
    else  codigo = nameMbr(particiones.at(i).at(0));
    codigo = "digraph G{\n node[shape=plaintext];\n" + codigo + "}";
    string dot = path.substr(0,path.find_last_of(".")) + ".dot";
    ofstream archivo(dot);
    archivo << codigo << endl;
    archivo.close();
    string comando = "dot -T" + aux + " " + dot + " -o " + path;
    system(comando.c_str());
    system(("xdg-open " + path).c_str());
    return true;
}

string rep::nameMbr(string path){
    FILE *archivo;
    extras::MBR mbr;
    extras::Particion P;
    extras::EBR ebr;
    archivo = fopen(path.c_str(), "r");
    if(archivo == NULL) return "NULL";
    fread(&mbr, sizeof (mbr), 1, archivo);
    time_t tiempo = mbr.fecha;
    struct tm* timeinfo;
    timeinfo = localtime(&tiempo);
    string codigoMBR = "tabla [label=<<table><tr><td>Nombre</td><td>Valor</td></tr>\n";
    string codigoEBR = "";
    codigoMBR += "<tr><td>mbr_tamaño</td><td>" + to_string(mbr.tamano) + "</td></tr>\n";
    codigoMBR += "<tr><td>mbr_fecha_creacion</td><td>" + string(asctime(timeinfo)) + "</td></tr>\n";
    codigoMBR += "<tr><td>mbr_disk_signature</td><td>" + to_string(mbr.signature) + "</td></tr>\n";
    codigoMBR += "<tr><td>Disk_fit</td><td>" + ext.c_toStringC(mbr.fit) + "</td></tr>\n";
    if(mbr.p1.size > 0){
        P = mbr.p1;
        codigoMBR += "<tr><td>part_status_1</td><td>" + ext.c_toStringC(P.status) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_type_1</td><td>" + ext.c_toStringC(P.type) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_fit_1</td><td>" + ext.c_toStringC(P.fit) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_start_1</td><td>" + to_string(P.start) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_size_1</td><td>" + to_string(P.size) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_name_1</td><td>" + ext.c_toString(P.name) + "</td></tr>\n";
        if(P.type == 'E'){
            int contEBR = 1;
            fseek(archivo, P.start, SEEK_SET);
            fread(&ebr, sizeof (ebr), 1, archivo);
            while(ebr.size > 0){
                codigoEBR += "EBR_" + to_string(contEBR) + " [label=<<table><tr><td>Nombre</td><td>Valor</td></tr>\n";
                codigoEBR += "<tr><td>part_status_1</td><td>" + ext.c_toStringC(ebr.status) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_fit_1</td><td>" + ext.c_toStringC(ebr.fit) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_start_1</td><td>" + to_string(ebr.start) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_size_1</td><td>" + to_string(ebr.size) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_next_1</td><td>" + to_string(ebr.next) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_name_1</td><td>" + ext.c_toString(ebr.name) + "</td></tr>\n";
                codigoEBR += "</table>>];\n";
                contEBR++;
                if(ebr.next != -1){
                    fseek(archivo, ebr.next, SEEK_SET);
                    fread(&ebr, sizeof (ebr), 1, archivo);
                }
                else break;
            }
        }
    }
    if(mbr.p2.size > 0){
        P = mbr.p2;
        codigoMBR += "<tr><td>part_status_2</td><td>" + ext.c_toStringC(P.status) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_type_2</td><td>" + ext.c_toStringC(P.type) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_fit_2</td><td>" + ext.c_toStringC(P.fit) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_start_2</td><td>" + to_string(P.start) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_size_2</td><td>" + to_string(P.size) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_name_2</td><td>" + ext.c_toString(P.name) + "</td></tr>\n";
        if(P.type == 'E'){
            int contEBR = 1;
            fseek(archivo, P.start, SEEK_SET);
            fread(&ebr, sizeof (ebr), 1, archivo);
            while(ebr.size > 0){
                codigoEBR += "EBR_" + to_string(contEBR) + " [label=<<table><tr><td>Nombre</td><td>Valor</td></tr>\n";
                codigoEBR += "<tr><td>part_status_1</td><td>" + ext.c_toStringC(ebr.status) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_fit_1</td><td>" + ext.c_toStringC(ebr.fit) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_start_1</td><td>" + to_string(ebr.start) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_size_1</td><td>" + to_string(ebr.size) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_next_1</td><td>" + to_string(ebr.next) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_name_1</td><td>" + ext.c_toString(ebr.name) + "</td></tr>\n";
                codigoEBR += "</table>>];\n";
                contEBR++;
                if(ebr.next != -1){
                    fseek(archivo, ebr.next, SEEK_SET);
                    fread(&ebr, sizeof (ebr), 1, archivo);
                }
                else break;
            }
        }
    }if(mbr.p3.size > 0){
        P = mbr.p3;
        codigoMBR += "<tr><td>part_status_3</td><td>" + ext.c_toStringC(P.status) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_type_3</td><td>" + ext.c_toStringC(P.type) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_fit_3</td><td>" + ext.c_toStringC(P.fit) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_start_3</td><td>" + to_string(P.start) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_size_3</td><td>" + to_string(P.size) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_name_3</td><td>" + ext.c_toString(P.name) + "</td></tr>\n";
        if(P.type == 'E'){
            int contEBR = 1;
            fseek(archivo, P.start, SEEK_SET);
            fread(&ebr, sizeof (ebr), 1, archivo);
            while(ebr.size > 0){
                codigoEBR += "EBR_" + to_string(contEBR) + " [label=<<table><tr><td>Nombre</td><td>Valor</td></tr>\n";
                codigoEBR += "<tr><td>part_status_1</td><td>" + ext.c_toStringC(ebr.status) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_fit_1</td><td>" + ext.c_toStringC(ebr.fit) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_start_1</td><td>" + to_string(ebr.start) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_size_1</td><td>" + to_string(ebr.size) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_next_1</td><td>" + to_string(ebr.next) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_name_1</td><td>" + ext.c_toString(ebr.name) + "</td></tr>\n";
                codigoEBR += "</table>>];\n";
                contEBR++;
                if(ebr.next != -1){
                    fseek(archivo, ebr.next, SEEK_SET);
                    fread(&ebr, sizeof (ebr), 1, archivo);
                }
                else break;
            }
        }
    }if(mbr.p4.size > 0){
        P = mbr.p4;
        codigoMBR += "<tr><td>part_status_4</td><td>" + ext.c_toStringC(P.status) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_type_4</td><td>" + ext.c_toStringC(P.type) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_fit_4</td><td>" + ext.c_toStringC(P.fit) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_start_4</td><td>" + to_string(P.start) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_size_4</td><td>" + to_string(P.size) + "</td></tr>\n";
        codigoMBR += "<tr><td>part_name_4</td><td>" + ext.c_toString(P.name) + "</td></tr>\n";
        if(P.type == 'E'){
            int contEBR = 1;
            fseek(archivo, P.start, SEEK_SET);
            fread(&ebr, sizeof (ebr), 1, archivo);
            while(ebr.size > 0){
                codigoEBR += "EBR_" + to_string(contEBR) + " [label=<<table><tr><td>Nombre</td><td>Valor</td></tr>\n";
                codigoEBR += "<tr><td>part_status_1</td><td>" + ext.c_toStringC(ebr.status) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_fit_1</td><td>" + ext.c_toStringC(ebr.fit) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_start_1</td><td>" + to_string(ebr.start) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_size_1</td><td>" + to_string(ebr.size) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_next_1</td><td>" + to_string(ebr.next) + "</td></tr>\n";
                codigoEBR += "<tr><td>part_name_1</td><td>" + ext.c_toString(ebr.name) + "</td></tr>\n";
                codigoEBR += "</table>>];\n";
                contEBR++;
                if(ebr.next != -1){
                    fseek(archivo, ebr.next, SEEK_SET);
                    fread(&ebr, sizeof (ebr), 1, archivo);
                }
                else break;
            }
        }
    }
    codigoMBR += "</table>>];\n";
    return codigoMBR + codigoEBR;
}

string rep::nameDisk(string path){
    string codigo = "";
    return codigo;
}
