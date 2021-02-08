package sample;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Serverhandler implements Runnable {
    public static ServerSocket serverSocket;
    public Socket socket;
    Thread t;
    public Serverhandler() {
        t= new Thread(this);
        t.start();
    }

    @Override
    public void run() {


        try {
            serverSocket=new ServerSocket(11500);
        } catch (IOException e) {
            System.out.println("Couldn't open ServerSocket at port 11500");
        }

        while (!Main.exitFlag){
            System.out.println("open");
            try {
                socket=serverSocket.accept();
            } catch (IOException e) {
                System.out.println("ServerSocket closed");
            }
            System.out.println("Connection complete");

            ClientHandler clientHandler=new ClientHandler(socket);
            Thread thread=new Thread(clientHandler);
            thread.start();

            System.out.println("client connected");
             }



    }
}
