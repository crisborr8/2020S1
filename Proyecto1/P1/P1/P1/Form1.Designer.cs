namespace P1
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.Archivo = new System.Windows.Forms.ToolStripMenuItem();
            this.abrir = new System.Windows.Forms.ToolStripMenuItem();
            this.guardar = new System.Windows.Forms.ToolStripMenuItem();
            this.guardarComo = new System.Windows.Forms.ToolStripMenuItem();
            this.cerrar = new System.Windows.Forms.ToolStripMenuItem();
            this.pestañasToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nuevaP = new System.Windows.Forms.ToolStripMenuItem();
            this.cerrarP = new System.Windows.Forms.ToolStripMenuItem();
            this.verToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.guardarTokens = new System.Windows.Forms.ToolStripMenuItem();
            this.guardarErrores = new System.Windows.Forms.ToolStripMenuItem();
            this.reportesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.errorLexico = new System.Windows.Forms.ToolStripMenuItem();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.richTextBox2 = new System.Windows.Forms.RichTextBox();
            this.pestañas = new System.Windows.Forms.TabControl();
            this.txtConsola = new System.Windows.Forms.RichTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btnGenerar = new System.Windows.Forms.Button();
            this.imgGrafica = new System.Windows.Forms.PictureBox();
            this.btnAnterior = new System.Windows.Forms.Button();
            this.btnSiguiente = new System.Windows.Forms.Button();
            this.cbGrafica = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.menuStrip1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.pestañas.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.imgGrafica)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Archivo,
            this.pestañasToolStripMenuItem,
            this.verToolStripMenuItem,
            this.reportesToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(945, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // Archivo
            // 
            this.Archivo.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.abrir,
            this.guardar,
            this.guardarComo,
            this.cerrar});
            this.Archivo.Name = "Archivo";
            this.Archivo.Size = new System.Drawing.Size(60, 20);
            this.Archivo.Text = "Archivo";
            // 
            // abrir
            // 
            this.abrir.Name = "abrir";
            this.abrir.Size = new System.Drawing.Size(152, 22);
            this.abrir.Text = "Abrir";
            this.abrir.Click += new System.EventHandler(this.abrir_Click);
            // 
            // guardar
            // 
            this.guardar.Name = "guardar";
            this.guardar.Size = new System.Drawing.Size(152, 22);
            this.guardar.Text = "Guardar";
            this.guardar.Click += new System.EventHandler(this.guardar_Click);
            // 
            // guardarComo
            // 
            this.guardarComo.Name = "guardarComo";
            this.guardarComo.Size = new System.Drawing.Size(152, 22);
            this.guardarComo.Text = "Guardar Como";
            this.guardarComo.Click += new System.EventHandler(this.guardarComo_Click);
            // 
            // cerrar
            // 
            this.cerrar.Name = "cerrar";
            this.cerrar.Size = new System.Drawing.Size(152, 22);
            this.cerrar.Text = "Cerrar";
            this.cerrar.Click += new System.EventHandler(this.cerrar_Click);
            // 
            // pestañasToolStripMenuItem
            // 
            this.pestañasToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.nuevaP,
            this.cerrarP});
            this.pestañasToolStripMenuItem.Name = "pestañasToolStripMenuItem";
            this.pestañasToolStripMenuItem.Size = new System.Drawing.Size(65, 20);
            this.pestañasToolStripMenuItem.Text = "Pestañas";
            // 
            // nuevaP
            // 
            this.nuevaP.Name = "nuevaP";
            this.nuevaP.Size = new System.Drawing.Size(152, 22);
            this.nuevaP.Text = "Nueva Pestaña";
            this.nuevaP.Click += new System.EventHandler(this.nuevaP_Click);
            // 
            // cerrarP
            // 
            this.cerrarP.Name = "cerrarP";
            this.cerrarP.Size = new System.Drawing.Size(152, 22);
            this.cerrarP.Text = "Cerrar Pestaña";
            this.cerrarP.Click += new System.EventHandler(this.cerrarP_Click);
            // 
            // verToolStripMenuItem
            // 
            this.verToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.guardarTokens,
            this.guardarErrores});
            this.verToolStripMenuItem.Name = "verToolStripMenuItem";
            this.verToolStripMenuItem.Size = new System.Drawing.Size(90, 20);
            this.verToolStripMenuItem.Text = "Herramientas";
            // 
            // guardarTokens
            // 
            this.guardarTokens.Name = "guardarTokens";
            this.guardarTokens.Size = new System.Drawing.Size(155, 22);
            this.guardarTokens.Text = "Guardar tokens";
            this.guardarTokens.Click += new System.EventHandler(this.guardarTokens_Click);
            // 
            // guardarErrores
            // 
            this.guardarErrores.Name = "guardarErrores";
            this.guardarErrores.Size = new System.Drawing.Size(155, 22);
            this.guardarErrores.Text = "Guardar errores";
            this.guardarErrores.Click += new System.EventHandler(this.guardarErrores_Click);
            // 
            // reportesToolStripMenuItem
            // 
            this.reportesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.errorLexico});
            this.reportesToolStripMenuItem.Name = "reportesToolStripMenuItem";
            this.reportesToolStripMenuItem.Size = new System.Drawing.Size(35, 20);
            this.reportesToolStripMenuItem.Text = "Ver";
            // 
            // errorLexico
            // 
            this.errorLexico.Name = "errorLexico";
            this.errorLexico.Size = new System.Drawing.Size(149, 22);
            this.errorLexico.Text = "Errores léxicos";
            this.errorLexico.Click += new System.EventHandler(this.errorLexico_Click);
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.richTextBox2);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(574, 220);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Nueva pestaña";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // richTextBox2
            // 
            this.richTextBox2.Location = new System.Drawing.Point(0, 0);
            this.richTextBox2.Name = "richTextBox2";
            this.richTextBox2.Size = new System.Drawing.Size(574, 220);
            this.richTextBox2.TabIndex = 0;
            this.richTextBox2.Text = "";
            // 
            // pestañas
            // 
            this.pestañas.Controls.Add(this.tabPage1);
            this.pestañas.Location = new System.Drawing.Point(0, 27);
            this.pestañas.Name = "pestañas";
            this.pestañas.SelectedIndex = 0;
            this.pestañas.Size = new System.Drawing.Size(582, 246);
            this.pestañas.TabIndex = 1;
            // 
            // txtConsola
            // 
            this.txtConsola.BackColor = System.Drawing.SystemColors.InactiveCaption;
            this.txtConsola.Location = new System.Drawing.Point(8, 304);
            this.txtConsola.Name = "txtConsola";
            this.txtConsola.ReadOnly = true;
            this.txtConsola.Size = new System.Drawing.Size(574, 110);
            this.txtConsola.TabIndex = 2;
            this.txtConsola.Text = "";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(4, 278);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(70, 20);
            this.label1.TabIndex = 3;
            this.label1.Text = "Consola";
            // 
            // btnGenerar
            // 
            this.btnGenerar.Location = new System.Drawing.Point(385, 275);
            this.btnGenerar.Name = "btnGenerar";
            this.btnGenerar.Size = new System.Drawing.Size(193, 23);
            this.btnGenerar.TabIndex = 4;
            this.btnGenerar.Text = "CargarThopmson";
            this.btnGenerar.UseVisualStyleBackColor = true;
            this.btnGenerar.Click += new System.EventHandler(this.btnGenerar_Click);
            // 
            // imgGrafica
            // 
            this.imgGrafica.BackColor = System.Drawing.SystemColors.ControlDark;
            this.imgGrafica.Location = new System.Drawing.Point(588, 107);
            this.imgGrafica.Name = "imgGrafica";
            this.imgGrafica.Size = new System.Drawing.Size(345, 307);
            this.imgGrafica.TabIndex = 5;
            this.imgGrafica.TabStop = false;
            // 
            // btnAnterior
            // 
            this.btnAnterior.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnAnterior.Location = new System.Drawing.Point(588, 65);
            this.btnAnterior.Name = "btnAnterior";
            this.btnAnterior.Size = new System.Drawing.Size(66, 36);
            this.btnAnterior.TabIndex = 6;
            this.btnAnterior.Text = "<---";
            this.btnAnterior.UseVisualStyleBackColor = true;
            this.btnAnterior.Click += new System.EventHandler(this.btnAnterior_Click);
            // 
            // btnSiguiente
            // 
            this.btnSiguiente.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSiguiente.Location = new System.Drawing.Point(867, 65);
            this.btnSiguiente.Name = "btnSiguiente";
            this.btnSiguiente.Size = new System.Drawing.Size(66, 36);
            this.btnSiguiente.TabIndex = 7;
            this.btnSiguiente.Text = "--->";
            this.btnSiguiente.UseVisualStyleBackColor = true;
            this.btnSiguiente.Click += new System.EventHandler(this.btnSiguiente_Click);
            // 
            // cbGrafica
            // 
            this.cbGrafica.FormattingEnabled = true;
            this.cbGrafica.Items.AddRange(new object[] {
            "Ver graficas...",
            "AFD",
            "AFND",
            "Tabla de transiciones",
            "Tabla de cerraduras"});
            this.cbGrafica.Location = new System.Drawing.Point(659, 65);
            this.cbGrafica.Name = "cbGrafica";
            this.cbGrafica.Size = new System.Drawing.Size(202, 21);
            this.cbGrafica.TabIndex = 8;
            this.cbGrafica.SelectedIndexChanged += new System.EventHandler(this.cbGrafica_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(729, 27);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(68, 24);
            this.label2.TabIndex = 9;
            this.label2.Text = "Grafica";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(599, 49);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(43, 13);
            this.label3.TabIndex = 10;
            this.label3.Text = "Anterior";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(877, 49);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(51, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "Siguiente";
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(945, 422);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.cbGrafica);
            this.Controls.Add(this.btnSiguiente);
            this.Controls.Add(this.btnAnterior);
            this.Controls.Add(this.imgGrafica);
            this.Controls.Add(this.btnGenerar);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtConsola);
            this.Controls.Add(this.pestañas);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Proyecto 1";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.tabPage1.ResumeLayout(false);
            this.pestañas.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.imgGrafica)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem Archivo;
        private System.Windows.Forms.ToolStripMenuItem abrir;
        private System.Windows.Forms.ToolStripMenuItem guardar;
        private System.Windows.Forms.ToolStripMenuItem guardarComo;
        private System.Windows.Forms.ToolStripMenuItem cerrar;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabControl pestañas;
        private System.Windows.Forms.RichTextBox txtConsola;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnGenerar;
        private System.Windows.Forms.PictureBox imgGrafica;
        private System.Windows.Forms.Button btnAnterior;
        private System.Windows.Forms.Button btnSiguiente;
        private System.Windows.Forms.ComboBox cbGrafica;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ToolStripMenuItem pestañasToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nuevaP;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.RichTextBox richTextBox2;
        private System.Windows.Forms.ToolStripMenuItem cerrarP;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.ToolStripMenuItem verToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem guardarTokens;
        private System.Windows.Forms.ToolStripMenuItem guardarErrores;
        private System.Windows.Forms.ToolStripMenuItem reportesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem errorLexico;
    }
}

