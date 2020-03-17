using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace P1
{
    class Cerradura
    {
        public string Letra;
        public List<int> Epsilon;
        public List<int> Siguientes;
        public List<Ir> Ir;

        public Cerradura()
        {
            Epsilon = new List<int>();
            Siguientes = new List<int>();
            Ir = new List<Ir>();
        }
    }

    class Ir
    {
        public string Letra_C;
        public string Letra_I;
        public List<int> Siguientes;

        public Ir()
        {
            Siguientes = new List<int>();
        }
    }
}
