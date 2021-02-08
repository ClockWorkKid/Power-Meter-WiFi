package sample;

import java.io.*;
import java.net.Socket;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;

public class ClientHandler implements Runnable {
    /*
    two necessary objects to handle networking
     */
    BufferedReader bufferedReader;
    PrintWriter printWriter;

    Socket client;
    /*
    This represents the socket of the client created by the serverSocket
     */

    String data;
    /*
    A variable to store a line sent from the server
     */

    public static int count=0;
    /*
    This static variable keeps count of the number of connected clients
     */

    static ArrayList<Float> bufferedPower= new ArrayList<>();
    /*
    This array is a temporary store house to keep 10 readings of power.
    After saving 10 readings into the bufferedPower, the readings are then written to the file 'append'
     */
    public ClientHandler(Socket socket) {
        client=socket;

        count++;
        /*
        increment counter because a new client has been connected
         */

        System.out.println("Created thread for client "+count);
        System.out.println("");
        try {
            /*
            bufferedReader will handle everything necessary to read data from server
            printWriter will handle evrything necessary to send data to server
             */
            bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            printWriter = new PrintWriter(socket.getOutputStream());
        } catch (Exception e) {
            System.out.println("Couldn't create ClientHandler");
        }
    }

    @Override
    public void run() {
        /*
        A counter to keep track whether 10 reading have been read.
         */
        int bufferCounter=0;

        /*
        This loop will iterate till the GUI closes.
        Main.exitFlag will be assigned 'false' when the GUI is closed.


         */
        while(!Main.exitFlag){

            try {
                /*
                read a line from the server
                 */
                data = bufferedReader.readLine();
            } catch (IOException e) {
                System.out.println("Couldn't readLine from BufferedReader");
            }
            if(data!=null && data.length()!=0) {
                /*
                This branch will be active if a valid string is read from the server.
                 */

                    String[] splitted= data.split(" ");
                    /*
                    Split the string sent from the server.
                     */

                    Main.current=Float.parseFloat(splitted[1]);
                    Main.voltage= Float.parseFloat(splitted[0]);
                    Main.power= Float.parseFloat(splitted[2]);
                    /*
                    convert the strings into floats and assign the readings to the static variables of main
                    for further uses.
                     */

                    System.out.println(Main.current+" "+Main.voltage+" "+Main.power);


                    bufferedPower.add(Main.power);
                    /*
                    Add a reading to the array
                     */
                    bufferCounter++;

                    /*
                    check whether 10 readings have been recorded
                     */
                    if(bufferCounter==10)
                    {
                        /*
                        Save the recorded 10 reading in the file 'append' power
                         */
                        appendPower();

                        /*
                        reset the array
                         */
                        bufferedPower= new ArrayList<>();
                        bufferCounter=0;
                    }

                }

        }
    }
    public static void appendPower(){
        try {
            /*This function writes the total of the 10 power readings to the file append*/
            File file = new File("src/sample/append");
            FileWriter fr = new FileWriter(file, true);
            BufferedWriter br = new BufferedWriter(fr);

            Double sumBuffer= 0d;
            /*
            a variable to keep the sum of 10 power readings
             */
            for(int i = 0; i<10;i++){
                sumBuffer+=bufferedPower.get(i);
            }

            /*Get the current from the system*/
            DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
            LocalDateTime now = LocalDateTime.now();
            dtf.format(now);

            /*
            Write the current time and the sum of 10 power readings to the file
             */
            br.write(dtf.format(now)+" "+String.valueOf(sumBuffer)+"\n");

            /*
            close the file
             */
            br.close();
            fr.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
