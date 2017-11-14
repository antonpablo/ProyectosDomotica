/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package serverprueba;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.FileWriter;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import javax.swing.JTextArea;

/**
 *
 * @author Pablo-Por
 */
public class Hilo1 extends Thread{
    
   private final JTextArea jtaScreen;
   public Hilo1( JTextArea jtaScreen) {  
       this.jtaScreen=jtaScreen; 
   }

    @Override
    public void run() {
        
        try{
       ServerSocket welcome=new ServerSocket(1234);
       Socket conecta;
       BufferedReader  entra;
       PrintWriter pw;
       FileWriter fichero;
      while(true)
       {
        try{   
         jtaScreen.append("esperando conexion 1....");
         jtaScreen.append("\n");
         conecta = welcome.accept();
         jtaScreen.append("Conectado a conex 1"+conecta.getInetAddress()+":"+conecta.getPort());
         jtaScreen.append("\n");                                                     
         
         entra = new BufferedReader(
         new InputStreamReader(conecta.getInputStream()));
                                                                    
         int entradaDato = entra.read();
         jtaScreen.append("el dato leido : " +entradaDato);                                                         
         jtaScreen.append("\n");
         
         if (entradaDato >= 0 && entradaDato <=9)
         {
             fichero = new FileWriter("/dev/rfcomm0",true);
             pw= new PrintWriter(fichero);
             pw.println(fichero);
             Thread.sleep(2000);
             jtaScreen.append("daato enviado ");                                                         
            jtaScreen.append("\n");
            pw.close();
            fichero.close();
         }
         else if (entradaDato== 10  && entradaDato==11)
         {//enviar datos de temperatura y humedad
              
            DataOutputStream sale = new DataOutputStream(conecta.getOutputStream());
            if (entradaDato== 10)
            {
            }
            else 
            {
                sale.writeUTF
            }
         }
         
         entra.close();
         conecta.close();
       }catch(Exception e)   { System.out.println("conecta close ");  }
     }
    } catch(Exception e){}
  }                                          
}
