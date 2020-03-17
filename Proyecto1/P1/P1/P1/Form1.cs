using System;
using System.IO;
using System.Diagnostics;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Drawing;

namespace P1
{
    public partial class Form1 : Form
    {
        Analizador a;
        Generador g;
        string path, dir;
        RichTextBox rtbox;
        int indexImg;

        public Form1()
        {
            path = "";
            indexImg = 0;
            a = new Analizador();
            g = new Generador();
            InitializeComponent();
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
                sr.Close();
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
                    MessageBox.Show("ARCHIVO GUARDADO");
                }
                else MessageBox.Show("ERROR AL GUARDAR EL ARCHIVO");
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
                MessageBox.Show("ARCHIVO GUARDADO");
            }
            else MessageBox.Show("NO EXISTEN PESTAÑAS A CERRAR");
        }

        private void guardarComo_Click(object sender, EventArgs e)
        {
            guardar_Como();
        }

        private void btnGenerar_Click(object sender, EventArgs e)
        {
            cbGrafica.SelectedIndex = 0;
            setImagen();
            if(pestañas.TabCount > 0)
            {
                rtbox = (RichTextBox)pestañas.TabPages[pestañas.SelectedIndex].Controls[0];
                if (rtbox.Text.Trim() == "") MessageBox.Show("TEXTO VACIO");
                else
                {
                    a.Analizar(rtbox.Text);
                    MessageBox.Show("ANALIZADO");
                    if (a.correcto)
                    {
                        if (a.vExpReg.Count > 0)
                        {
                            g.setListas(a.vExpReg, a.vConjunto, a.vExpresion);
                            g.Generar();
                            txtConsola.Text = g.salida;
                            indexImg = 0;
                            setImagen();
                        }
                        else txtConsola.Text = "ERROR NO EXISTEN EXPRESIONES REGULARES";
                    }
                    else txtConsola.Text = "ERROR EN LA SINTAXIS AL ANALIZAR";
                }
            }
            else MessageBox.Show("NO EXISTEN PESTAÑAS A ANALIZAR");
        }

        private void setImagen()
        {
            if(cbGrafica.SelectedIndex == 0)
            {
                imgGrafica.Image = new Bitmap(Directory.GetCurrentDirectory() + "/nada.png");
                imgGrafica.SizeMode = PictureBoxSizeMode.CenterImage;
            }
            else if (g.pathAFD.Count != 0 && cbGrafica.SelectedIndex == 1)
            {
                if (indexImg > g.pathAFD.Count - 1) indexImg = 0;
                else if (indexImg < 0) indexImg = g.pathAFD.Count - 1;
                imgGrafica.Image = new Bitmap(g.pathAFD[indexImg] + ".png");
                imgGrafica.SizeMode = PictureBoxSizeMode.CenterImage;
            }
            else if (g.pathAFN.Count != 0 && cbGrafica.SelectedIndex == 2)
            {
                if (indexImg > g.pathAFN.Count - 1) indexImg = 0;
                else if (indexImg < 0) indexImg = g.pathAFN.Count - 1;
                imgGrafica.Image = new Bitmap(g.pathAFN[indexImg] + ".png");
                imgGrafica.SizeMode = PictureBoxSizeMode.CenterImage;
            }
            else if (g.pathSiguientes.Count != 0 && cbGrafica.SelectedIndex == 3)
            {
                if (indexImg > g.pathSiguientes.Count - 1) indexImg = 0;
                else if (indexImg < 0) indexImg = g.pathSiguientes.Count - 1;
                imgGrafica.Image = new Bitmap(g.pathSiguientes[indexImg] + ".png");
                imgGrafica.SizeMode = PictureBoxSizeMode.CenterImage;
            }
            else if (g.pathCerradura.Count != 0 && cbGrafica.SelectedIndex == 4)
            {
                if (indexImg > g.pathCerradura.Count - 1) indexImg = 0;
                else if (indexImg < 0) indexImg = g.pathCerradura.Count - 1;
                imgGrafica.Image = new Bitmap(g.pathCerradura[indexImg] + ".png");
                imgGrafica.SizeMode = PictureBoxSizeMode.CenterImage;
            }
        }

        private void errorLexico_Click(object sender, EventArgs e)
        {
            File.WriteAllText(@dir + "\\Error.html", a.repErrores);
            Process.Start(@dir + "\\Error.html");
        }

        private void guardarErrores_Click(object sender, EventArgs e)
        {
            File.WriteAllText(@dir + "\\xmlError.xml", a.xmlErrores);
            Process.Start(@dir + "\\xmlError.xml");
        }

        private void btnAnterior_Click(object sender, EventArgs e)
        {
            indexImg--;
            setImagen();
        }

        private void btnSiguiente_Click(object sender, EventArgs e)
        {
            indexImg++;
            setImagen();
        }

        private void cbGrafica_SelectedIndexChanged(object sender, EventArgs e)
        {
            indexImg = 0;
            setImagen();
        }

        private void guardarTokens_Click(object sender, EventArgs e)
        {
            File.WriteAllText(@dir + "\\xmlTokens.xml", a.xmlTokens);
            Process.Start(@dir + "\\xmlTokens.xml");
        }
    }
}
