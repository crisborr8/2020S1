using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace P1
{
    class Automata
    {

        private int n;
        private string t1, t2;
        private Automata s1, s2;

        public Automata()
        {
            s1 = s2 = null;
            t1 = t2 = null;
            n = -1;
        }

        public void setN(int n) { this.n = n; }
        public void setT1(string t1) { this.t1 = t1; }
        public void setT2(string t2) { this.t2 = t2; }
        public void setS1(Automata s1) { this.s1 = s1; }
        public void setS2(Automata s2) { this.s2 = s2; }

        public int getN() { return n; }
        public string getT1() { return t1; }
        public string getT2() { return t2; }
        public Automata getS1() { return s1; }
        public Automata getS2() { return s2; }
    }
}
