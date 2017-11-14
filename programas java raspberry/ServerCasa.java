/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servercasa;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 *
 * @author pi
 */
public class ServerCasa {

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
			
               
                    
						Thread thread;
                                            thread = new Thread(){
                                                @Override public void run() {
                                                    
                                                    
                                                    int port=1234;
                                                    String lin="";
                                                    BufferedReader entra;
                                                    Socket conecta=null;
                                                    PrintWriter output = null;
                                                    ServerSocket welcome = null;
                                                    while(true)
                                                    {
                                                    try{
                                                        welcome = new ServerSocket(port);
                                                        conecta = welcome.accept();
                                                        System.out.println("Conectado a "+conecta.getInetAddress()+":"+conecta.getPort());
                                                       
                                                        while (true){  //trabajar infinitamente
                                                            //espera que alguien quiera conectarse
                                                           
                                                                
                                                            entra = new BufferedReader(
                                                                    new InputStreamReader(conecta.getInputStream()));
                                                            //  DataOutputStream sale = new DataOutputStream(conecta.getOutputStream());
                                                            int servomover = entra.read();  //Esperando que le envÃ­en el texto a convertir
                                                             //enter an infinite loop that sends text to the arduino
                                                            output = new PrintWriter(chosenPort.getOutputStream());					
                                                            System.out.println( servomover);
                                                            output.print( servomover);
                                                            output.flush();
                                                        }
                                                        
                                                    }catch(Exception e)
                                                    {
                                                        try {
                                                         output = new PrintWriter(chosenPort.getOutputStream());					
                                                         output.print(0);
                                                        conecta.close();
                                                        welcome.close();
                                                        } catch (Exception ex) {}
                                                         System.out.println("se ha cerrado la conexion por seguridad se va apara el coche STOP!!0 ");
           
                                                    }
                                                 }
                                                    
                                                   
                                                    
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
  
  
    
    
