package olc1.practica1;

public class Practica1 extends javax.swing.JFrame {

    Archivos archivos;
    Analizador analizador;
    
    public Practica1() {
        initComponents();
        Inicializar();
    }
    
    private void Inicializar(){
        archivos = new Archivos();
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jScrollPane1 = new javax.swing.JScrollPane();
        txt_Entrada = new javax.swing.JTextArea();
        jScrollPane2 = new javax.swing.JScrollPane();
        txt_Salida = new javax.swing.JTextArea();
        btn_Generar = new javax.swing.JButton();
        btn_Analizar = new javax.swing.JButton();
        jScrollPane3 = new javax.swing.JScrollPane();
        tree_Archivos = new javax.swing.JTree();
        cb_Img = new javax.swing.JComboBox();
        btn_Anterior = new javax.swing.JButton();
        panel_Img = new javax.swing.JPanel();
        slide_Img = new javax.swing.JSlider();
        btn_Siguiente = new javax.swing.JButton();
        jMenuBar1 = new javax.swing.JMenuBar();
        jMenu1 = new javax.swing.JMenu();
        menu_Abrir = new javax.swing.JMenuItem();
        jMenuItem1 = new javax.swing.JMenuItem();
        jMenuItem2 = new javax.swing.JMenuItem();
        menu_Cerrar = new javax.swing.JMenuItem();
        jMenu2 = new javax.swing.JMenu();
        menu_Usuario = new javax.swing.JMenuItem();
        menu_Tecnico = new javax.swing.JMenuItem();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Practica 1");
        setBackground(new java.awt.Color(153, 255, 255));
        setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        setResizable(false);

        txt_Entrada.setColumns(20);
        txt_Entrada.setRows(5);
        jScrollPane1.setViewportView(txt_Entrada);

        txt_Salida.setEditable(false);
        txt_Salida.setColumns(20);
        txt_Salida.setForeground(new java.awt.Color(51, 51, 51));
        txt_Salida.setRows(5);
        txt_Salida.setText("//Codigo analizado...");
        jScrollPane2.setViewportView(txt_Salida);

        btn_Generar.setText("Generar automata");

        btn_Analizar.setText("Analizar entradas");
        btn_Analizar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_AnalizarActionPerformed(evt);
            }
        });

        javax.swing.tree.DefaultMutableTreeNode treeNode1 = new javax.swing.tree.DefaultMutableTreeNode("Expresión regular");
        javax.swing.tree.DefaultMutableTreeNode treeNode2 = new javax.swing.tree.DefaultMutableTreeNode("AFD");
        javax.swing.tree.DefaultMutableTreeNode treeNode3 = new javax.swing.tree.DefaultMutableTreeNode("-");
        treeNode2.add(treeNode3);
        treeNode1.add(treeNode2);
        treeNode2 = new javax.swing.tree.DefaultMutableTreeNode("Arbol");
        treeNode3 = new javax.swing.tree.DefaultMutableTreeNode("-");
        treeNode2.add(treeNode3);
        treeNode1.add(treeNode2);
        treeNode2 = new javax.swing.tree.DefaultMutableTreeNode("Tabla de siguientes");
        treeNode3 = new javax.swing.tree.DefaultMutableTreeNode("-");
        treeNode2.add(treeNode3);
        treeNode1.add(treeNode2);
        treeNode2 = new javax.swing.tree.DefaultMutableTreeNode("Tabla de trancisiones");
        treeNode3 = new javax.swing.tree.DefaultMutableTreeNode("-");
        treeNode2.add(treeNode3);
        treeNode1.add(treeNode2);
        tree_Archivos.setModel(new javax.swing.tree.DefaultTreeModel(treeNode1));
        jScrollPane3.setViewportView(tree_Archivos);

        cb_Img.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "--->Seleccione una imagen<---" }));
        cb_Img.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cb_ImgActionPerformed(evt);
            }
        });

        btn_Anterior.setText("Anterior");

        panel_Img.setBorder(new javax.swing.border.MatteBorder(null));

        javax.swing.GroupLayout panel_ImgLayout = new javax.swing.GroupLayout(panel_Img);
        panel_Img.setLayout(panel_ImgLayout);
        panel_ImgLayout.setHorizontalGroup(
            panel_ImgLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );
        panel_ImgLayout.setVerticalGroup(
            panel_ImgLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );

        btn_Siguiente.setText("Siguiente");

        jMenu1.setText("Archivo");

        menu_Abrir.setText("Abrir");
        menu_Abrir.setPreferredSize(new java.awt.Dimension(150, 22));
        menu_Abrir.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menu_AbrirActionPerformed(evt);
            }
        });
        jMenu1.add(menu_Abrir);

        jMenuItem1.setText("Guardar");
        jMenuItem1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem1ActionPerformed(evt);
            }
        });
        jMenu1.add(jMenuItem1);

        jMenuItem2.setText("Guardar como");
        jMenuItem2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem2ActionPerformed(evt);
            }
        });
        jMenu1.add(jMenuItem2);

        menu_Cerrar.setText("Cerrar");
        menu_Cerrar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menu_CerrarActionPerformed(evt);
            }
        });
        jMenu1.add(menu_Cerrar);

        jMenuBar1.add(jMenu1);

        jMenu2.setText("Ver");

        menu_Usuario.setText("Manual de usuario");
        jMenu2.add(menu_Usuario);

        menu_Tecnico.setText("Manual técnico");
        jMenu2.add(menu_Tecnico);

        jMenuBar1.add(jMenu2);

        setJMenuBar(jMenuBar1);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                    .addComponent(jScrollPane2)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 304, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addComponent(btn_Generar, javax.swing.GroupLayout.PREFERRED_SIZE, 140, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(btn_Analizar, javax.swing.GroupLayout.PREFERRED_SIZE, 130, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jScrollPane3, javax.swing.GroupLayout.PREFERRED_SIZE, 194, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                            .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                                .addComponent(btn_Anterior, javax.swing.GroupLayout.PREFERRED_SIZE, 138, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 53, Short.MAX_VALUE)
                                .addComponent(btn_Siguiente, javax.swing.GroupLayout.PREFERRED_SIZE, 138, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addComponent(slide_Img, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(panel_Img, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(cb_Img, 0, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(cb_Img, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(panel_Img, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(slide_Img, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(btn_Anterior, javax.swing.GroupLayout.PREFERRED_SIZE, 31, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(btn_Siguiente, javax.swing.GroupLayout.PREFERRED_SIZE, 31, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addComponent(jScrollPane3, javax.swing.GroupLayout.DEFAULT_SIZE, 353, Short.MAX_VALUE)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addComponent(jScrollPane1)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(btn_Analizar, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(btn_Generar, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 112, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void cb_ImgActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cb_ImgActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_cb_ImgActionPerformed

    
    //                                  ARCHIVO
    //**************************************************************************
    //**************************************************************************
    //ABRIR
    private void menu_AbrirActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menu_AbrirActionPerformed
        txt_Entrada.setText(archivos.Abrir());
    }//GEN-LAST:event_menu_AbrirActionPerformed
    //GUARDAR
    private void jMenuItem1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem1ActionPerformed
        if(archivos.existePath()) archivos.Guardar(txt_Entrada.getText());
        else archivos.GuardarC(txt_Entrada.getText());
    }//GEN-LAST:event_jMenuItem1ActionPerformed
    //GUARDAR COMO
    private void jMenuItem2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem2ActionPerformed
        archivos.GuardarC(txt_Entrada.getText());
    }//GEN-LAST:event_jMenuItem2ActionPerformed
    //CERRAR
    private void menu_CerrarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menu_CerrarActionPerformed
        this.dispose();
    }//GEN-LAST:event_menu_CerrarActionPerformed

    private void btn_AnalizarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_AnalizarActionPerformed
        analizador = new Analizador(txt_Entrada.getText());
        if(analizador.getExito()) txt_Salida.setText("Bien");
        else txt_Salida.setText("Error al analizar...\n" + analizador.getSalida());
    }//GEN-LAST:event_btn_AnalizarActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Practica1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Practica1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Practica1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Practica1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Practica1().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btn_Analizar;
    private javax.swing.JButton btn_Anterior;
    private javax.swing.JButton btn_Generar;
    private javax.swing.JButton btn_Siguiente;
    private javax.swing.JComboBox cb_Img;
    private javax.swing.JMenu jMenu1;
    private javax.swing.JMenu jMenu2;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JMenuItem jMenuItem1;
    private javax.swing.JMenuItem jMenuItem2;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JScrollPane jScrollPane3;
    private javax.swing.JMenuItem menu_Abrir;
    private javax.swing.JMenuItem menu_Cerrar;
    private javax.swing.JMenuItem menu_Tecnico;
    private javax.swing.JMenuItem menu_Usuario;
    private javax.swing.JPanel panel_Img;
    private javax.swing.JSlider slide_Img;
    private javax.swing.JTree tree_Archivos;
    private javax.swing.JTextArea txt_Entrada;
    private javax.swing.JTextArea txt_Salida;
    // End of variables declaration//GEN-END:variables
}
