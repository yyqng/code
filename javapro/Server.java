// 文件名 Server.java
 
import java.net.*;
import java.io.*;

//关于继承
//1. extends :继承父类 Thread ， Thread 不能为 final 或者 abstract
//2. JAVA 中不支持多重继承，但 implements 可以实现多个接口( interface )
public class Server extends Thread
{
    private ServerSocket sSocket;
   
    public Server(int port) throws IOException
    {
         //使用 java.net.ServerSocket 类以创建绑定到特定端口的服务器套接字
         sSocket = new ServerSocket(port);
         //通过指定超时值启用/禁用 SO_TIMEOUT，以毫秒为单位。
         sSocket.setSoTimeout(100000);
    }
 
    public void run()
    {
        while(true)
        {
            try
            {
                //getLocalPort()：返回本端侦听端口
                //System.out.println("Server port : " + sSocket.getLocalPort() + "...");
                //服务器通过accept()侦听并接受客户端的连接,获得一个 Socket 对象
                Socket server = sSocket.accept();
                long t1=System.currentTimeMillis();
                // getRemoteSocketAddress() 返回远端的地址，如果未连接则返回 null。
                System.out.println("Conneted to remote client " + server.getRemoteSocketAddress());

                // getInputStream() 返回此套接字的输入流
                DataInputStream in = new DataInputStream(server.getInputStream());
				String surl = in.readUTF();
                URL url = new URL(surl);
                System.out.println( "Client: " + surl );
                // getOutputStream() 返回此套接字的输出流
                DataOutputStream out = new DataOutputStream(server.getOutputStream());

				URLConnection urlconn = null;
				urlconn = url.openConnection();
                BufferedReader br = null;
                br = new BufferedReader(new InputStreamReader( urlconn.getInputStream()));
				String buf = null;

                PrintWriter pw = null;
                pw = new PrintWriter(new FileWriter("/root/result.html"), true);
                while ((buf = br.readLine()) != null) 
				{
                    pw.println( buf );
                    out.writeUTF( buf );
                    //System.out.println( buf );
            	}
                System.out.println( "Result wrote to /root/result.html " );
                pw.close(); 

                //out.writeUTF("I am server, " + server.getLocalSocketAddress() + ", Goodbye!");
                server.close();
                long t2=System.currentTimeMillis();
                System.out.println(t2-t1);
            }catch(SocketTimeoutException s)
            {
                 System.out.println("Socket timed out!");
                 break;
            }catch(IOException e)
            {
                 e.printStackTrace();
                 break;
            }
        }
    }
    public static void main(String [] args)
    {
         int port = Integer.parseInt(args[0]);
         try
         {
 	         //实例化一个 ServerSocket 对象
              Thread t = new Server(port);
              t.run();
         }catch(IOException e)
         {
              e.printStackTrace();
         }
    }
}
