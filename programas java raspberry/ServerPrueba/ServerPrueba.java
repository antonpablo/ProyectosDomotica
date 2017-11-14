/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package serverprueba;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;


/**
 *
 * @author Pablo-Por
 */
public class ServerPrueba extends Frame{


	public static void main(String[] args) {
		
          
                        		
                        try{//cosas del arduino
                            String   cmd = "sudo rfcomm bind /dev/rfcomm0 20:16:06:15:26:90  1"; //Comando de apagado en linux
                            Runtime.getRuntime().exec(cmd);
                        }catch(Exception e){System.out.println("yo esta creada la conectividad bluetooth");}
                        
			
			JFrame window = new JFrame("Server Raspberry");
			JPanel ser=new JPanel();
                        JTextArea jtaScreen = new JTextArea();
			jtaScreen.setPreferredSize(new Dimension(700, 350));
			JScrollPane jspScroll = new JScrollPane(jtaScreen, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
					JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
			
			ser.add(jspScroll);
			
			
					

			// quit button
			JButton quitButton = new JButton("Stop Sever");
			quitButton.addMouseListener(new MouseAdapter() {
				public void mouseClicked(MouseEvent me) {
					
					System.exit(0);
				}			
			});
			quitButton.setSize(100, 50);
			ser.add(quitButton,BorderLayout.CENTER);

			window.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
			window.add(ser, BorderLayout.CENTER);
			window.setPreferredSize(new Dimension(750, 450));
			window.pack();
			window.setVisible(true); 
                
                        Hilo1 hilo1= new Hilo1(jtaScreen);
                        Hilo2 hilo2= new Hilo2(jtaScreen);
                        hilo1.start();
                        hilo2.start();
                                               
        }                             
}
  
  
    
    

