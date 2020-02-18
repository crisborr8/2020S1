#include "menu_principal.h"

Menu_Principal::Menu_Principal()
{
    string comando, mensajeError = "";
    LlenarVariables();
    while(comando != "exit"){
        comando = "";
        cout << "*************************************************************" << endl;
        cout << "************ MANEJO E IMPLEMENTACIÓN DE ARCHIVOS ************" << endl;
        cout << "************        APLICACIÓN DE COMANDOS       ************" << endl;
        cout << "\nEscriba el comando a utilizar:\n" << endl;
        getline(cin, comando);
        if(comando.length() != 0){
            comando = trim(comando);
            if(toLowerString(comando) != "exit")
                validador(comando);
            else break;
        }
    }
}

//***************************************************************************
//***************************************************************************
//********************************VALIDADORES********************************
void Menu_Principal::validador(string comando){
    dividirComando(comando);
    if(comandos.size() == 0){
        mensajeError = "Formato de comandos incorrecto";
        mostrarMensajeError();
    }
    else{
        cout << "---->" << comandos.at(0) << endl;
        obtenerVectorComandos(comandos.at(0));
        if(vectorComandos.size() == 0){
            mensajeError = "El comando principal no existe";
            mostrarMensajeError();
        }
        else{
            if(!validarSubComandosPermitidos()){
                mostrarMensajeError();
            }
            else{
                if(!validarSubComandosParametros()){
                    mensajeError = "Parametros incorrectos en " + mensajeError;
                    mostrarMensajeError();
                }
                else{
                    if(comandos.at(0) == "mkdisk")
                        mk.comandoMkdisk(comandos);
                    else if(comandos.at(0) == "rmdisk")
                        rm.comandoRmdisk(comandos.at(1));
                    LlenarVariables();
                }
            }
        }
    }
}
void Menu_Principal::dividirComando(string comando){
    if(comandos.size() > 0) comandos.clear();
    string subComando;
    int st = comando.find_first_of(" ");
    if(st <= 0) st = comando.size();
    comandos.push_back(toLowerString(comando.substr(0, st)));
    if(st < static_cast<int>(comando.size())){
        comando = Ltrim(comando.substr(st, comando.size()));
        while(comando != ""){
            if(comando.size() > 3)
                if(comando.substr(0, 3) == "–")
                    comando = "-" + comando.substr(3, comando.size());
            if(comando.size() > 7){
                if(comando.substr(0, 7) == "-path=\"" || comando.substr(0, 7) == "-name=\""){
                    st = comando.find_first_of("\"");
                    if(st <= 0) st = comando.size();
                    subComando = comando.substr(0, st);
                    if(st + 1 < static_cast<int>(comando.size())){
                        comando = comando.substr(st + 1, comando.size());
                        st = comando.find_first_of("\"");
                        if(st <= 0) st = comando.size();
                        subComando += comando.substr(0, st);
                        if(st + 1 < static_cast<int>(comando.size()))
                            comando = Ltrim(comando.substr(st + 1, comando.size()));
                        else comando = "";
                    }
                    else comando = "";
                }
                else{
                    st = comando.find_first_of(" ");
                    if(st <= 0) st = comando.size();
                    subComando = comando.substr(0, st);
                    if(++st < static_cast<int>(comando.size()))
                        comando = Ltrim(comando.substr(st, comando.size()));
                    else
                        comando = "";
                }
            }else{
                st = comando.find_first_of(" ");
                if(st <= 0) st = comando.size();
                subComando = comando.substr(0, st);
                if(++st < static_cast<int>(comando.size()))
                    comando = Ltrim(comando.substr(st, comando.size()));
                else
                    comando = "";
            }
            comandos.push_back(subComando);
        }
    }
}
void Menu_Principal::obtenerVectorComandos(string comando){
    if(vectorComandos.size() > 0) vectorComandos.clear();
     for (vector<string> comandoP: comandosExistentes){
        if(comandoP.at(0) == comando){
            vectorComandos = comandoP;
            break;
        }
     }
}
bool Menu_Principal::validarSubComandosPermitidos(){
    string texto = "", textoComandos = "";
    int j;
    for(int i = 1; i < static_cast<int>(vectorComandos.size()); i++){
        texto = vectorComandos.at(i);
        if(texto.at(0) == '0'){
            for(j = 1; j < static_cast<int>(comandos.size()); j++){
                textoComandos = toLowerString(comandos.at(j));
                if(textoComandos.rfind(texto.substr(1, texto.size()) + "=", 0) == 0)
                    break;
            }
            if(j >= static_cast<int>(comandos.size())){
                mensajeError = "Faltan subcomandos obligatorios: " + texto.substr(1, texto.size());
                return false;
            }
        }
        else
            break;
    }
    for(int i = 1; i < static_cast<int>(comandos.size()); i++){
        textoComandos = toLowerString(comandos.at(i));
        for(j = 1; j < static_cast<int>(vectorComandos.size()); j++){
            texto = vectorComandos.at(j);
            if(textoComandos.rfind(texto.substr(1, texto.size()) + "=", 0) == 0)
                break;
        }
        if(j >= static_cast<int>(vectorComandos.size())){
            mensajeError = "Existen subcomandos no permitidos: " + comandos.at(i);
            return false;
        }
    }
    return true;
}
bool Menu_Principal::validarSubComandosParametros(){
    size_t st;
    string subcomando, parametro;
    for(int i = 1; i < static_cast<int>(comandos.size()); i++){
        st = comandos.at(i).find_first_of("=");
        if(st == comandos.at(i).size()){
            mensajeError = comandos.at(i) + ", no existen parametros";
            return false;
        }
        subcomando = toLowerString(comandos.at(i).substr(0, st));
        parametro = toLowerString(comandos.at(i).substr(st + 1, comandos.at(i).size()));
        if(subcomando == "-size"){
            try {
                if(stoi(parametro) <= 0){
                    mensajeError = comandos.at(i) + ", el parametro debe ser mayor a 0.";
                    return false;
                }
            } catch (exception ex) {
                mensajeError = comandos.at(i) + ", el parametro debe ser tipo numerico.";
                return false;
            }
        } else if(subcomando == "-fit"){
            if(parametro != "bf" && parametro != "ff" && parametro != "wf"){
                mensajeError = comandos.at(i) + ", el parametro debe ser BF, FF o WF.";
                return false;
            }
        } else if(subcomando == "-unit"){
            if(parametro != "b" && parametro != "k"){
                if(comandos.at(0) != "fdisk" || parametro != "m"){
                    mensajeError = comandos.at(i) + ", el parametro debe ser B, K o M.";
                    return false;
                }else{
                    mensajeError = comandos.at(i) + ", el parametro debe ser B o K";
                    return false;
                }
            }
        } else if(subcomando == "-type"){
            if(parametro != "p" && parametro != "e" && parametro != "l"){
                mensajeError = comandos.at(i) + ", el parametro debe P, E o L";
                return false;
            }
        } else if(subcomando == "-delete"){
            if(parametro != "fast" && parametro != "full"){
                mensajeError = comandos.at(i) + ", el parametro debe FAST o FULL";
                return false;
            }

        } else if(subcomando == "-add"){
            try {
                int x = stoi(parametro);
            } catch (exception ex) {
                mensajeError = comandos.at(i) + ", el parametro debe ser tipo numerico.";
                return false;
            }
        } else if(subcomando == "-path"){
            if(parametro.find_last_of(".disk") != parametro.size() - 1){
                mensajeError = subcomando + ", se necesita que path termine en .disk";
                return false;
            }
        } else if(subcomando != "-name" && subcomando != "-id"){
            mensajeError = subcomando + ", el parametro no existe.";
        }
    }
    return true;
}

