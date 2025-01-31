﻿using System;
using System.Collections.Generic;

namespace P1
{
    class Analizador
    {
        //**************************************************************************
        //**************************************************************************
        //DECLARACION DE VARIABLES
        private bool expresion, op1, op2;
        private string[] texto;
        private char[] textoLinea, c;
        private int colAct, colIni, filAct;
        public int filER;
        private List<string> nuevo;
        public List<List<string>> vExpReg;
        public List<List<string>> vConjunto;
        public List<List<string>> vExpresion;
        public string pActual, repErrores, xmlErrores, xmlTokens;
        public bool correcto;

        //**************************************************************************
        //**************************************************************************
        //CONSTRUCTOR
        public void Analizar(string t)
        {
            inicializarVariables(t);
            ER();
            repErrores += "</table></body></html>";
            xmlErrores += "</ListaErrores>";
            xmlTokens += "</ListaTokens>";
        }

        private void ER()
        {
            Comentario();
            while(getChar() != '\0' && getChar() == 'C')
            {
                pActual += 'C';
                colAct++;
                CONJ();
                Comentario();
            }
            while (getChar() != '\0' && char.IsLetter(getChar()))
            {
                pActual = getCharLS().ToString();
                colAct++;
                ExpReg();
                Comentario();
            }
            Comentario();
        }
        //CONJUNTOS
        private void CONJ()
        {
            if (getCharLC() == 'O')
            {
                pActual += getCharLC();
                colAct++;
                if (getCharLC() == 'N')
                {
                    pActual += getCharLC();
                    colAct++;
                    if (getCharLC() == 'J')
                    {
                        colAct++;
                        if (getCharLS() == ':')
                        {
                            colAct--;
                            pActual = "CONJ";
                            setToken("TOKEN CONJ");
                            colAct++;
                            pActual = ":";
                            setToken("TOKEN DOS PUNTOS");
                            colAct++;
                            if (Palabra(' ','-'))
                            {
                                nuevo = new List<string>();
                                nuevo.Add(pActual);
                                setToken("TOKEN CONJUNTO");
                                if (getCharLS() == '-')
                                {
                                    pActual += getCharLC();
                                    colAct++;
                                    if (getCharLS() == '>')
                                    {
                                        pActual += getCharLC();
                                        setToken("TOKEN FLECHA");
                                        colAct++;
                                        if (CONJ_Parametros())
                                        {
                                            pActual = ";";
                                            setToken("PUNTO Y COMA");
                                            vConjunto.Add(nuevo);
                                            colAct++;
                                        }
                                        else setErrores();
                                    }
                                    else setErrores();
                                }
                                else setErrores();
                            }
                            else setErrores();
                        }
                        else ExpReg();
                    }
                    else ExpReg();
                }
                else ExpReg();
            }
            else ExpReg();
        }
        private bool CONJ_Parametros()
        {
            if (32 <= getCharLC() && getCharLC() <= 125)
            {
                pActual = getCharLS().ToString();
                colAct++;
                while (getCharLS() != '~' && getCharLS() != ',' && getCharLS() != ';')
                {
                    pActual += getCharLS();
                    colAct++;
                    if (getCharLS() == '\0') return false;
                }
                if (getCharLC() == '~')
                {
                    colAct++;
                    nuevo.Add("~");
                    nuevo.Add(pActual);
                    if (32 <= getCharLC() && getCharLC() <= 125)
                    {
                        pActual = "";
                        if (esNum(nuevo[2]))
                        {
                            while (48 <= getCharLC() && getCharLC() <= 57)
                            {
                                pActual += getCharLC();
                                colAct++;
                                if (getCharLC() == '\0') return false;
                                if (getCharLC() == ';') break;
                                if (!(48 <= getCharLC() && getCharLC() <= 57))
                                {
                                    pActual = "";
                                    break;
                                }
                            }
                            if (pActual == "") return false;
                        }
                        else
                        {
                            if ((65 <= nuevo[2].ToCharArray()[0] && nuevo[2].ToCharArray()[0] <= 90)
                                || (97 <= nuevo[2].ToCharArray()[0] && nuevo[2].ToCharArray()[0] <= 122))
                            {
                                if (!(65 <= getCharLC() && getCharLC() <= 90) && !(97 <= getCharLC() && getCharLC() <= 122))
                                    return false;
                            }
                            else if ((65 <= getCharLC() && getCharLC() <= 90) || (97 <= getCharLC() && getCharLC() <= 122)
                                    || (48 <= getCharLC() && getCharLC() <= 57))
                                return false;
                            pActual += getCharLC();
                            colAct++;
                            if (getCharLC() != ';') return false;
                        }
                        nuevo.Add(pActual);
                        return true;
                    }
                    else return false;
                }
                else if (getCharLC() == ',')
                {
                    colAct++;
                    nuevo.Add(",");
                    nuevo.Add(pActual);
                    while (32 <= getCharLC() && getCharLC() <= 125)
                    {
                        if (getCharLC() == ';') return true;
                        pActual = getCharLC().ToString();
                        colAct++;
                        if (getCharLC() == '\0') return false;
                        while (getCharLC() != ',' && getCharLC() != ';')
                        {
                            pActual += getCharLC();
                            colAct++;
                            if (getCharLC() == '\0') return false;
                        }
                        if (getCharLC() == ',') colAct++;
                        nuevo.Add(pActual);
                    }
                    return false;
                }
                else if (getCharLC() == ';')
                {
                    nuevo.Add("");
                    nuevo.Add(pActual);
                    return true;
                }
                else return false;
            }
            else return false;
        }
        private bool esNum(string s)
        {
            try { int n = int.Parse(s); }
            catch (Exception e) { return false; }
            return true;
        }
        //EXPRESIONES REGULARES
        private void ExpReg()
        {
            while(getCharLC() != ' ' && getCharLC() != '-' && getCharLC() != ':' && getCharLC() != '\0')
            {
                pActual += getCharLC();
                colAct++;
            }
            if (getCharLS() == '-' || getCharLS() == ':')
            {
                nuevo = new List<string>();
                nuevo.Add(pActual);
                setToken("EXPRESION REGULAR");
                if (getCharLC() == '-' && expresion == false)
                {
                    pActual += getCharLC();
                    colAct++;
                    if (getCharLC() == '>')
                    {
                        pActual += getCharLC();
                        setToken("TOKEN FLECHA");
                        colAct++;
                        if (ExpReg_Parametros())
                        {
                            pActual = ";";
                            setToken("PUNTO Y COMA");
                            vExpReg.Add(nuevo);
                            colAct++;
                        }
                        else setErrores();
                    }
                    else setErrores();
                }
                else if(getCharLC() == ':')
                {
                    expresion = true;
                    pActual += getCharLC();
                    setToken("TOKEN DOS PUNTOS");
                    colAct++;
                    if (Expresion_Parametros())
                    {
                        pActual = ";";
                        setToken("PUNTO Y COMA");
                        vExpresion.Add(nuevo);
                        if (filER == -1) filER = filAct;
                        colAct++;
                    }
                    else setErrores();
                }
                else setErrores();
            }
            else setErrores();
        }
        private bool ExpReg_Parametros()
        {
            if(getCharLS() == '*' || getCharLS() == '+' || getCharLS() == '?')
            {
                pActual += getCharLS();
                nuevo.Add(pActual);
                setToken("OPERADOR UNIARIO");
                colAct++;
                return ExpReg_Parametros();
            }
            else if(getCharLS() == '|' || getCharLS() == '.')
            {
                pActual += getCharLS();
                nuevo.Add(pActual);
                setToken("OPERADOR BINARIO");
                colAct++;
                op1 = ExpReg_Parametros();
                op2 = ExpReg_Parametros();
                if (op1 == op2 == true) return true;
                else return false;
            }
            else if(getCharLS() == '{')
            {
                setToken("LLAVE INICIO");
                colAct++;
                do
                {
                    if (getCharLC() == '\0')
                    {
                        setErrores();
                        return false;
                    }
                    pActual += getCharLC();
                    colAct++;
                } while (getCharLC() != '}');
                nuevo.Add("{" + pActual);
                pActual = "}";
                setToken("LLAVE FIN");
                colAct++;
                return true;
            }
            else if(getCharLS() == '"' || getCharLS() == '“')
            {
                setToken("COMILLAS INICIO");
                colAct++;
                do
                {
                    if (getCharLC() == '\0')
                    {
                        setErrores();
                        return false;
                    }
                    pActual += getCharLC();
                    colAct++;
                } while (getCharLC() != '"' && getCharLC() != '”');
                nuevo.Add("\''" + pActual);
                pActual = "\"";
                setToken("COMILLAS FIN");
                colAct++;
                return true;
            }
            else if(getCharLS() == '\\')
            {
                pActual = "\\";
                colAct++;
                if(getCharLC() == 'n')
                {
                    pActual += getCharLC();
                    nuevo.Add(pActual);
                    setToken("Salto de linea");
                    colAct++;
                    return true;
                }
                else if (getCharLC() == '\'')
                {
                    pActual += getCharLC();
                    nuevo.Add("\\" + getCharLC());
                    setToken("Comilla simple");
                    colAct++;
                    return true;
                }
                else if (getCharLC() == '"' || getCharLC() == '“' || getCharLC() == '”')
                {
                    pActual += getCharLC();
                    nuevo.Add("\\" + pActual);
                    setToken("Comilla doble");
                    colAct++;
                    return true;
                }
                else if (getCharLC() == 't')
                {
                    pActual += getCharLC();
                    nuevo.Add(pActual);
                    setToken("Tabulacion");
                    colAct++;
                    return true;
                }
                else
                {
                    setErrores();
                    return false;
                }
            }
            else if(getCharLS() == '[')
            {
                pActual = "[";
                colAct++;
                if (getCharLC() == ':')
                {
                    pActual += getCharLC();
                    colAct++;
                    if (getCharLC() == 't')
                    {
                        pActual += getCharLC();
                        colAct++;
                        if (getCharLC() == 'o')
                        {
                            pActual += getCharLC();
                            colAct++;
                            if (getCharLC() == 'd')
                            {
                                pActual += getCharLC();
                                colAct++;
                                if (getCharLC() == 'o')
                                {
                                    pActual += getCharLC();
                                    colAct++;
                                    if (getCharLC() == ':')
                                    {
                                        pActual += getCharLC();
                                        colAct++;
                                        if (getCharLC() == ']')
                                        {
                                            pActual += getCharLC();
                                            nuevo.Add(pActual);
                                            setToken("CONJUNTO TOTAL");
                                            colAct++;
                                            return true;
                                        }
                                        else setErrores();
                                    }
                                    else setErrores();
                                }
                                else setErrores();
                            }
                            else setErrores();
                        }
                        else setErrores();
                    }
                    else setErrores();
                }
                else setErrores();
                return false;
            }
            else return false;
        }
        //EJEMPLOS DE EXPRESIONES REGULARES
        private bool Expresion_Parametros()
        {
            if(getCharLS() == '"' || getCharLS() == '“')
            {
                pActual += getCharLS();
                setToken("TOKEN COMILLAS INICIO");
                colAct++;
                while(getChar() != '\0')
                {
                    while (getCharLC() != '\0' && filAct < texto.Length)
                    {
                        if (getCharLC() == '"')
                        {
                            colAct++;
                            if (getCharLC() == ';')
                            {
                                nuevo.Add(pActual);
                                pActual = "\"";
                                colAct--;
                                setToken("TOKEN COMILLAS FIN");
                                colAct++;
                                return true;
                            }
                            else pActual += '"';
                        }
                        pActual += getCharLC();
                        colAct++;
                    }
                    pActual += "\n";
                }
            }
            return false;
        }
        //PALABRAS Y COMENTARIOS
        private bool Palabra(char caracter1, char caracter2)
        {
            pActual = "";
            if (char.IsLetter(getCharLS()))
            {
                while (getCharLC() != caracter1 && getCharLC() != caracter2)
                {
                    pActual += getCharLC();
                    if (getCharLC() != '\0') colAct++;
                    else return false;
                }
                return true;
            }
            return false;
        }
        private void Comentario()
        {
            while (getChar() != '\0' && (getChar() == '/' || getChar() == '<'))
            {
                colIni = colAct;
                if (getCharLS() == '/')
                {
                    pActual += getCharLS();
                    colAct++;
                    if (getCharLC() == '/')
                    {
                        pActual += getCharLS();
                        setToken("COMENTARIO LINEA");
                        nuevaFila();
                    }
                    else setErrores();
                }
                else if (getCharLS() == '<')
                {
                    pActual += getCharLS();
                    colAct++;
                    if (getCharLC() == '!')
                    {
                        pActual += getCharLS();
                        setToken("COMENTARIO PARRAFO (INICIO)");
                        while(getChar() != '\0')
                        {
                            if (getCharLS() == '!')
                            {
                                colAct++;
                                if (getCharLC() == '>')
                                {
                                    pActual = "!>";
                                    setToken("COMENTARIO PARRAFO (FIN)");
                                    colAct++;
                                    break;
                                }
                            }
                            else colAct++;
                        }
                    }
                    else setErrores();
                }
                else setErrores();
            }
        }
        //**************************************************************************
        //**************************************************************************
        //XML Y REPORTE
        private void setErrores()
        {
            correcto = false;
            while(getCharLC() != '\0' && getCharLC() != ' ')
            {
                pActual += getCharLC();
                colAct++;
            }
            colIni = colAct - pActual.Length + 1;
            reescribirPActual();
            xmlErrores += "<Error>\n" +
                          "       <Valor>" + pActual + "</Valor>\n" +
                          "       <Fila>" + (filAct + 1) + "</Fila>\n" +
                          "       <Columna>" + (colIni + 1) + "</Columna>\n" +
                          "</Error>\n";
            repErrores += "   <tr><th>" + (colIni + 1) + "</th>\n" +
                          "   <th>" + (filAct + 1) + "</th>\n" +
                          "   <th>" + pActual + "</th></tr>\n";
            pActual = "";
        }
        private void setToken(string nombre)
        {
            colIni = colAct - pActual.Length + 1;
            reescribirPActual();
            xmlTokens += "<Token>\n" +
                         "       <Nombre>" + nombre + "</Nombre>\n" +
                         "       <Valor>" + pActual + "</Valor>\n" +
                         "       <Fila>" + (filAct + 1) + "</Fila>\n" +
                         "       <Columna>" + (colIni + 1) + "</Columna>\n" +
                         "</Token>\n";
            pActual = "";
        }
        private void reescribirPActual()
        {
            c = pActual.ToCharArray();
            pActual = "";
            foreach(char i in c)
            {
                if (i == '<') pActual += "&#60;";
                else if (i == '>') pActual += "&#62;";
                else pActual += i;
            }
        }

