using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace P1
{
    class AFD
    {
        public string letra;
        public bool finalizador;
        public List<string> s_Letra;
        public List<string> s_Transicion;

        public AFD()
        {
            letra = "";
            finalizador = false;
            s_Letra = new List<string>();
            s_Transicion = new List<string>();
        }
    }

    class AFD_Lista
    {
        public string titulo;
        public List<AFD> AFD;

        public AFD_Lista()
        {
            titulo = "";
            AFD = new List<AFD>();
        }
    }
}
