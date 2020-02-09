package olc1.practica1;

import java.util.Vector;

public class Analizador {
    
    //**************************************************************************
    //**************************************************************************
    //DECLARACION DE VARIABLES
    private boolean exito;
    int colAct, filAct;
    int colMax, filMax;
    Vector L, D, A, S1, S2;
    Vector<Vector> vExpReg;
    Vector<Vector> vConjunto;
    Vector<Vector> vExpresion;
    String texto, texto_linea, salida, pActual, errores;
    
    //**************************************************************************
    //**************************************************************************
    //CONSTRUCTOR
    Analizador(String texto){
        this.texto = texto;
        Inicializador();
        ER();
    }
    
    //**************************************************************************
    //**************************************************************************
    //EXPRESIONES REGULARES PARA EL ANALISIS
    private void ER(){
        Comentario();
        if(getChar() == '{'){
            colAct++;
            Comentario();
            while (getChar() == 'C' && getChar() != 0){
                colAct++;
                pActual = "C";
                Conjuntos();
                Comentario();
            }
            while (L.contains(getChar()) && getChar() != 0){
                colAct++;
                pActual = Character.toString(getChar());
                ExpReg();
                Comentario();
            }
            Comentario();
            Porcentaje();
            Comentario();
            while (L.contains(getChar()) && getChar() != 0){
                colAct++;
                pActual = Character.toString(getChar());
                LexemaEnt();
                Comentario();
            }
            Comentario();
            if(getChar() == '}'){
                colAct++;
            }
            else setErrorChar(getChar(), '}');
            Comentario();
        }
        else setErrorChar(getChar(), '{');
    }
    
    private void Conjuntos(){
        if(getChar() == 'O'){
            colAct++;
            pActual += "O";
            if(getChar() == 'N'){
                colAct++;
                pActual += "N";
                if(getChar() == 'J'){
                    colAct++;
                    pActual += "J";
                    if(getChar() == ':'){
                        colAct++;
                        pActual = "";
                        Palabra();
                        Vector nuevo = new Vector(1, 1);
                        nuevo.addElement(pActual);
                        vConjunto.addElement(nuevo);
                        pActual = "";
                        if(getChar() == '-'){
                            colAct++;
                            if(getChar() == '>'){
                                colAct++;
                                NotacionConjuntos();
                            }
                            else setErrorChar(getChar(), '>');
                        }
                        else setErrorChar(getChar(), '-');
                    }
                    else if(L.contains(getChar()) || D.contains(getChar()) || getChar() == '.' || getChar() == '_')
                        ExpReg();
                    else setErrorChar(getChar(), ':');
                }
                else ExpReg();
            }
            else ExpReg();
        }
        else ExpReg();
    }
    private void NotacionConjuntos(){
        int inicio, fin;
        if(L.contains(getChar()) || D.contains(getChar()) || A.contains(getChar())){
            inicio = getChar();
            fin = getChar();
            colAct++;
            if(D.contains(getChar())){
                inicio = (inicio*10) + getChar() - 48;
                colAct++;
                while(D.contains(getChar()) && getChar() != 0){
                    inicio = (inicio*10) + getChar() - 48;
                    colAct++;
                }
            }
            if(getChar() == '~'){
                colAct++;
                if(32 <= fin && fin <= 125){
                    if(48 <= fin && fin <= 57){
                        if(D.contains(getChar())){
                            fin = getChar() - 48;
                            colAct++;
                            while(D.contains(getChar()) && getChar() != 0){
                                fin = (fin*10) + (getChar() - 48);
                                colAct++;
                            }
                            for(int i = inicio; i <= fin; i++)
                                vConjunto.lastElement().addElement(i);
                            if(getChar() == ';'){
                                colAct++;
                            }
                            else setErrorChar(getChar(), ';');
                        }
                        else setErrorString(Character.toString(getChar()), "Limite compatible con Dígito");
                    }
                    else if((65 <= inicio && inicio <= 90) || (97 <= inicio && inicio <= 122)){
                        if(L.contains(getChar()) && L.contains((char) inicio)){
                            fin = getChar();
                            colAct++;
                            for(int i = L.indexOf((char) inicio); i <= L.indexOf(fin); i++)
                                vConjunto.lastElement().addElement(L.elementAt(i));
                            if(getChar() == ';'){
                                colAct++;
                            }
                            else setErrorChar(getChar(), ';');
                        }
                        else if(!L.contains(getChar()))
                            setErrorString(Character.toString(getChar()), "Limite compatible con Letra");
                        else
                            setErrorString(Character.toString((char) inicio), "Limite compatible con Letra");
                    }
                    else{
                        if(A.contains(getChar()) && A.contains((char) inicio)){
                            fin = getChar();
                            colAct++;
                            for(int i = A.indexOf((char) inicio); i <= A.indexOf(fin); i++)
                                vConjunto.lastElement().addElement(A.elementAt(i));
                            if(getChar() == ';'){
                                colAct++;
                            }
                            else setErrorChar(getChar(), ';');
                        }
                        else setErrorString(Character.toString(getChar()), "Limite compatible con Símbolo");
                    }
                }
                else setErrorString(Character.toString(getChar()), "Caracter ASCII entre 32 y 125");
            }
            else if(getChar() == ','){
                vConjunto.lastElement().addElement(Character.toString((char) inicio));
                while(getChar() != ';' && getChar() != 0){
                    colAct++;
                    if(L.contains(getChar()) || D.contains(getChar()) || A.contains(getChar())){
                        if(D.contains(getChar())){
                            inicio = getChar() - 48;
                            colAct++;
                            while(D.contains(getChar())){
                                inicio = (inicio*10) + getChar() - 48;
                                colAct++;
                            }
                            vConjunto.lastElement().addElement(inicio);
                        }
                        else vConjunto.lastElement().addElement(Character.toString(getChar()));
                        colAct++;
                        if(getChar() == ',')
                            colAct++;
                        else if(getChar() != ';') 
                            setErrorString(Character.toString(getChar()), "; ó ,");
                    }
                    else setErrorString(Character.toString(getChar()), "Letra, símbolo o dígito");
                }
                colAct++;
            }
            else if(getChar() == ';'){
                vConjunto.lastElement().addElement(Character.toString((char) inicio));
                colAct++;
            }
            else setErrorString(Character.toString(getChar()), ", ; ó ~");
        }
    }
    
