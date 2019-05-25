import java.net.*;
import java.io.*;
 
public class Client
{
    public static void main(String [] args)
    {
        String serverName = args[0];
        int port = Integer.parseInt(args[1]);
        try
        {
			long t1=System.currentTimeMillis();
            //java.net.Socket 类代表客户端和服务器都用来互相沟通的套接字
            Socket cSocket = new Socket(serverName, port);
            //Socket cSocket = new Socket("119.23.229.178", port);
            // getRemoteSocketAddress() 返回对端地址，如果未连接则返回 null。
            System.out.println(" Connected to remote server " + cSocket.getRemoteSocketAddress());

            // getOutputStream() 返回此套接字的输出流
            OutputStream outToServer = cSocket.getOutputStream();
            DataOutputStream out = new DataOutputStream(outToServer);
            //out.writeUTF("I am client " + cSocket.getLocalSocketAddress());
            String url = args[2];
            out.writeUTF( url );
            System.out.println( "Client: " + url );

            //  getInputStream() 返回此套接字的输入流
            InputStream inFromServer = cSocket.getInputStream();
            DataInputStream in = new DataInputStream(inFromServer);

			String buf = null;
            PrintWriter pw = null;
            pw = new PrintWriter(new FileWriter("/root/result.html"), true);
            while ((buf = in.readUTF()) != null) 
            {
                pw.println( buf );
                //System.out.println( buf );
            }
            System.out.println( "Client: Result wrote to /root/result.html " );
            pw.close();

            //System.out.println( "Server: " + in.readUTF());
			long t2=System.currentTimeMillis();
			System.out.println(t2-t1);

            cSocket.close();
        }catch(IOException e)
        {
            e.printStackTrace();
        }
    }
}
