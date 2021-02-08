package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.*;


public class Main extends Application {
    /*
    * This is the Main class which starts everything.
    *
    * */


    /*
    Note on static variables:
    you can access the static variables of 'Main' class from any other class without creating any object of 'Main'
     */

    public static Stage myStage;
    /*
    A 'Stage' is the window you see on which the GUI is loaded.
     */


    public static float voltage=0;
    public static float current=0;
    public static float power=0;
    /*
    The data sent from ESP is stored in these three variables
     */

    public static boolean exitFlag=false;
    /*
    These flag is assigned true if the GUI is closed. This flag is used to close a the serversocket so that
    the program can close itself.
     */

    public static String username="";
    public static String password="";
    /*
    These two strings are used to store your login information.
     */



    /*
    'start' function is called when the main function calls launch(args)
     */
    @Override
    public void start(Stage primaryStage) throws Exception{
        /*
        In this project, a GUI is representated by the fxml file. The fxml file looks similar to
        html and it consists everything needed to show on the screen. The root container is the parent of all
        the tags present in the fxml file
         */
        Parent root = FXMLLoader.load(getClass().getResource("start.fxml"));

        /*
        As you can see, when the 'start' function is called, a 'primaryStage' object of 'Stage' class is created and
        passed and it is assigned to the static 'myStage' variable so that the created stage object can be
        accessed from any other class so that the contents of the stage can be changed.
         */
        myStage= primaryStage;

        /*
        'Start Page' is shown as title on the newly created window
         */
        myStage.setTitle("Start Page");

        /*
        the root tag of the fxml is used to create a 'Scene' object of resolution 600 x 400.
        The newly created 'Scene' object has been set as the scene on the stage.
        Alternate line for the code below:

        Scene scene = new Scene(root,600,400);
        myStage.setScene(scene);

         */
        myStage.setScene(new Scene(root, 600, 400));

        /*
        Finally, after setting the scene, the myStage can be showed to the user.
         */
        myStage.show();
    }


    public static void main(String[] args) {
        loadUserInfo();

        /*
        This line initiates a different portion of code known as a thread.
        This seperately running code handles all the work for the server.
         */
        Serverhandler serverhandler= new Serverhandler();

        /*
        This function calls the start() function of 'Main'. The code doesn't progress further from here because
        a GUI is created. This main function will progress from this point whenever the GUI is exited
         */
        launch(args);

        /*
        If the code reaches this portion, it means that the user exited the GUI. So we set the exitFlag to 'true'
         */
        exitFlag=true;


        try {
            /*
            we close the serverSocket situated in the Serverhandler.
             */
            Serverhandler.serverSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void loadUserInfo()
    {
        /*
        This function's sole purpose is to load the username and password from the 'userinfo' file
         */
        try {

            /*
            In summary, these two lines are used to create the 'br' BufferedReader object to read lines
             */
            FileInputStream fstream = new FileInputStream("src/sample/userinfo");
            BufferedReader br = new BufferedReader(new InputStreamReader(fstream));

            String strLine;
            while ((strLine = br.readLine()) != null) {
                /*
                    strLine = br.readLine()
                    this function reads a line from the file and and puts the line in
                    'strLine'
                 */

                String[] splitted = strLine.split(" ");
                /*
                strLine.split(" ") splits the string into an array of strings.
                For example, the string
                "Sayeed 123456" will be split into "Sayeed" and "123456"
                 */

                /*
                Finally, the split parts are stored as the username and the password for this program.
                 */
                username= splitted[0];
                password= splitted[1];

            }
            /*
            This line closes everything needed to read the file.
             */
            fstream.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }


    public static void saveUserinfo(){

        /*
        This portion only creates the userinfo file to save the username and password
         */
        BufferedWriter bw = null;
        try {
            File file = new File("src/sample/userinfo");

            if (!file.exists()) {
                file.createNewFile();
            }
            FileWriter fw = new FileWriter(file);
            bw = new BufferedWriter(fw);


            /*
            The two strings are concatenated with a 'space' and then written to the file.
             */
            bw.write(Main.username+" "+Main.password);

        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
        finally
        {
            /*
            This portion closes all the necessary stuff for writing to the file
             */
            try{
                if(bw!=null)
                    bw.close();
            }catch(Exception ex){
                System.out.println("Error in closing the BufferedWriter"+ex);
            }
        }

    }
}
