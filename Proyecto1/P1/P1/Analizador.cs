using System.Collections.Generic;

namespace P1
{
    class Analizador
    {
        private int fil, col, filIni, colIni;
        private char[] textoFila, c;
        private string[] textoColumna;
        public string codigoError, xmlError, xmlTokens, pActual;

        List<string> conjunto;
        List<List<string>> conjuntos;
        
        public void Analizar(string codigo)
        {
            setSalidas();
            textoColumna = codigo.Split('\n');
            for(col = 0; col < textoColumna.Length; col++)
            {
                textoFila = textoColumna[col].ToCharArray();
                for(fil = 0; fil < textoFila.Length; fil++)
                {
                    pActual = "";
                    Comentario();
                    Conjunto();
                }
            }
            codigoError += "</table></body></html>";
            xmlError += "</ListaErrores>";
            xmlTokens += "</ListaTokens>";
        }

        private void Comentario()
        {
            filIni = fil + 1;
            colIni = col + 1;
            if (getChar() == '/')
            {
                pActual += '/';
                fil++;
                if (getChar() == '/')
                {
                    setToken("Comentario de linea", "//...");
                    fil = textoFila.Length;
                }
                else setError();
            }
            else if(getChar() == '<')
            {
                pActual += getChar();
                fil++;
                if (getChar() == '!')
                {
                    setToken("Comentario multilinea (Inicio)", "<!...");
                    while(getCharMultilinea() != '\0')
                    {
                        fil++;
                        if (getChar() == '!')
                        {
                            fil++;
                            if (getChar() == '>')
                            {
                                filIni = fil + 1;
                                colIni = col + 1;
                                setToken("Comentario multilinea (Fin)", "...!>");
                                fil++;
                                break;
                            }
                        }
                    }
                }
                else setError();
            }
        }
        private void Conjunto()
        {
            filIni = fil + 1;
            colIni = col + 1;
            if(getChar() == 'C')
            {
                pActual += getChar();
                fil++;
                if (getChar() == 'O')
                {
                    pActual += getChar();
                    fil++;
                    if (getChar() == 'N')
                    {
                        pActual += getChar();
                        fil++;
                        if (getChar() == 'J')
                        {
                            pActual += getChar();
                            fil++;
                            if (getChar() == ':')
                            {
                                setToken("Token Conjunto", "CONJ:");
                                fil++;
                                ConjuntoParametro();
                            }
                            else setError();
                        }
                        else setError();
                    }
                    else setError();
                }
                else setError();
            }
        }
        private void ConjuntoParametro()
        {
            pActual = "";
            while(getChar() != '-' || getChar() != '\0')
            {
                pActual += getChar();
                fil++;
            }
            conjunto = new List<string>();
            conjunto.Add(pActual);
            pActual = "";
            ConjuntoParametros();
        }
        private void ConjuntoParametros()
        {
            filIni = fil + 1;
            colIni = col + 1;
            if (getChar() == '-')
            {
                pActual += getChar();
                fil++;
                if (getChar() == '>')
                {
                    pActual += getChar();
                    fil++;
                }
                else setError();
            }
            else setError();
        }

        private char getChar()
        {
            if (fil >= textoFila.Length) return '\0';
            return textoFila[fil];
        }
        private char getCharMultilinea()
        {
            while (fil >= textoFila.Length)
            {
                col++;
                if (col >= textoColumna.Length) return '\0';
                textoFila = textoColumna[col].ToCharArray();
                fil = 0;
            }
            return textoFila[fil];
        }
        private void setError()
        {
            while(getChar() != '\0')
            {
                if (getChar() == ' ') break;
                pActual += getChar();
                fil++;
            }
            c = pActual.ToCharArray();
            pActual = "";
            foreach (char c_ in c)
            {
                if (c_ == '<') pActual += "&#60;";
                else if (c_ == '>') pActual += "&#62;";
                else pActual += c_;
            }
            codigoError += "  <tr><th>" + pActual + "</th><th>" + filIni + "</th><th>" + colIni + "</th></tr>\n";
            xmlError += "<Error>\n" +
                        "  <Valor>" + pActual + "</Valor>\n" +
                        "  <Fila>" + filIni + "</Fila>\n" +
                        "  <Columna>" + colIni + "</Columna>\n" +
                        "</Error>\n";
            pActual = "";
            fil++;
        }
        private void setToken(string nombre, string valor)
        {
            c = valor.ToCharArray();
            valor = "";
            foreach (char c_ in c)
            {
                if (c_ == '<') valor += "&#60;";
                else if (c_ == '>') valor += "&#62;";
                else valor += c_;
            }
            xmlTokens +=   "<Token>\n" +
                           "  <Nombre>" + nombre + "</Nombre>\n" +
                           "  <Valor>" + valor + "</Valor>\n" +
                           "  <Fila>" + filIni + "</Fila>\n" +
                           "  <Columna>" + colIni + "</Columna>\n" +
                           "</Token>\n";
        }
        private void setSalidas()
        {
            conjuntos = new List<List<string>>();
            codigoError = "<!DOCTYPE html><html><head><style>\n" +
                            "table{\n" +
                            "  font - family: arial, sans - serif;\n" +
                            "  border - collapse: collapse;\n" +
                            "  width: 100 %;}\n" +
                            "td, th {\n" +
                            "  border: 1px solid #dddddd;\n" +
                            "  text - align: left;\n" +
                            "padding: 8px;}\n" +
                            "tr: nth - child(even){\n" +
                            "  background - color: #dddddd;}\n" +
                            "</style></head><body><h2> TABLA DE ERRORES LEXICOS</h2><table>\n" +
                            "  <tr><th>Lexema</th><th>Fila</th><th>Columna</th></tr>\n";
            xmlError = "<ListaErrores>\n";
            xmlTokens = "<ListaTokens>\n";
        }
    }
}