    private void ExpReg(){
        while((L.contains(getChar()) || D.contains(getChar()) || getChar() == '.' || getChar() == '_') && getChar() != 0){
            pActual += getChar();
            colAct++;
        }
        if(getChar() == '-'){
            colAct++;
            Vector nuevo = new Vector(1, 1);
            nuevo.addElement(pActual);
            vExpReg.addElement(nuevo);
            if(getChar() == '>'){
                colAct++;
                NotacionExpReg();
                if(getChar() == ';'){
                    colAct++;
                }
                else setErrorChar(getChar(), ';');
            }
            else setErrorChar(getChar(), '>');
        }
        else setErrorChar(getChar(), '-');
    }
    private void NotacionExpReg(){
        if(S1.contains(getChar())){
            vExpReg.lastElement().addElement(Character.toString(getChar()));
            colAct++;
            if(getChar() == '{'){
                colAct++;
                if(L.contains(getChar()) || D.contains(getChar()) || A.contains(getChar())){
                    pActual = "";
                    Palabra();
                    vExpReg.lastElement().addElement(pActual);
                    if(getChar() == '}'){
                        colAct++;
                    }
                    else setErrorChar(getChar(), '}');
                }
                else setErrorString(Character.toString(getChar()), "Letra, Simbolo o Digito");
            }
            else if(getChar() == '"' || getChar() == '“'){
                colAct++;
                if(L.contains(getChar()) || D.contains(getChar()) || A.contains(getChar())){
                    vExpReg.lastElement().addElement(Character.toString(getChar()));
                    colAct++;
                    if(getChar() == '"' || getChar() == '”'){
                        colAct++;
                    }
                    else setErrorChar(getChar(), '"');
                }
                else setErrorString(Character.toString(getChar()), "Letra, Simbolo o Digito");
            }
            else NotacionExpReg();
        }
        else if(S2.contains(getChar())){
            vExpReg.lastElement().addElement(Character.toString(getChar()));
            colAct++;
            if(getChar() == '{'){
                colAct++;
                if(L.contains(getChar()) || D.contains(getChar()) || A.contains(getChar())){
                    pActual = "";
                    Palabra();
                    vExpReg.lastElement().addElement(pActual);
                    if(getChar() == '}'){
                        colAct++;
                    }
                    else setErrorChar(getChar(), '}');
                }
                else setErrorString(Character.toString(getChar()), "Letra, Simbolo o Digito");
            }
            else if(getChar() == '"' || getChar() == '“'){
                colAct++;
                if(L.contains(getChar()) || D.contains(getChar()) || A.contains(getChar())){
                    vExpReg.lastElement().addElement(Character.toString(getChar()));
                    colAct++;
                    if(getChar() == '"' || getChar() == '”'){
                        colAct++;
                    }
                    else setErrorChar(getChar(), '"');
                }
                else setErrorString(Character.toString(getChar()), "Letra, Simbolo o Digito");
            }
            else NotacionExpReg();
            if(getChar() == '{'){
                colAct++;
                if(L.contains(getChar()) || D.contains(getChar()) || A.contains(getChar())){
                    pActual = "";
                    Palabra();
                    vExpReg.lastElement().addElement(pActual);
                    if(getChar() == '}'){
                        colAct++;
                    }
                    else setErrorChar(getChar(), '}');
                }
                else setErrorString(Character.toString(getChar()), "Letra, Simbolo o Digito");
            }
            else if(getChar() == '"' || getChar() == '“'){
                colAct++;
                if(L.contains(getChar()) || D.contains(getChar()) || A.contains(getChar())){
                    vExpReg.lastElement().addElement(Character.toString(getChar()));
                    colAct++;
                    if(getChar() == '"' || getChar() == '”'){
                        colAct++;
                    }
                    else setErrorChar(getChar(), '"');
                }
                else setErrorString(Character.toString(getChar()), "Letra, Simbolo o Digito");
            }
            else NotacionExpReg();
        }
        else if(L.contains(getChar()) || D.contains(getChar()) || A.contains(getChar())){
            if(getChar() == '{'){
                colAct++;
                if(L.contains(getChar()) || D.contains(getChar()) || A.contains(getChar())){
                    pActual = "";
                    Palabra();
                    vExpReg.lastElement().addElement(pActual);
                    if(getChar() == '}'){
                        colAct++;
                    }
                    else setErrorChar(getChar(), '}');
                }
                else setErrorString(Character.toString(getChar()), "Letra, Simbolo o Digito");
            }
            else if(getChar() == '"' || getChar() == '“'){
                colAct++;
                if(L.contains(getChar()) || D.contains(getChar()) || A.contains(getChar())){
                    vExpReg.lastElement().addElement(Character.toString(getChar()));
                    colAct++;
                    if(getChar() == '"' || getChar() == '”'){
                        colAct++;
                    }
                    else setErrorChar(getChar(), '"');
                }
                else setErrorString(Character.toString(getChar()), "Letra, Simbolo o Digito");
            }
            else setErrorString(Character.toString(getChar()), "Letra, Simbolo o Digito");
        }
        else setErrorString(Character.toString(getChar()), "Símbolo");
    }
    
