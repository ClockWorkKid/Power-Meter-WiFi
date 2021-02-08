package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;

import java.net.ServerSocket;
import java.net.Socket;
import java.net.URL;
import java.util.ResourceBundle;


public class StartController implements Initializable {
    public Button signInButton;
    public TextField passwordField;
    public TextField userField;
    public Text notification;

    public void signinAction(ActionEvent actionEvent) {
        /*
        This is the function which is called when the sign in button is pressed
         */

        /*
        Load the username and password from the file
         */
        Main.loadUserInfo();

        /*
        get the necessary texts from the GUI and check whether the texts from the GUI matches with the
        texts from the file
         */
        if(Main.username.equals(userField.getText())&& Main.password.equals(passwordField.getText())) {
            try {
                /*
                Change screen
                 */
                Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));

                Main.myStage.setTitle("Menu Page");
                Main.myStage.setScene(new Scene(root, 600, 400));
                Main.myStage.show();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }else{
            /*
            If the username or password from the GUI are wrong,
             */
            notification.setText("Wrong username/ password");
            notification.setVisible(true);
        }


    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {

    }
}
