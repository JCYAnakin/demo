//client
package javase.net.socket; 

import java.util.Scanner;
import java.io.DataInputStream; 
import java.io.DataOutputStream; 
import java.io.IOException; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.net.Socket; 
import java.net.UnknownHostException; 

public class Client{ 
    public static void main(String[] args) { 
        try {
        	Scanner in = new Scanner(System.in);
        	String s = in.nextLine();
        	
            Socket socket = new Socket(s, 8887); 
            // Ïò·þÎñÆ÷¶Ë·¢ËÍÊý¾Ý 
            OutputStream os =  socket.getOutputStream(); 
            DataOutputStream bos = new DataOutputStream(os); 
            bos.writeUTF("Connect"); 
            bos.flush(); 

            // ½ÓÊÕ·þÎñÆ÷¶ËÊý¾Ý 
            for(int j = 1; j <= 100; j++){
            InputStream is = socket.getInputStream(); 
            DataInputStream dis = new DataInputStream(is); 
            System.out.println(dis.readUTF()); 
            }
         
        } catch (UnknownHostException e) { 
            e.printStackTrace(); 
        } catch (IOException e) { 
            e.printStackTrace(); 
        } 
    } 
}  