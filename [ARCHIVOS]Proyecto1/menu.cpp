#include "menu.h"

Menu::Menu()
{
    particionesMontadas.clear();
    while(comando != "exit"){
        cout << "*************************************************************" << endl;
        cout << "************ MANEJO E IMPLEMENTACIÓN DE ARCHIVOS ************" << endl;
        cout << "************        APLICACIÓN DE COMANDOS       ************" << endl;
        cout << "\nEscriba el comando a utilizar:\n" << endl;
        getline(cin, comando);
        comando = ext.trim(comando);
        if(ext.toLowerS(comando) != "exit"){
            setVectorComandosIngresados();
            if(verificarComandosIngresados())
                ingresarComandos();
            else cout << "ERROR! SE HAN INGRESADO COMANDOS INCORRECTOS\n" << comando <<endl;
        }
        else break;
    }
}

void Menu::ingresarComandos(){
    if(comandosIngresados.at(0) == "mkdisk")
        mk.comandoMkdisk(comandosIngresados);
    else if(comandosIngresados.at(0) == "rmdisk")
        rm.comandoRmdisk(comandosIngresados);
    else if(comandosIngresados.at(0) == "fdisk")
        fd.comandoFdisk(comandosIngresados);
    else if(comandosIngresados.at(0) == "mount"){
        vector<string> vector = mt.comandoMount(comandosIngresados);
        if(vector.size() != 0){
            char letra = 'a';
            int numero = 1;
            for(int i = 0; i < static_cast<int>(particionesMontadas.size()); i++){
                if(vector.at(1) == particionesMontadas.at(i).at(1))
                    letra++;
                if(vector.at(0) == particionesMontadas.at(i).at(0))
                    numero++;
            }
            vector.push_back("VD" + string(1, letra) + to_string(numero));
            particionesMontadas.push_back(vector);
            cout << "PARTICION MONTADA CON EXITO" << endl;
        }
    }
    else if(comandosIngresados.at(0) == "unmount"){
        int i = um.comandoUnmount(particionesMontadas, comandosIngresados.at(1));
        if(i > -1){
            particionesMontadas.erase(particionesMontadas.begin()+i);
            cout << "PARTICION DESMONTADA CON EXITO!!!" << endl;
        }
    }
    else if(comandosIngresados.at(0) == "rep")
        rp.comandoRep(comandosIngresados, particionesMontadas);
    for(int i = 0; i < static_cast<int>(particionesMontadas.size()); i++)
        cout << "---->" << particionesMontadas.at(i).at(2) << endl;
}

void Menu::setVectorComandosIngresados(){
    comandosIngresados.clear();
    while(comando.size() > 0){
        if(comando.size() > 3){
            if(comando.substr(0, 3) == "–")
                comando = "-" + comando.substr(3, comando.size());
            s = comando.substr(0, comando.find_first_of(" "));
            if(s.size() < comando.size())
                comando = comando.substr(comando.find_first_of(" "), comando.size());
            else comando = "";
            if(s.size() >= 7){
                if(s.substr(0, 7) == "-path=\"" || s.substr(0, 7) == "-name=\""){
                    if(s.find_last_of("\"") != s.size() - 1){
                        if(comando.find_last_of("\"") > comando.size()){
                            s = "-path=\"... ";
                            comando = "";
                        }
                        else{
                            s += comando.substr(0, comando.find_first_of("\"") + 1);
                            if(comando.find_first_of("\"") < comando.size() - 1)
                                comando = comando.substr(comando.find_first_of("\"") + 1, comando.size());
                            else comando = "";
                        }
                    }
                }
            }
            comandosIngresados.push_back(s);
            comando = ext.trimL(comando);
        }
        else {
            comandosIngresados.push_back(comando);
            break;
        }
    }
}
bool Menu::verificarComandosIngresados(){
    comando = "NO EXISTE EL NUMERO DE COMANDOS NECESARIO PARA FUNCIONAR";
    if(comandosIngresados.size() < 2) return false;
    int i, j;
    setVectorComandosPermitidos();
    comandosIngresados.at(0) = ext.toLowerS(comandosIngresados.at(0));
    for(i = 0; i < static_cast<int>(comandosPermitidos.size()); i++){
        comandosPermitidosLinea = comandosPermitidos.at(i);
        if(comandosIngresados.at(0) == comandosPermitidosLinea.at(0))
            break;
    }
    if(i == static_cast<int>(comandosPermitidos.size())){
        comando = "NO EXISTE UN COMANDO PRINCIPAL";
        return false;
    }
    for(i = 1; i < static_cast<int>(comandosIngresados.size()); i++){
        comando = ext.toLowerS(comandosIngresados.at(i));
        for(j = 1; j < static_cast<int>(comandosPermitidosLinea.size()); j++)
            if(comando.substr(0, comandosPermitidosLinea.at(j).size()) == comandosPermitidosLinea.at(j))
                break;
        if(j == static_cast<int>(comandosPermitidosLinea.size())){
            comando = comandosIngresados.at(i) + " NO ES UN COMANDO PERMITIDO";
            return false;
        }
    }
    return true;
}

void Menu::setVectorComandosPermitidos(){
    comandosPermitidos.clear();
    comandosPermitidosLinea.clear();
    comandosPermitidosLinea.push_back("mkdisk");
    comandosPermitidosLinea.push_back("-size=");
    comandosPermitidosLinea.push_back("-path=");
    comandosPermitidosLinea.push_back("-fit=");
    comandosPermitidosLinea.push_back("-unit=");
    comandosPermitidos.push_back(comandosPermitidosLinea);
    comandosPermitidosLinea.clear();
    comandosPermitidosLinea.push_back("rmdisk");
    comandosPermitidosLinea.push_back("-path=");
    comandosPermitidos.push_back(comandosPermitidosLinea);
    comandosPermitidosLinea.clear();
    comandosPermitidosLinea.push_back("fdisk");
    comandosPermitidosLinea.push_back("-path=");
    comandosPermitidosLinea.push_back("-size=");
    comandosPermitidosLinea.push_back("-unit=");
    comandosPermitidosLinea.push_back("-type=");
    comandosPermitidosLinea.push_back("-fit=");
    comandosPermitidosLinea.push_back("-delete=");
    comandosPermitidosLinea.push_back("-name=");
    comandosPermitidosLinea.push_back("-add=");
    comandosPermitidos.push_back(comandosPermitidosLinea);
    comandosPermitidosLinea.clear();
    comandosPermitidosLinea.push_back("mount");
    comandosPermitidosLinea.push_back("-path=");
    comandosPermitidosLinea.push_back("-name=");
    comandosPermitidos.push_back(comandosPermitidosLinea);
    comandosPermitidosLinea.clear();
    comandosPermitidosLinea.push_back("unmount");
    comandosPermitidosLinea.push_back("-id=");
    comandosPermitidos.push_back(comandosPermitidosLinea);
    comandosPermitidosLinea.clear();
    comandosPermitidosLinea.push_back("rep");
    comandosPermitidosLinea.push_back("-path=");
    comandosPermitidosLinea.push_back("-name=");
    comandosPermitidosLinea.push_back("-id=");
    comandosPermitidos.push_back(comandosPermitidosLinea);
    comandosPermitidosLinea.clear();
    comandosPermitidosLinea.push_back("exec");
    comandosPermitidosLinea.push_back("-path=");
    comandosPermitidos.push_back(comandosPermitidosLinea);
    comandosPermitidosLinea.clear();
}
