/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication2;

/**
 *
 * @author Pablo-Por
 */
import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.*;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;
import com.fazecast.jSerialComm.SerialPort;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import javax.swing.BoxLayout;
public class JavaApplication2 {



	
static int cont=0;	
static SerialPort chosenPort;

	public static void main(String[] args) {
		
            
		// create and configure the window
		JFrame window = new JFrame();
		window.setTitle("Arduino LCD Clock");
		window.setSize(400, 75);
		window.setLayout(new BorderLayout());
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		// create a drop-down box and connect button, then place them at the top of the window
		JComboBox<String> portList = new JComboBox<String>();
		JButton connectButton = new JButton("Connect");
		JPanel topPanel = new JPanel();
		topPanel.add(portList);
		topPanel.add(connectButton);	
                    
             
		window.add(topPanel, BorderLayout.NORTH);
		
		// populate the drop-down box
		SerialPort[] portNames = SerialPort.getCommPorts();
		for(int i = 0; i < portNames.length; i++)
			portList.addItem(portNames[i].getSystemPortName());
		
             
		// configure the connect button and use another thread to send data
		connectButton.addActionListener(new ActionListener(){
			@Override public void actionPerformed(ActionEvent arg0) {
				if(connectButton.getText().equals("Connect")) {
					// attempt to connect to the serial port
					chosenPort = SerialPort.getCommPort(portList.getSelectedItem().toString());
					chosenPort.setComPortTimeouts(SerialPort.TIMEOUT_SCANNER, 0, 0);
					if(chosenPort.openPort()) {
						connectButton.setText("Disconnect");
						portList.setEnabled(false);
                                                int nm;
			
                         JPanel botones= new JPanel();
                         botones.setLayout(new BoxLayout(botones, BoxLayout.Y_AXIS));
                        JButton	jbAceleterar = new JButton("Acelerar");
			jbAceleterar.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent me) {
			// enter an infinite loop that sends text to the arduino
			PrintWriter output = new PrintWriter(chosenPort.getOutputStream());					
			output.print("3");
			output.flush();
                        }				
		});
                jbAceleterar.setLocation(0, 0);  
                jbAceleterar.setSize(50, 100);
                botones.add(jbAceleterar);
             
                   JPanel move=new JPanel();
                
                   JButton	jbIzquierda = new JButton("Izquierda");
			jbIzquierda.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent me) {
				// enter an infinite loop that sends text to the arduino
			PrintWriter output = new PrintWriter(chosenPort.getOutputStream());					
			output.print("1");
			output.flush();
			}
		});  
                jbIzquierda.setSize(50, 100);
                move.add(jbIzquierda);
              
                 JButton	jbParar = new JButton("Parar");
			jbParar.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent me) {
				// enter an infinite loop that sends text to the arduino
			PrintWriter output = new PrintWriter(chosenPort.getOutputStream());					
			output.print("5");
			output.flush();
			}
		});  
                jbParar.setSize(50, 100);
                move.add(jbParar);
                botones.add(move);
                  JButton	jbDerecha = new JButton("Derecha");
			jbDerecha.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent me) {
                            // enter an infinite loop that sends text to the arduino
			PrintWriter output = new PrintWriter(chosenPort.getOutputStream());					
			output.print("2");
			output.flush();
				
			}
		});  
                jbDerecha.setSize(50, 100);
                move.add(jbDerecha);
                botones.add(move);
                
                JButton	jbMarchaAtras = new JButton("marcha atras");
			jbMarchaAtras.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent me) {
				// enter an infinite loop that sends text to the arduino
			PrintWriter output = new PrintWriter(chosenPort.getOutputStream());					
			output.print("4");
			output.flush();
			}
		});  
                jbMarchaAtras.setSize(50, 100);
                 botones.add(jbMarchaAtras);
                 
                window.add(botones);
                    
						// create a new thread for sending data to the arduino
						Thread thread = new Thread(){
							@Override public void run() {
                                                            
                                                          
                                                            
                                                            Scanner scanner=new Scanner (chosenPort.getInputStream());
                                                            
                                                            while (scanner.hasNextLine())
                                                            {
                                                                String res=scanner.nextLine();
                                                                if (res.compareToIgnoreCase("alarma")==0)
                                                                {
                                                                    cont++;
                                                                    
                                                                        System.out.println(res);
                                                                        try {
                                                                        String cmd = "raspistill -o /home/pi/Pictures/Imagen"+cont+".jpg"; //Comando de apagado en linux
                                                                        Runtime.getRuntime().exec(cmd);
                                                                        
                                                                       Thread.sleep(6000);
                                                                        cmd = "/home/pi/dropbox_uploader.sh upload /home/pi/Pictures/Imagen"+cont+".jpg /fotosRaspberry"; //Comando de apagado en linux
                                                                        Runtime.getRuntime().exec(cmd);
                                                                     
                                                                    } catch (IOException ioe) {
                                                                            System.out.println (ioe);
                                                                    }catch(InterruptedException e){}
                                                                    
                                                                    
                                                                    
                                                                    
                                                                }
                                                                     
                                                               
                                                            }
                                                             scanner.close();
								// wait after connecting, so the bootloader can finish
								try {Thread.sleep(100); } catch(Exception e) {}

								
							}
						};
						thread.start();
					}
				} else {
					// disconnect from the serial port
					chosenPort.closePort();
					portList.setEnabled(true);
					connectButton.setText("Connect");
				}
			}
		});
		
		// show the window
		window.setVisible(true);
	}
}
