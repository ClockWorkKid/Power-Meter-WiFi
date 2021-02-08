package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.*;


public class Main extends Application {

    public static Stage myStage;
    public static float voltage=0;
    public static float current=0;
    public static float power=0;
    public static boolean exitFlag=false;
    public static String username="";
    public static String password="";



    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("start.fxml"));
        myStage= primaryStage;
        myStage.setTitle("Start Page");
        myStage.setScene(new Scene(root, 600, 400));
        myStage.show();
    }


    public static void main(String[] args) {
        loadUserInfo();
        Serverhandler serverhandler= new Serverhandler();
        launch(args);
        exitFlag=true;
        try {
            Serverhandler.serverSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void loadUserInfo()
    {
        try {

            FileInputStream fstream = new FileInputStream("src/sample/userinfo");
            //FileInputStream fstream = new FileInputStream("sample/userinfo");
            BufferedReader br = new BufferedReader(new InputStreamReader(fstream));

            String strLine;
            while ((strLine = br.readLine()) != null) {
                String[] splitted = strLine.split(" ");
                username= splitted[0];
                password= splitted[1];
            }
            fstream.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
    public static void saveUserinfo(){
        BufferedWriter bw = null;
        try {
            File file = new File("src/sample/userinfo");

            if (!file.exists()) {
                file.createNewFile();
            }

            FileWriter fw = new FileWriter(file);
            bw = new BufferedWriter(fw);
            bw.write(Main.username+" "+Main.password);

        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
        finally
        {
            try{
                if(bw!=null)
                    bw.close();
            }catch(Exception ex){
                System.out.println("Error in closing the BufferedWriter"+ex);
            }
        }

    }
}
