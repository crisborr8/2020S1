using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace P1
{
    class Graficar
    {

        public string dir = Directory.GetCurrentDirectory() + "\\Salidas";

        public void Grafica(string codigo, string titulo)
        {
            titulo = @dir + "\\G_" + titulo;
            File.WriteAllText(titulo + ".dot", codigo);
            System.Diagnostics.Process process = new System.Diagnostics.Process();
            System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo();
            startInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
            startInfo.FileName = "cmd.exe";
            string comando = "dot " + titulo + ".dot -Tpng -o " + titulo + ".png";
            startInfo.Arguments = "/C " + comando;
            process.StartInfo = startInfo;
            process.Start();
            //Process.Start(titulo + ".png");
        }

        public void Eliminar()
        {
            string dirr = Directory.GetCurrentDirectory() + "\\Salidas";
            string[] files = Directory.GetFiles(@dirr);
            foreach (string file in files)
            {
                File.Delete(file);
                Console.WriteLine($"{file} is deleted.");
            }
        }
    }
}
