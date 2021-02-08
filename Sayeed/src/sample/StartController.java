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
        Main.loadUserInfo();
        if(Main.username.equals(userField.getText())&& Main.password.equals(passwordField.getText())) {
            try {
                Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));

                Main.myStage.setTitle("Menu Page");
                Main.myStage.setScene(new Scene(root, 600, 400));
                Main.myStage.show();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }else{
            notification.setText("Wrong username/ password");
            notification.setVisible(true);
        }


    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {

    }
}
