using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace P1
{
    public partial class Form1 : Form
    {
        Analizador a;
        string path, dir;
        RichTextBox rtbox;

        public Form1()
        {
            InitializeComponent();
            path = "";
            a = new Analizador();
            cbGrafica.SelectedIndex = 0;
            dir = Directory.GetCurrentDirectory() + "\\Salidas";
        }

        private void nuevaP_Click(object sender, EventArgs e)
        {
            crearPestaña();
        }

        private void cerrarP_Click(object sender, EventArgs e)
        {
            if (pestañas.TabCount > 0) pestañas.TabPages.RemoveAt(pestañas.SelectedIndex);
            else MessageBox.Show("NO EXISTEN PESTAÑAS A CERRAR");
        }

        private void cerrar_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void abrir_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "Archivo er (*.er)|*.er|Todos los archivos (*.*)|*.*";
            if(openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                path = openFileDialog1.FileName;
                if (pestañas.TabCount == 0) crearPestaña();
                rtbox = (RichTextBox) pestañas.TabPages[pestañas.SelectedIndex].Controls[0];
                var sr = new StreamReader(openFileDialog1.FileName);
                rtbox.Text = sr.ReadToEnd();
                string[] nombre = openFileDialog1.FileName.Split('\\');
                pestañas.TabPages[pestañas.SelectedIndex].Text = nombre[nombre.Length - 1];
            }
        }

        private void crearPestaña()
        {
            TabPage pagina = new TabPage();
            pagina.Text = "Nueva Pestaña";
            RichTextBox texto = new RichTextBox();
            pagina.Controls.Add(texto);
            pestañas.TabPages.Add(pagina);
            texto.Size = pagina.Size;
            pestañas.SelectedIndex = pestañas.TabCount - 1;
        }

        private void guardar_Como()
        {
            if(pestañas.TabCount > 0)
            {
                saveFileDialog1.Filter = "Archivo er (*.er)|*.er|Todos los archivos (*.*)|*.*";
                if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    rtbox = (RichTextBox)pestañas.TabPages[pestañas.SelectedIndex].Controls[0];
                    File.WriteAllText(saveFileDialog1.FileName, rtbox.Text);
                }
            }
            else MessageBox.Show("NO EXISTEN PESTAÑAS A GUARDAR");
        }

        private void guardar_Click(object sender, EventArgs e)
        {
            if (path.Equals("")) guardar_Como();
            else if(pestañas.TabCount > 0)
            {
                rtbox = (RichTextBox)pestañas.TabPages[pestañas.SelectedIndex].Controls[0];
                File.WriteAllText(path, rtbox.Text);
            }
            else MessageBox.Show("NO EXISTEN PESTAÑAS A CERRAR");
        }

        private void guardarComo_Click(object sender, EventArgs e)
        {
            guardar_Como();
        }

        private void btnGenerar_Click(object sender, EventArgs e)
        {
            if(pestañas.TabCount > 0)
            {
                rtbox = (RichTextBox)pestañas.TabPages[pestañas.SelectedIndex].Controls[0];
                if (rtbox.Text.Trim() == "") MessageBox.Show("TEXTO VACIO");
                else
                {
                    a.Analizar(rtbox.Text);
                    MessageBox.Show("ANALIZADO");
                }
            }
            else MessageBox.Show("NO EXISTEN PESTAÑAS A ANALIZAR");
        }

        private void errorLexico_Click(object sender, EventArgs e)
        {
            File.WriteAllText(@dir + "\\Error.html", a.codigoError);
            Process.Start(@dir + "\\Error.html");
        }

        private void guardarErrores_Click(object sender, EventArgs e)
        {
            File.WriteAllText(@dir + "\\xmlError.xml", a.xmlError);
            Process.Start(@dir + "\\xmlError.xml");
        }

        private void guardarTokens_Click(object sender, EventArgs e)
        {
            File.WriteAllText(@dir + "\\xmlTokens.xml", a.xmlTokens);
            Process.Start(@dir + "\\xmlTokens.xml");
        }
    }
}