//***************************************************************************
//***************************************************************************
//***********************************ERROR***********************************
void Menu_Principal::mostrarMensajeError(){
    cout << "*************************************************************" << endl;
    cout << "*************************   ERROR   *************************" << endl;
    cout << mensajeError << endl;
    cout << "*************************************************************\n\n\n" << endl;
    mensajeError = "";
}

//***************************************************************************
//***************************************************************************
//***********************************EXTRAS**********************************
void Menu_Principal::LlenarVariables(){
    vector <string> comandosPermitidos;
    //----------------------MKDISK-------------------
    comandosPermitidos.push_back("mkdisk");
    comandosPermitidos.push_back("0-size");
    comandosPermitidos.push_back("0-path");
    comandosPermitidos.push_back("1-fit");
    comandosPermitidos.push_back("1-unit");
    comandosExistentes.push_back(comandosPermitidos);
    comandosPermitidos.clear();
    //----------------------RMDISK-------------------
    comandosPermitidos.push_back("rmdisk");
    comandosPermitidos.push_back("0-path");
    comandosExistentes.push_back(comandosPermitidos);
    comandosPermitidos.clear();
    //----------------------FDISK-------------------
    comandosPermitidos.push_back("fdisk");
    comandosPermitidos.push_back("0-path");
    comandosPermitidos.push_back("0-name");
    comandosPermitidos.push_back("1-size");
    comandosPermitidos.push_back("1-unit");
    comandosPermitidos.push_back("1-type");
    comandosPermitidos.push_back("1-unit");
    comandosPermitidos.push_back("1-fit");
    comandosPermitidos.push_back("1-delete");
    comandosPermitidos.push_back("1-add");
    comandosExistentes.push_back(comandosPermitidos);
    comandosPermitidos.clear();
    //----------------------MOUNT-------------------
    comandosPermitidos.push_back("mount");
    comandosPermitidos.push_back("0-path");
    comandosPermitidos.push_back("0-name");
    comandosExistentes.push_back(comandosPermitidos);
    comandosPermitidos.clear();
    //----------------------UNMOUNT-------------------
    comandosPermitidos.push_back("unmount");
    comandosPermitidos.push_back("0-id");
    comandosExistentes.push_back(comandosPermitidos);
    comandosPermitidos.clear();
    //----------------------REP-------------------
    comandosPermitidos.push_back("rep");
    comandosPermitidos.push_back("0-id");
    comandosPermitidos.push_back("0-path");
    comandosPermitidos.push_back("0-name");
    comandosExistentes.push_back(comandosPermitidos);
    comandosPermitidos.clear();
    //----------------------SCRIPT-------------------
    comandosPermitidos.push_back("exec");
    comandosPermitidos.push_back("0-path");
    comandosExistentes.push_back(comandosPermitidos);
    comandosPermitidos.clear();
}
char Menu_Principal::toLowerChar(char c){
    if(c <= 'Z' && c >= 'A')
        return c - ('Z' - 'z');
    return c;
}
string Menu_Principal::toLowerString(string s){
    string toLower = "";
    for (char& c: s)
        toLower += toLowerChar(c);
    return toLower;
}
string Menu_Principal::Ltrim(string s){
    int L = s.find_first_not_of(" ");
    return s.substr(L, s.size());
}
string Menu_Principal::Rtrim(string s){
    int R = s.find_last_not_of(" ");
    return s.substr(0, R + 1);
}
string Menu_Principal::trim(string s){
    return Ltrim(Rtrim(s));
}
