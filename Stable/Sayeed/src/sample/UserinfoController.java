package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.text.Text;

import java.net.URL;
import java.util.ResourceBundle;

public class UserinfoController implements Initializable {
    public PasswordField currentField;
    public PasswordField newField;
    public PasswordField confirmField;
    public Button confirmButton;
    public Button backButton;
    public Text notificationText;

    /*
    this function is called when the confirm button is pressed
     */
    public void confirmAction(ActionEvent actionEvent) {
        /*
        check whether the inputs in the texfields are valid
         */
        if(confirmField.getText().equals(newField.getText()) && currentField.getText().equals(Main.password) && confirmField.getText().length()!=0)
        {
            try {
                /*
                save the password to Main.password and file
                 */
                Main.password=confirmField.getText();
                Main.saveUserinfo();

                /*
                Load new scene
                 */
                Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));
                Main.myStage.setTitle("Menu Page");
                Main.myStage.setScene(new Scene(root, 600, 400));
                Main.myStage.show();
            }
            catch (Exception e){
                e.printStackTrace();
            }
        }else{
            /*
            IF the inputs in the textfields are invalid
             */
            notificationText.setText("Error in changing password");
            notificationText.setVisible(true);
        }


    }

    public void backAction(ActionEvent actionEvent) {
        /*
        This method is called when the back button is pressed
         */
        try {
            /*
            load a new scene on stage
             */
            Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));
            Main.myStage.setTitle("Menu Page");
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
