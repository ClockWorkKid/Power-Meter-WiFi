package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.text.Text;

import java.net.URL;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ResourceBundle;

public class LivefeedController implements Initializable {
    public Text timeText;
    public Text voltageText;
    public Text curentText;
    public Text powerText;
    public Text powerfactorText;
    public Button backButton;
    public Button refreshButton;

    public void backAction(ActionEvent actionEvent) {
        try {
            Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));

            Main.myStage.setTitle("Menu Page");
            Main.myStage.setScene(new Scene(root, 600, 400));
            Main.myStage.show();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    public void refreshAction(ActionEvent actionEvent) {
        voltageText.setText(String.valueOf(Main.voltage));
        curentText.setText(String.valueOf(Main.current));
        powerText.setText(String.valueOf(Main.power));
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
        LocalDateTime now = LocalDateTime.now();
        timeText.setText(dtf.format(now));
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        voltageText.setText(String.valueOf(Main.voltage));
        curentText.setText(String.valueOf(Main.current));
        powerText.setText(String.valueOf(Main.power));
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
        LocalDateTime now = LocalDateTime.now();
        timeText.setText(dtf.format(now));
    }
}
