using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace P1
{
    class Generador
    {
        //**************************************************************************
        //**************************************************************************
        //DECLARACION DE VARIABLES
        public string salida;
        private string codigo;
        public Graficar g;

        private int index, k, ultimo;

        private List<int> visitados;
        private List<int> siguientes;
        private List<string> actual;
        private List<List<string>> vExpReg;
        private List<List<string>> vConjunto;
        private List<List<string>> vExpresion;

        private List<Cerradura> TablaCerradura;
        private List<Automata> OperacionCerradura;

        public List<string> pathAFD;
        public List<string> pathAFN;
        public List<string> pathCerradura;
        public List<string> pathSiguientes;

        public Generador()
        {
            Inicializar();
            g.Eliminar();
        }

        public void Generar()
        {
            if (verificarConjuntos())
            {
                Inicializar();
                salida = "";
                for (int i = 0; i < vExpReg.Count; i++)
                {
                    actual = vExpReg[i];
                    if (actual.Count > 1)
                    {
                        Automata n1 = new Automata();
                        Automata n2 = new Automata();
                        Automata n3 = new Automata();

                        k = 1;
                        index = 1;
                        n1.setN(0);
                        n1.setT1(actual[0]);
                        n1.setS1(Insertar(n2, n3));
                        n3.setN(k);
                        OperacionCerradura.Add(n1);
                    }
                }
                string dir = g.dir;
                for (int i = 0; i < OperacionCerradura.Count; i++)
                {
                    ultimo = getUltimo(OperacionCerradura[i].getS1());

                    visitados = new List<int>();
                    codigo = "digraph AFN{\nrankdir=LR;\n";
                    codigo += "labelloc=t;\nlabel=\"" + OperacionCerradura[i].getT1() + "\";\n";
                    AFN(OperacionCerradura[i].getS1());
                    g.Grafica(codigo + "}", OperacionCerradura[i].getT1() + "_AFN");
                    pathAFN.Add(@dir + "\\G_" + OperacionCerradura[i].getT1() + "_AFN");

                    codigo = "digraph Cerradura{\n";
                    codigo += "labelloc=t;\nlabel=\"" + OperacionCerradura[i].getT1() + "\";\n";
                    codigo += "node [shape=plaintext];\n";
                    codigo += "tabla [label=<<table>\n";
                    Tabla_Cerradura_2(OperacionCerradura[i].getS1());
                    codigo += "</table>>];\n}";
                    g.Grafica(codigo, OperacionCerradura[i].getT1() + "_Cerradura");
                    pathCerradura.Add(@dir + "\\G_" + OperacionCerradura[i].getT1() + "_Cerradura");

                    codigo = "digraph Siguientes{\n";
                    codigo += "labelloc=t;\nlabel=\"" + OperacionCerradura[i].getT1() + "\";\n";
                    codigo += "node [shape=plaintext];\n";
                    codigo += "tabla [label=<<table>\n";
                    Tabla_Siguientes();
                    codigo += "</table>>];\n}";
                    g.Grafica(codigo, OperacionCerradura[i].getT1() + "_Siguientes");
                    pathSiguientes.Add(@dir + "\\G_" + OperacionCerradura[i].getT1() + "_Siguientes");

                    codigo = "digraph AFD{\nrankdir=LR;\n";
                    codigo += "labelloc=t;\nlabel=\"" + OperacionCerradura[i].getT1() + "\";\n";
                    AFD();
                    g.Grafica(codigo + "}", OperacionCerradura[i].getT1() + "_AFD");
                    pathAFD.Add(@dir + "\\G_" + OperacionCerradura[i].getT1() + "_AFD");
                }
            }
        }
        private void AFN(Automata a)
        {
            visitados.Add(a.getN());
            if (a.getS1() != null)
            {
                codigo += a.getN() + " -> " + a.getS1().getN() + " [label=\"" + a.getT1() + "\"];\n";
                if (!visitados.Contains(a.getS1().getN())) AFN(a.getS1());
            }
            if (a.getS2() != null)
            {
                codigo += a.getN() + " -> " + a.getS2().getN() + " [label=\"" + a.getT2() + "\"];\n";
                if (!visitados.Contains(a.getS2().getN())) AFN(a.getS2());
            }
            if (a.getS1() == null && a.getS2() == null)
                codigo += a.getN() + " [shape=doublecircle];\n";
        }
        private void Tabla_Cerradura_2(Automata ini)
        {
            TablaCerradura = new List<Cerradura>();
            Cerradura c = new Cerradura();
            c.Epsilon.Add(1);
            char letra = 'B';
            c.Letra = "A";
            TablaCerradura.Add(c);


            Automata act;
            int ir, t2;

            for (int t = 0; t < TablaCerradura.Count; t++)
            {
                siguientes = new List<int>();
                for (int ep = 0; ep < TablaCerradura[t].Epsilon.Count; ep++)
                {
                    visitados = new List<int>();
                    TablaCerradura_Siguientes(getNodo(ini, TablaCerradura[t].Epsilon[ep]), TablaCerradura[t].Epsilon[ep]);
                }
                TablaCerradura[t].Siguientes = siguientes;

                for (int si = 0; si < TablaCerradura[t].Siguientes.Count; si++)
                {
                    visitados = new List<int>();
                    act = getNodo(ini, TablaCerradura[t].Siguientes[si]);
                    siguientes = new List<int>();
                    visitados = new List<int>();
                    TablaCerradura_Ir(act);

                    for (int s = 0; s < siguientes.Count; s++)
                    {
                        visitados = new List<int>();
                        act = getNodo(ini, siguientes[s]);

                        for (ir = 0; ir < TablaCerradura[t].Ir.Count; ir++)
                        {
                            if (act.getT1() == null) break;
                            if (TablaCerradura[t].Ir[ir].Letra_I.ToString() == act.getT1())
                            {
                                if (!TablaCerradura[t].Ir[ir].Siguientes.Contains(act.getS1().getN()))
                                    TablaCerradura[t].Ir[ir].Siguientes.Add(act.getS1().getN());
                                break;
                            }
                        }
                        if (ir == TablaCerradura[t].Ir.Count && act.getS1() != null)
                        {
                            Ir nir = new Ir();
                            nir.Letra_I = act.getT1();
                            nir.Siguientes.Add(act.getS1().getN());
                            TablaCerradura[t].Ir.Add(nir);
                        }
                    }
                }
                for (ir = 0; ir < TablaCerradura[t].Ir.Count; ir++)
                {
                    for (t2 = 0; t2 < TablaCerradura.Count; t2++)
                    {
                        if (Iguales(TablaCerradura[t2].Epsilon, TablaCerradura[t].Ir[ir].Siguientes))
                        {
                            TablaCerradura[t].Ir[ir].Letra_C = TablaCerradura[t2].Letra;
                            break;
                        }
                    }
                    if (t2 == TablaCerradura.Count)
                    {
                        c = new Cerradura();
                        c.Letra = ((char)letra++).ToString();
                        TablaCerradura[t].Ir[ir].Letra_C = c.Letra;
                        c.Epsilon = TablaCerradura[t].Ir[ir].Siguientes;
                        TablaCerradura.Add(c);
                    }
                }
                
            }

            for (int t = 0; t < TablaCerradura.Count; t++)
            {
                codigo += "<tr>";
                codigo += "<td>" + TablaCerradura[t].Letra + " - Cerradura (";
                if (TablaCerradura[t].Epsilon.Count == 0) codigo += "--)</td>";
                for (int e = 0; e < TablaCerradura[t].Epsilon.Count; e++)
                {
                    codigo += TablaCerradura[t].Epsilon[e];
                    if (e == TablaCerradura[t].Epsilon.Count - 1) codigo += ")</td>";
                    else codigo += ", ";
                }
                if (TablaCerradura[t].Siguientes.Count > 0) codigo += "<td>";
                for (int s = 0; s < TablaCerradura[t].Siguientes.Count; s++)
                {
                    codigo += TablaCerradura[t].Siguientes[s];
                    if (s == TablaCerradura[t].Siguientes.Count - 1) codigo += "</td>";
                    else codigo += ", ";
                }
                codigo += "</tr>\n";
                for (ir = 0; ir < TablaCerradura[t].Ir.Count; ir++)
                {
                    codigo += "<tr>";
                    codigo += "<td>Ir (" + TablaCerradura[t].Ir[ir].Letra_I + ")" +
                              " - " + TablaCerradura[t].Ir[ir].Letra_C + "</td>";
                    if (TablaCerradura[t].Ir[ir].Siguientes.Count > 0) codigo += "<td>";
                    for (int irS = 0; irS < TablaCerradura[t].Ir[ir].Siguientes.Count; irS++)
                    {
                        codigo += TablaCerradura[t].Ir[ir].Siguientes[irS];
                        if (irS == TablaCerradura[t].Ir[ir].Siguientes.Count - 1) codigo += "</td>";
                        else codigo += ", ";
                    }
                    codigo += "</tr>\n";
                }
            }
        }

        private void Tabla_Cerradura(Automata ini)
        {
            TablaCerradura = new List<Cerradura>();
            Cerradura c = new Cerradura();
            c.Epsilon.Add(1);
            char letra = 'B';
            c.Letra = "A";
            TablaCerradura.Add(c);


            Automata act;
            int ir, t2;

            for (int t = 0; t < TablaCerradura.Count; t++)
            {
                siguientes = new List<int>();
                for (int ep = 0; ep < TablaCerradura[t].Epsilon.Count; ep++)
                {
                    visitados = new List<int>();
                    TablaCerradura_Siguientes(getNodo(ini, TablaCerradura[t].Epsilon[ep]), TablaCerradura[t].Epsilon[ep]);
                }
                TablaCerradura[t].Siguientes = siguientes;

                for(int si = 0; si < TablaCerradura[t].Siguientes.Count; si++)
                {
                    visitados = new List<int>();
                    act = getNodo(ini, TablaCerradura[t].Siguientes[si]);
                    siguientes = new List<int>();
                    visitados = new List<int>();
                    TablaCerradura_Ir(act);
                    
                    for (int s = 0; s < siguientes.Count; s++)
                    {
                        visitados = new List<int>();
                        act = getNodo(ini, siguientes[s]);
                        for (ir = 0; ir < TablaCerradura[t].Ir.Count; ir++)
                        {
                            if (TablaCerradura[t].Ir[ir].Letra_I.ToString() == "--") break;
                            if (TablaCerradura[t].Ir[ir].Letra_I.ToString() == act.getT1())
                            {
                                if (!TablaCerradura[t].Ir[ir].Siguientes.Contains(act.getS1().getN()))
                                    TablaCerradura[t].Ir[ir].Siguientes.Add(act.getS1().getN());
                                break;
                            }
                        }
                        if (ir == TablaCerradura[t].Ir.Count)
                        {
                            Ir nir = new Ir();
                            if (act.getS1() == null && act.getS2() == null) nir.Letra_I = "--";
                            else
                            {
                                nir.Letra_I = act.getT1();
                                nir.Siguientes.Add(act.getS1().getN());
                            }
                            TablaCerradura[t].Ir.Add(nir);
                        }
                    }
                }
                for (ir = 0; ir < TablaCerradura[t].Ir.Count; ir++)
                {
                    for (t2 = 0; t2 < TablaCerradura.Count; t2++)
                    {
                        if (Iguales(TablaCerradura[t2].Epsilon, TablaCerradura[t].Ir[ir].Siguientes))
                        {
                            TablaCerradura[t].Ir[ir].Letra_C = TablaCerradura[t2].Letra;
                            break;
                        }
                    }
                    if (t2 == TablaCerradura.Count)
                    {
                        c = new Cerradura();
                        c.Letra = ((char)letra).ToString();
                        TablaCerradura[t].Ir[ir].Letra_C = c.Letra;
                        c.Epsilon = TablaCerradura[t].Ir[ir].Siguientes;
                        TablaCerradura.Add(c);
                        letra++;
                    }
                }
            }

            for (int t = 0; t < TablaCerradura.Count; t++)
            {
                codigo += "<tr>";
                codigo += "<td>" + TablaCerradura[t].Letra + " - Cerradura (";
                if (TablaCerradura[t].Epsilon.Count == 0) codigo += "--)</td>";
                for (int e = 0; e < TablaCerradura[t].Epsilon.Count; e++)
                {
                    codigo += TablaCerradura[t].Epsilon[e];
                    if (e == TablaCerradura[t].Epsilon.Count - 1) codigo += ")</td>";
                    else codigo += ", ";
                }
                if (TablaCerradura[t].Siguientes.Count > 0) codigo += "<td>";
                for (int s = 0; s < TablaCerradura[t].Siguientes.Count; s++)
                {
                    codigo += TablaCerradura[t].Siguientes[s];
                    if (s == TablaCerradura[t].Siguientes.Count - 1) codigo += "</td>";
                    else codigo += ", ";
                }
                codigo += "</tr>\n";
                for (ir = 0; ir < TablaCerradura[t].Ir.Count; ir++)
                {
                    codigo += "<tr>";
                    codigo += "<td>Ir (" + TablaCerradura[t].Ir[ir].Letra_I + ")" +
                              " - " + TablaCerradura[t].Ir[ir].Letra_C + "</td>";
                    if (TablaCerradura[t].Ir[ir].Siguientes.Count > 0) codigo += "<td>";
                    for (int irS = 0; irS < TablaCerradura[t].Ir[ir].Siguientes.Count; irS++)
                    {
                        codigo += TablaCerradura[t].Ir[ir].Siguientes[irS];
                        if (irS == TablaCerradura[t].Ir[ir].Siguientes.Count - 1) codigo += "</td>";
                        else codigo += ", ";
                    }
                    codigo += "</tr>\n";
                }
            }
        }
        private void Tabla_Siguientes()
        {
            actual = new List<string>();
            string s = "";
            for(int t = 0; t < TablaCerradura.Count; t++)
            {
                for(int ir = 0; ir < TablaCerradura[t].Ir.Count; ir++)
                    if (!actual.Contains(TablaCerradura[t].Ir[ir].Letra_I)) actual.Add(TablaCerradura[t].Ir[ir].Letra_I);
            }
            for (int t = 0; t < TablaCerradura.Count; t++)
            {
                if(TablaCerradura[t].Siguientes.Contains(ultimo))
                    s += "<tr><td>" + TablaCerradura[t].Letra + "*</td>";
                else
                    s += "<tr><td>" + TablaCerradura[t].Letra + "</td>";
                visitados = new List<int>();
                for (int v = 0; v < actual.Count; v++)
                    visitados.Add(-1);
                for (int ir = 0; ir < TablaCerradura[t].Ir.Count; ir++)
                    visitados[actual.IndexOf(TablaCerradura[t].Ir[ir].Letra_I)] = ir;
                foreach(int v in visitados)
                {
                    if (v != -1)
                        s += "<td>" + TablaCerradura[t].Ir[v].Letra_C + "</td>";
                    else
                        s += "<td>--</td>";
                }
                s += "</tr>\n";
            }
            codigo += "<tr><td>--</td>";
            for (int i = 0; i < actual.Count; i++)
                codigo += "<td>" + actual[i] + "</td>";
            codigo += "</tr>\n";
            codigo += s;
        }
        private void AFD()
        {
            string l1, l2;
            for (int t = 0; t < TablaCerradura.Count; t++)
            {
                visitados = new List<int>();
                if (TablaCerradura[t].Siguientes.Contains(ultimo))
                    codigo += TablaCerradura[t].Letra + " [shape=doublecircle];\n";
                for (int v = 0; v < actual.Count; v++)
                    visitados.Add(-1);
                for (int ir = 0; ir < TablaCerradura[t].Ir.Count; ir++)
                    visitados[actual.IndexOf(TablaCerradura[t].Ir[ir].Letra_I)] = ir;
                foreach (int v in visitados)
                {
                    if (v != -1)
                    {
                        l1 = TablaCerradura[t].Letra;
                        l2 = TablaCerradura[t].Ir[v].Letra_C;
                        codigo += l1 + " -> " + l2 + " [label=\"" + TablaCerradura[t].Ir[v].Letra_I + "\"];\n";
                    }
                }
            }
        }

        private void TablaCerradura_Siguientes(Automata a, int idOrigen)
        {
            if(!siguientes.Contains(a.getN()) && a.getN() != idOrigen) siguientes.Add(a.getN());
            if (a.getS1() != null)
                if (!siguientes.Contains(a.getS1().getN()))
                    if (a.getT1() == "ε") TablaCerradura_Siguientes(a.getS1(), idOrigen);
            if (a.getS2() != null)
                if (!siguientes.Contains(a.getS2().getN()))
                    if (a.getT2() == "ε") TablaCerradura_Siguientes(a.getS2(), idOrigen);
        }
        private void TablaCerradura_Ir(Automata a)
        {
            visitados.Add(a.getN());
            if (a.getS1() != null)
                if (!visitados.Contains(a.getS1().getN()))
                {
                    if (a.getT1() == "ε") TablaCerradura_Ir(a.getS1());
                    else siguientes.Add(a.getN());
                }
            if (a.getS2() != null)
                if (!visitados.Contains(a.getS2().getN()))
                {
                    if (a.getT2() == "ε") TablaCerradura_Ir(a.getS2());
                    else siguientes.Add(a.getN());
                }
            if (a.getS1() == null && a.getS2() == null) siguientes.Add(a.getN());
        }
        private Automata getNodo(Automata actual, int id)
        {
            if (actual.getN() == id) return actual;
            visitados.Add(actual.getN());
            if (actual.getS2() != null)
            {
                if (!visitados.Contains(actual.getS2().getN()))
                    if (actual.getS2().getN() <= id)
                    {
                        Automata a = getNodo(actual.getS2(), id);
                        if (a != null) return a;
                    }
            }
            if (actual.getS1() != null)
            {
                if (!visitados.Contains(actual.getS1().getN()))
                    if (actual.getS1().getN() <= id) return getNodo(actual.getS1(), id);
            }
            return null;
        }
        private int getUltimo(Automata actual)
        {
            if (actual.getS1() != null)
                return getUltimo(actual.getS1());
            return actual.getN();
        }

        private bool verificarConjuntos()
        {
            string s;
            for(int i = 0; i < vExpReg.Count; i++)
            {
                actual = vExpReg[i];
                for(int j = 1; j < actual.Count; j++)
                {
                    if (actual[j].StartsWith("{"))
                    {
                        s = actual[j].TrimStart('{');
                        for(k = 0; k < vConjunto.Count; k++)
                            if (vConjunto[k][0] == s) break;
                        if (k == vConjunto.Count)
                        {
                            salida = "****  ERROR EN " + actual[0] + "  ****\n" +
                                     "---->NO SE RECONOCE EL VALOR DE " + s;
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        private Automata Insertar(Automata ini, Automata fin)
        {
            if(actual[index] == ".")
            {
                Automata A = new Automata();
                Automata B = new Automata();
                Automata epA = new Automata();
                ini.setN(k);
                ini.setT1("ε");
                index++;
                k++;

                ini.setS1(Insertar(A, epA));
                epA.setT1("ε");
                epA.setN(k);
                k++;

                epA.setS1(Insertar(B, fin));
            }
            else if (actual[index] == "|")
            {
                Automata A = new Automata();
                Automata B = new Automata();
                Automata epA = new Automata();
                Automata epB = new Automata();
                ini.setN(k);
                ini.setT1("ε");
                ini.setT2("ε");
                index++;
                k++;

                ini.setS1(Insertar(A, epA));
                epA.setT1("ε");
                epA.setN(k);
                k++;
                ini.setS2(Insertar(B, epB));
                epB.setT1("ε");
                epB.setN(k);
                k++;

                epA.setS1(fin);
                epB.setS1(fin);
                
            }
            else if (actual[index] == "*")
            {
                Automata A = new Automata();
                Automata epA = new Automata();
                ini.setN(k);
                ini.setT1("ε");
                ini.setT2("ε");
                index++;
                k++;

                ini.setS1(Insertar(A, epA));
                ini.setS2(epA);
                epA.setT1("ε");
                epA.setT2("ε");
                epA.setN(k);
                k++;

                epA.setS1(fin);
                epA.setS2(A);
                
            }
            else if (actual[index] == "+")
            {
                Automata A = new Automata();
                Automata epA = new Automata();
                ini.setN(k);
                ini.setT1("ε");
                index++;
                k++;

                ini.setS1(Insertar(A, epA));
                epA.setT1("ε");
                epA.setT2("ε");
                epA.setN(k);
                k++;

                epA.setS1(fin);
                epA.setS2(A);
                
            }
            else if (actual[index] == "?")
            {
                Automata A = new Automata();
                Automata epA = new Automata();
                ini.setN(k);
                ini.setT1("ε");
                ini.setT2("ε");
                index++;
                k++;

                ini.setS1(Insertar(A, epA));
                ini.setS2(epA);
                epA.setT1("ε");
                epA.setN(k);
                k++;

                epA.setS1(fin);
                
            }
            else if (actual[index].StartsWith("{"))
            {
                ini.setN(k);
                ini.setT1(actual[index] + "}");
                ini.setS1(fin);
                index++;
                k++;
            }
            else
            {
                ini.setN(k);
                ini.setT1("\\" + actual[index] + "\\\"");
                ini.setS1(fin);
                index++;
                k++;
            }
            return ini;
        }

        private bool Iguales(List<int> l1, List<int> l2)
        {
            if (l1.Count != l2.Count) return false;
            int i;
            foreach(int l_1 in l1)
            {
                for (i = 0; i < l2.Count; i++)
                    if (l_1 == l2[i]) break;
                if (i == l2.Count) return false;
            }
            return true;
        }
        //**************************************************************************
        //**************************************************************************
        //INICIALIZAR
        private void Inicializar()
        { 
            OperacionCerradura = new List<Automata>();
            TablaCerradura = new List<Cerradura>();
            pathSiguientes = new List<string>();
            pathCerradura = new List<string>();
            pathAFD = new List<string>();
            pathAFN = new List<string>();
            g = new Graficar();
            
        }
        public void setListas(List<List<string>> vExpReg, List<List<string>> vConjunto, List<List<string>> vExpresion)
        {
            this.vExpReg = vExpReg;
            this.vConjunto = vConjunto;
            this.vExpresion = vExpresion;
        }
    }
}