    private void Porcentaje(){
        if(getChar() == '%'){
            colAct++;
            if(getChar() == '%'){
                colAct++;
                Comentario();
                if(getChar() == '%'){
                    colAct++;
                    if(getChar() == '%'){
                        colAct++;
                    }
                    else setErrorChar(getChar(), '%');
                }
                else setErrorChar(getChar(), '%');
            }
            else setErrorChar(getChar(), '%');
        }
        else setErrorChar(getChar(), '%');
    }
    
    private void LexemaEnt(){
        while((L.contains(getChar()) || D.contains(getChar()) || getChar() == '.' || getChar() == '_') && getChar() != 0){
            pActual += getChar();
            colAct++;
        }
        if(getChar() == ':'){
            colAct++;
            Vector nuevo = new Vector(1, 1);
            nuevo.addElement(pActual);
            vExpresion.addElement(nuevo);
            if(getChar() == '"' || getChar() == '“'){
                colAct++;
                pActual = "";
                if(L.contains(getChar()) || D.contains(getChar()) || A.contains(getChar())){
                    pActual = Character.toString(getChar());
                    while((L.contains(getChar()) || D.contains(getChar()) || A.contains(getChar())) && getChar() != 0){
                        pActual += getChar();
                        colAct++;
                    }
                    vExpresion.lastElement().addElement(pActual);
                    if(getChar() == '"' || getChar() == '”'){
                        colAct++;
                        if(getChar() == ';'){
                            colAct++;
                        }
                        else setErrorChar(getChar(), ';');
                    }
                    else setErrorChar(getChar(), '"');
                }
                else setErrorString(Character.toString(getChar()), "Letra, Dígito o Símbolo");
            }
            else setErrorChar(getChar(), '"');
        }
        else setErrorChar(getChar(), ':');
    }
    
