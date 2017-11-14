package capturescreen;
import java.awt.*;
import java.awt.image.*;
import java.io.*;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import javax.imageio.ImageIO;

public class capturaScreen {

	
	static public void capturaPantalla(String fileName) throws Exception {
	Dimension screenSize = java.awt.Toolkit.getDefaultToolkit().getScreenSize();
	Rectangle screenRectangle = new Rectangle(screenSize);
	Robot robot = new Robot();
	BufferedImage image = robot.createScreenCapture(screenRectangle);
	ImageIO.write(image, "jpg", new File(fileName));
	}
	
	
	
	public static void main(String[] args) {
	
		
	    
	    int hora;
	    int min;
	    int seg;
	    int cont=0;
	    while(true)
	    {
	    	// (1) get today's date
		    Date today = Calendar.getInstance().getTime();
	    	hora=today.getHours();
	    	min=today.getMinutes();
               
	    	 try {
				Thread.sleep(15000);} catch (InterruptedException e1) {}
	    //	if (hora > 7 && hora<22)
	    //	{
	    		if (min%15==0 )
	    		{
	    		     
	    			try{
                                    String cmd = "raspistill -o /home/pi/Pictures/ImagenRaspi"+cont+".jpg"; //Comando de apagado en linux
                                    Runtime.getRuntime().exec(cmd);
	    		       Thread.sleep(5000);
                                     String FILENAME="/home/pi/Pictures/ImagenCamSegu"+cont+".jpg";
                                     capturaScreen.capturaPantalla(FILENAME);
                                     Thread.sleep(10000);
                                     cmd = "/home/pi/dropbox_uploader.sh upload /home/pi/Pictures/ImagenRaspi"+cont+".jpg /fotosRaspberry"; //Comando de apagado en linux
                                    Runtime.getRuntime().exec(cmd);
                                    Thread.sleep(5000);
	    			  cmd = "/home/pi/dropbox_uploader.sh upload  /home/pi/Pictures/ImagenCamSegu"+cont+".jpg /fotosRaspberry"; //Comando de apagado en linux
	    			     Runtime.getRuntime().exec(cmd);
	    			 Thread.sleep(45000);
                                 System.out.println("foto sacada > "+cont);

	    			 cont++;
	    			}
	    			catch(Exception e)
	    			{
	    			e.printStackTrace();
	    			}
	    			
	    		}
	    		
	    	}
	    //}
	    	
	    
	}
	}
	//end of class Captura



