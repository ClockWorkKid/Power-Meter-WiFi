package sample;

import java.io.*;
import java.net.Socket;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;

public class ClientHandler implements Runnable {
    BufferedReader bufferedReader;
    PrintWriter printWriter;
    Socket client;
    String data;

    public static int count=0;

    static ArrayList<Float> bufferedPower= new ArrayList<>();
    public ClientHandler(Socket socket) {
        client=socket;
        count++;
        System.out.println("Created thread for client "+count);
        System.out.println("");
        try {
            bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            printWriter = new PrintWriter(socket.getOutputStream());
        } catch (Exception e) {
            System.out.println("Couldn't create ClientHandler");
        }
    }

    @Override
    public void run() {
        int bufferCounter=0;
        while(!Main.exitFlag){

            try {
                data = bufferedReader.readLine();
            } catch (IOException e) {
                System.out.println("Couldn't readLine from BufferedReader");
            }
            if(data!=null && data.length()!=0) {
                    String[] splitted= data.split(" ");
                    Main.current=Float.parseFloat(splitted[1]);
                    Main.voltage= Float.parseFloat(splitted[0]);
                    Main.power= Float.parseFloat(splitted[2]);
                    System.out.println(Main.current+" "+Main.voltage+" "+Main.power);


                    bufferedPower.add(Main.power);
                    bufferCounter++;
                    if(bufferCounter==10)
                    {
                        appendPower();
                        bufferedPower= new ArrayList<>();
                        bufferCounter=0;
                    }

                }

        }
    }
    public static void appendPower(){
        try {
            File file = new File("src/sample/append");
            FileWriter fr = new FileWriter(file, true);
            BufferedWriter br = new BufferedWriter(fr);
            Double sumBuffer= 0d;
            for(int i = 0; i<10;i++){
                sumBuffer+=bufferedPower.get(i);
            }

            DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
            LocalDateTime now = LocalDateTime.now();
            dtf.format(now);
            br.write(dtf.format(now)+" "+String.valueOf(sumBuffer)+"\n");

            br.close();
            fr.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