        //**************************************************************************
        //**************************************************************************
        //CARACTERES CON SALTO
        private char getChar()
        {
            while(filAct < texto.Length)
            {
                while (colAct < textoLinea.Length)
                {
                    if (textoLinea[colAct] != ' ') return textoLinea[colAct];
                    colAct++;
                }
                nuevaFila();
            }
            return '\0';
        }
        //CARACTERES LINEA SIN ESPACIO
        private char getCharLS()
        {
            if (filAct < texto.Length)
            {
                while (colAct < textoLinea.Length)
                {
                    if (textoLinea[colAct] != ' ') return textoLinea[colAct];
                    colAct++;
                }
                nuevaFila();
            }
            return '\0';
        }
        //CARACTERES LINEA CON ESPACIO
        private char getCharLC()
        {
            if (filAct < texto.Length)
            {
                if (colAct < textoLinea.Length) return textoLinea[colAct];
                nuevaFila();
            }
            return '\0';
        }
        //NUEVAS FILAS
        private void nuevaFila()
        {
            filAct++;
            if (filAct < texto.Length)
            {
                textoLinea = texto[filAct].ToCharArray();
                if (textoLinea.Length == 0) nuevaFila();
                else colAct = 0;
            }
        }

        //**************************************************************************
        //**************************************************************************
        //INICIALIZAR VARIABLES
        private void inicializarVariables(string t)
        {
            expresion = false;
            correcto = true;
            colAct = filAct = 0;
            filER = -1;
            texto = t.Split('\n');
            pActual = "";
            if (texto.Length != 0) textoLinea = texto[0].ToCharArray();

            vExpReg = new List<List<string>>();
            vConjunto = new List<List<string>>();
            vExpresion = new List<List<string>>();

            repErrores = "<!DOCTYPE html><html><head><style>\n" +
                            "table {\n" +
                            "   font - family: arial, sans - serif;\n" +
                            "   border - collapse: collapse;\n" +
                            "   width: 100 %;}\n" +
                            "td, th {\n" +
                            "   border: 1px solid #dddddd;\n" +
                            "   text - align: left;\n" +
                            "   padding: 8px;}\n" +
                            "tr: nth - child(even) {\n" +
                            "   background - color: #dddddd;}\n" +
                            "</style></head><body><h2>REPORTE DE ERRORES</h2><table>\n" +
                            "   <tr><th>COLUMNA</th>\n" +
                            "   <th>FILA</th>\n" +
                            "   <th>ERROR</th></tr>\n";
            xmlErrores = "<ListaErrores>\n";
            xmlTokens = "<ListaTokens>\n";
        }
    }
}
