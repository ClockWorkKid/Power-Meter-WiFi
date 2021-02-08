package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;

import java.net.URL;
import java.util.ResourceBundle;

public class MenuController implements Initializable {
    public Button livefeedButton;
    public Button duebillButton;
    public Button historyButton;
    public Button userinfoButton;
    public Button signoutButton;

    public void livefeedAction(ActionEvent actionEvent){
        try {
            Parent root = FXMLLoader.load(getClass().getResource("livefeed.fxml"));

            Main.myStage.setTitle("Feed Page");
            Main.myStage.setScene(new Scene(root, 600, 400));
            Main.myStage.show();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    public void duebillAction(ActionEvent actionEvent) {
        try {
            Parent root = FXMLLoader.load(getClass().getResource("duebill.fxml"));

            Main.myStage.setTitle("Bill Page");
            Main.myStage.setScene(new Scene(root, 600, 400));
            Main.myStage.show();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    public void historyAction(ActionEvent actionEvent) {
        try {
            Parent root = FXMLLoader.load(getClass().getResource("history.fxml"));

            Main.myStage.setTitle("History Page");
            Main.myStage.setScene(new Scene(root, 650, 470));
            Main.myStage.show();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    public void userinfoAction(ActionEvent actionEvent) {
        try {
            Parent root = FXMLLoader.load(getClass().getResource("userinfo.fxml"));

            Main.myStage.setTitle("User Page");
            Main.myStage.setScene(new Scene(root, 600, 400));
            Main.myStage.show();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    public void signoutAction(ActionEvent actionEvent) {
        try {
            Main.password="";
            Main.username="";
            Parent root = FXMLLoader.load(getClass().getResource("start.fxml"));

            Main.myStage.setTitle("Start Page");
            Main.myStage.setScene(new Scene(root, 600, 400));
            Main.myStage.show();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {

    }
}
