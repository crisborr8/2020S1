#include "mkdisk.h"

void mkdisk::comandoMkdisk(vector<string> comandos)
{
    string path = "", fit = "ff", unit = "m", size, texto;
    string salida = "Creado con exito";
    bool archivoCreado = true;
    for(int i = 1; i < static_cast<int>(comandos.size()); i++){
        texto = comandos.at(i);
        if(toLowerString(texto.substr(0, 6)) == "-path=")
            path = texto.substr(6, texto.size());
        else if(toLowerString(texto.substr(0, 5))  == "-fit=")
            fit = texto.substr(5, texto.size());
        else if(toLowerString(texto.substr(0, 6))  == "-unit=")
            unit = texto.substr(6, texto.size());
        else if(toLowerString(texto.substr(0, 6))  == "-size=")
            size = texto.substr(6, texto.size());
    }
    string path_2 = path.substr(0, path.find_last_of("/"));

    if (mkdir(path_2.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
        if(!(errno == EEXIST)){
            cout << "Error al crear archivo:" << endl;
            archivoCreado = false;
        }

    if(archivoCreado){
        comandos.clear();
        comandos.push_back(path);
        comandos.push_back(fit);
        comandos.push_back(unit);
        comandos.push_back(size);
        if(!escribirBytes(comandos))
            salida = "Error inesperado creando el archivo principal";
        else{
            path = path.substr(0, path.find_last_of(".")) + "_RAID.disk";
            comandos.clear();
            comandos.push_back(path);
            comandos.push_back(fit);
            comandos.push_back(unit);
            comandos.push_back(size);
            if(!escribirBytes(comandos))
                salida ="Error inesperado creando el archivo RAID";
        }
    }
    cout << salida << endl;
}

//***************************************************************************
//***************************************************************************
//***********************************ESCRIBIR BYTES**************************
bool mkdisk::escribirBytes(vector<string> comandos){
    int size = atoi(comandos.at(3).c_str());
    int unit = 1024;
    if(toLowerString(comandos.at(2)) == "k") unit = 1;

    vector<char> archivo(1024, 0);
    ofstream ofs(comandos.at(0), ios::binary | ios::out);
    for(int i = 0; i < size*unit; i++)
        if (!ofs.write(&archivo[0], archivo.size()))
            return false;

    Particion p0;
    p0.status = '0';
    p0.type = '0';
    p0.fit = '0';
    p0.start = 0;
    p0.next = 0;
    p0.size = 0;
    strcpy(p0.name, "0");

    MBR mbr;
    mbr.tamano = size*unit;
    mbr.fecha = time(0);
    mbr.signature = getRandom();
    char* c = const_cast<char*>(comandos.at(1).c_str());
    mbr.fit = toLowerChar(*c);
    mbr.p1 = p0;
    mbr.p2 = p0; //Mkdisk -Size=3000 –unit=K -path=/home/criss/Escritorio/aaa/bb.disk
    mbr.p3 = p0;
    mbr.p4 = p0;


    fstream fs;
    fs.open(comandos.at(0), ios::in | ios::binary | ios::out);
    int correcto = 0;
    while(!fs.eof()){
        int pos = fs.tellg();
        fs.read((char*)this, sizeof(MBR));
        if(fs){
            correcto = 1;
            fs.seekp(pos);
            fs.write((char *) &mbr, sizeof(MBR));
            break;
        }
    }
    fs.close();
    if(correcto == 0) return false;

    //probarBytesEscritos(comandos.at(0));
    return true;
}

//***************************************************************************
//***************************************************************************
//***********************************CREAR DIRECTORIO************************
bool mkdisk::crearDirectorio(string path){
    string comando = "mkdir -p " + path;
    system(comando.c_str());
    struct stat info;
    stat( path.c_str(), &info );
    if(!(info.st_mode & S_IFDIR))
        return false;
    return true;
}

//***************************************************************************
//***************************************************************************
//***********************************EXTRAS**********************************
bool mkdisk::probarBytesEscritos(string path){
    MBR mbr;
    ifstream rf(path, ios::out | ios::binary);
    if(!rf){
        cout << "no se puede abrir" << endl;
        return false;
    }
    rf.read((char*) &mbr, sizeof(MBR));
    rf.close();
    if(!rf.good()){
        cout << "error al leer" << endl;
        return false;
    }

    cout << "--->Tamano    " << mbr.tamano << endl;
    cout << "--->Fecha     " << mbr.fecha << endl;
    cout << "--->Signature " << mbr.signature << endl;
    cout << "--->Fit       " << mbr.fit << endl;

    cout << "--->P1" << endl;
    cout << "     ->Status" << mbr.p1.status << endl;
    cout << "     ->Type  " << mbr.p1.type << endl;
    cout << "     ->Fit   " << mbr.p1.fit << endl;
    cout << "     ->Start " << mbr.p1.start << endl;
    cout << "     ->Next  " << mbr.p1.next << endl;
    cout << "     ->Size  " << mbr.p1.size << endl;
    cout << "     ->Name  " << mbr.p1.name << endl;
    cout << "--->P2" << endl;
    cout << "     ->Status" << mbr.p2.status << endl;
    cout << "     ->Type  " << mbr.p2.type << endl;
    cout << "     ->Fit   " << mbr.p2.fit << endl;
    cout << "     ->Start " << mbr.p2.start << endl;
    cout << "     ->Next  " << mbr.p2.next << endl;
    cout << "     ->Size  " << mbr.p2.size << endl;
    cout << "     ->Name  " << mbr.p2.name << endl;
    cout << "--->P3" << endl;
    cout << "     ->Status" << mbr.p3.status << endl;
    cout << "     ->Type  " << mbr.p3.type << endl;
    cout << "     ->Fit   " << mbr.p3.fit << endl;
    cout << "     ->Start " << mbr.p3.start << endl;
    cout << "     ->Next  " << mbr.p3.next << endl;
    cout << "     ->Size  " << mbr.p3.size << endl;
    cout << "     ->Name  " << mbr.p3.name << endl;
    cout << "--->P4" << endl;
    cout << "     ->Status" << mbr.p4.status << endl;
    cout << "     ->Type  " << mbr.p4.type << endl;
    cout << "     ->Fit   " << mbr.p4.fit << endl;
    cout << "     ->Start " << mbr.p4.start << endl;
    cout << "     ->Next  " << mbr.p4.next << endl;
    cout << "     ->Size  " << mbr.p4.size << endl;
    cout << "     ->Name  " << mbr.p4.name << endl;

    return true;
}
int mkdisk::getRandom(){
    srand(time(0));
    return rand() % 99999 + 1;
}
char mkdisk::toLowerChar(char c){
    if(c <= 'Z' && c >= 'A')
        return c - ('Z' - 'z');
    return c;
}
string mkdisk::toLowerString(string s){
    string toLower = "";
    for (char& c: s)
        toLower += toLowerChar(c);
    return toLower;
}
