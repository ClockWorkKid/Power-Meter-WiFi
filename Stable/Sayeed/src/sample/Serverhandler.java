package sample;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Serverhandler implements Runnable {
    /*
    serverSocket is the object which handles all the necessary stuff for a server.
     */
    public static ServerSocket serverSocket;

    /*
    socket represents the client PC that is connected to the serversocket.
    In our case, the client PC is the ESP module
     */
    public Socket socket;

    /*
    This portion creates the thread.
    To create a thread, we have to do three things
    1) create a class (in our case, it's Serverhandler)
    2) Serverhandler should inherit from Runnable
    3) make a Thread object inside the Serverhandler (in our case, it's 't')
    4) initialize the Thread object t and
    5) start the thread
     */
    Thread t;
    public Serverhandler() {
        t= new Thread(this);
        t.start();
    }

    @Override
    public void run() {
    /*
    This is the program which runs parallel to the main() function of 'Main' Class.
    This code
     */

        try {
            serverSocket=new ServerSocket(11500);
            /*
            This line creates a server which is configured to port 11500
             */
        } catch (IOException e) {
            System.out.println("Couldn't open ServerSocket at port 11500");
        }

        while (!Main.exitFlag){
            System.out.println("open");
            try {
                /*
                The server then waits to accept a client on port 11500. The program doesn't proceed anymore.
                 */
                socket=serverSocket.accept();

                /*
                The program proceeds when a client is connected. The serverSocket creates a 'Socket'
                object which is assigned to 'socket'
                 */
            } catch (IOException e) {
                System.out.println("ServerSocket closed");
            }
            System.out.println("Connection complete");

            /*
            This line creates a new thread for that specific client.
            the socket object is passed to handle all the necessary part for networking in that thread
             */
            ClientHandler clientHandler=new ClientHandler(socket);




            Thread thread=new Thread(clientHandler);
            thread.start();

            System.out.println("client connected");
             }



    }
}
