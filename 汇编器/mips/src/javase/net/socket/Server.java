package javase.net.socket; 
import java.io.DataInputStream; 
import java.io.DataOutputStream; 
import java.io.IOException; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.net.ServerSocket; 
import java.net.Socket; 

public class Server{ 
    public static void main(String[] args) { 
        try { 
            ServerSocket serverSocket = new ServerSocket(8887); 
            Socket socket = serverSocket.accept(); 
            // 读取客户端数据 
            InputStream info = socket.getInputStream(); 
            DataInputStream dis = new DataInputStream(info); 
            System.out.println(dis.readUTF()); 
            
            for(int j = 1; j <= 100; j++){
            OutputStream os = socket.getOutputStream(); 
            DataOutputStream dos = new DataOutputStream(os); 
            dos.writeUTF("Hihihi!"); 
            dos.flush(); 
            }
            
        } catch (IOException e) { 
            e.printStackTrace(); 
        } 
    } 
}  