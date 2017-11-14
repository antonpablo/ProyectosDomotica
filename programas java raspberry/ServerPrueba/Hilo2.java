/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package serverprueba;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileReader;
import java.net.ServerSocket;
import java.net.Socket;
import javax.swing.JTextArea;

/**
 *
 * @author Pablo-Por
 */
public class Hilo2 extends  Thread{
   
   private final JTextArea jtaScreen;
   public Hilo2( JTextArea jtaScreen)
   {
       this.jtaScreen=jtaScreen;
   }

    @Override
   public void run() {
    try{
        ServerSocket welcome=new ServerSocket(1235);
        Socket conecta=null;
        
        File archivo= archivo= new File("/dev/rfcomm0");;
        FileReader fr=null;
        BufferedReader br=null;
        String res="";
        while(true)
        {
            try{
            jtaScreen.append("esperando conexion 2....");
            jtaScreen.append("\n");
            conecta = welcome.accept();
            jtaScreen.append("Conectado a  conex 2"+conecta.getInetAddress()+":"+conecta.getPort());
            jtaScreen.append("\n");  
            
            fr= new FileReader(archivo);
            br= new BufferedReader(br);
            DataOutputStream sale = new DataOutputStream(conecta.getOutputStream());
            res=br.readLine();
      
            if (res.equalsIgnoreCase("1"))    
                sale.writeByte(1);
            
            else
                sale.writeByte(1);
            sale.close();
            br.close();
            fr.close();
            conecta.close();
            
            jtaScreen.append("se envio dato por conexion 2");
            jtaScreen.append("\n");
                            
            
            }catch(Exception e){}   
        }
          
    }catch(Exception e){ }  
  }    
}