    private void Palabra(){
        quitarEspacios();
        if(L.contains(getChar())){
            pActual += getChar();
            colAct++;
            while((L.contains(getChar()) || D.contains(getChar()) || getChar() == '.' || getChar() == '_') && getChar() != 0){
                pActual += getChar();
                colAct++;
            }
        }
    }
    private void Comentario(){
        quitarEspacios();
        if(getChar() == '/'){
            colAct++;
            if(getChar() == '/') {
                filAct++;
                setColMax();
            }
            else setErrorChar(getChar(), '/');
        }
        else if(getChar() == '<'){
            colAct++;
            if(getChar() == '!'){
                boolean finComentario = false;
                while(!finComentario && getChar() != 0){
                    colAct++;
                    if(getChar() == '!'){
                        colAct++;
                        if(getChar() == '>'){
                            colAct++;
                            finComentario = true;
                        }
                    }
                }
            }
            else setErrorChar(getChar(),  '!');
        }
        quitarEspacios();
    }
    
    //**************************************************************************
    //**************************************************************************
    //EXTRAS
    private void Inicializador(){
        exito = true;
        salida = pActual = errores = "";
        
        //FILAS Y COLUMNAS
        filMax = texto.split("\n").length - 1;
        filAct = 0;
        setColMax();
        
        //VECTORES A UTILIZAR
        vExpReg = new Vector<Vector>(0, 1);
        vConjunto = new Vector<Vector>(0, 1);
        vExpresion = new Vector<Vector>(0 , 1);
        L = new Vector(45, 1);
        D = new Vector(10, 1);
        A = new Vector(20, 1);
        S1 = new Vector(3, 1);
        S2 = new Vector(2, 1);
        
        int i;
        //AGREGANDO LETRAS A "L"
        for(i = 97; i <= 122; i++)
            L.addElement((char) i);
        for(i = 65; i <= 90; i++)
            L.addElement((char) i);
        
        //AGREGANDO NUMEROS A "D"
        for(i = 48; i <= 57; i++)
            D.addElement((char) i);
        
        //AGREGANDO CARACTERES A "A"
        for(i = 32; i <= 47; i++)
            A.addElement((char) i);
        for(i = 58; i <= 64; i++)
            A.addElement((char) i);
        for(i = 91; i <= 96; i++)
            A.addElement((char) i);
        for(i = 123; i <= 125; i++)
            A.addElement((char) i);
        
        //AGREGANDO OPERADORES A "S"
        S1.addElement('+');
        S1.addElement('*');
        S1.addElement('?');
        S2.addElement('|');
        S2.addElement('.');
    }
    private void quitarEspacios(){
        boolean sinEspacios = false;
        while(!sinEspacios && getChar() != 0){
            if(colAct <= colMax){
                if(texto_linea.charAt(colAct) == ' ') colAct++;
                else sinEspacios = true;
            }
            else{
                filAct++;
                if(filAct <= filMax) setColMax();
                else sinEspacios = true;
            }
        }
    }
    private void setErrorChar(char c, char e){
        if(getChar() != 0){
            int fl = filAct + 1;
            int cl = colAct + 1;
            salida += "\nError en fila " + fl + ", columna " + cl;
            salida += "\n-->Caracter inesperado: '" + c + "'";
            salida += "\n-->Se esperaba: '" + e + "'";
            colAct++;
            exito = false;
        }
    }
    private void setErrorString(String c, String e){
        if(getChar() != 0){
            int fl = filAct + 1;
            int cl = colAct + 1;
            salida += "\nError en fila " + fl + ", columna " + cl;
            salida += "\n-->Palabra inesperada: '" + c + "'";
            salida += "\n-->Se esperaba: '" + e + "'";
            colAct++;
            exito = false;
        }
    }
    private void setColMax(){
        texto_linea = texto.split("\n")[filAct];
        colMax = texto_linea.length() - 1;
        colAct = 0;
    }
    private char getChar(){
        while(filAct <= filMax){
            while(colAct <= colMax){
                if(texto_linea.charAt(colAct) != ' ')
                    return texto_linea.charAt(colAct);
                else colAct++;
            }
            filAct++;
            if(filAct <= filMax) setColMax();
        }
        return 0;
    }
    
    public boolean getExito(){
        return exito;
    }
    public String getSalida(){
        return salida;
    }
}
