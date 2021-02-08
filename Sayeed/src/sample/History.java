package sample;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;

public class History{
    public static ArrayList<History> histories = new ArrayList<>();

    public String year,month,day,hour,minute,second;
    public double power;
    public History(String strLine) {
        String[] splitted = strLine.split(" ");
        System.out.println(splitted[0]+" "+splitted[1]+" "+splitted[2]);
        String[] date = splitted[0].split("/");
        String[] time = splitted[1].split(":");
        year=date[0];
        month = date[1];
        day = date[2];
        hour = time[0];
        minute = time[1];
        second = time[2];
        power = Double.parseDouble(splitted[2]);
    }
    public void print(){
        String history="";
        history+=year;history+=" ";
        history+=month;history+=" ";
        history+=day;history+=" ";
        history+=hour;history+=" ";
        history+=minute;history+=" ";
        history+=second;history+=" ";
        history+=power;history+=" ";
        System.out.println(history);
    }
    public static void readHistory(){
        try {

            FileInputStream fstream = new FileInputStream("src/sample/append");
            BufferedReader br = new BufferedReader(new InputStreamReader(fstream));

            String strLine;
            while ((strLine = br.readLine()) != null && strLine.length()!=0) {
                histories.add(new History(strLine));
            }
            fstream.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }

    public static void printHistory()
    {
        for(History h:histories)
        {
            h.print();
        }
    }

    public static String[] getCurrentTime(){
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
        LocalDateTime now = LocalDateTime.now();
        String todayString = dtf.format(now);
        String todaySplit[]= todayString.split(" ");
        String date[]= todaySplit[0].split("/");
        String time[] = todaySplit[1].split(":");

        String returnString[] = new String[6];
        returnString[0]=date[0];
        returnString[1]=date[1];
        returnString[2]=date[2];
        returnString[3]= time[0];
        returnString[4]= time[1];
        returnString[5]= time[2];

        return returnString;

    }
}