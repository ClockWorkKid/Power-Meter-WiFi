package sample;


import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;

import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.chart.BarChart;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Button;

import javafx.scene.layout.VBox;
import javafx.stage.Stage;


import java.net.URL;

import java.util.ResourceBundle;

public class HistoryController implements Initializable {
    public Button dailyButton;
    public Button monthlyButton;
    public Button backButton;
    public Button hourlyButton;






    /*
    this method is called when the hourly button is pressed
     */
    public void hourlyAction(ActionEvent actionEvent) {

        /*
        reads history datas from 'append' file
         */
        History.readHistory();

        /*
        print all the data
         */
        History.printHistory();

        /*
        create an array to store today's power consumption of each hour.
        the array is initialized to zero
         */
        Double[] power= new Double[24];
        for(int i = 0 ; i < 24;i++){
            power[i]=0d;
        }

        /*
        get the current time in an array of strings
         */
        String[] today= History.getCurrentTime();

        /*
        print the current time
         */
        System.out.println(today[0]+" "+today[1]+" "+today[2]+" "+today[3]+" "+today[4]+" "+today[5]);

        /*
        sum the data with respect to hours and keep them in the power array
         */
        for(History h:History.histories){
            if(h.year.equals(today[0]) && h.month.equals(today[1]) && h.day.equals(today[2]))
            {
                power[Integer.parseInt(h.hour)]+=h.power;
            }
        }

        /*
        print the total power consumption of each of the 24 hours
         */
        for(int i = 0 ; i < 24; i++){
            System.out.print(power[i]+" ");
        }
        System.out.println("");

        /*
        Create x axis and set the label
         */
        CategoryAxis xAxis = new CategoryAxis();
        xAxis.setLabel("Hours");

        /*
        create y axis and set the label
         */
        NumberAxis yAxis = new NumberAxis();
        yAxis.setLabel("Power Usage");

        /*
        create a bar chart using the x axis and the y axis created above
         */
        BarChart barChart = new BarChart(xAxis, yAxis);


        /*
        a special array to keep the data to be shown
         */
        XYChart.Series dataSeries1 = new XYChart.Series();
        dataSeries1.setName("Today");

        /*
        create 24 bars in the graph
         */
        for(int i = 0 ; i < 24;i++){
            /*
            add a bar
             */
            dataSeries1.getData().add(new XYChart.Data(String.valueOf(i), power[i]/3.6e6f));
        }

        /*
        add the data series to the barchart
         */
        barChart.getData().add(dataSeries1);

        /*
        vbox is a container to keep the barchart object
         */
        VBox vbox = new VBox(barChart);

        /*
        create a scene with vbox as root.
         */
        Scene scene = new Scene(vbox, 900, 400);

        /*
        Create a new stage
         */
        Stage stage = new Stage();
        stage.setScene(scene);
        stage.show();
    }

    public void dailyAction(ActionEvent actionEvent) {
        /*
        This method is similar to the method written above
         */
        History.readHistory();
        History.printHistory();

        Double[] power= new Double[31];
        for(int i = 0 ; i < 31;i++){
            power[i]=0d;
        }

        String[] today= History.getCurrentTime();

        System.out.println(today[0]+" "+today[1]+" "+today[2]+" "+today[3]+" "+today[4]+" "+today[5]);

        for(History h:History.histories){
            if(h.year.equals(today[0]) && h.month.equals(today[1]))
            {
                power[Integer.parseInt(h.day)-1]+=h.power;
            }
        }


        for(int i = 0 ; i < 31; i++){
            System.out.print(power[i]+" ");
        }

        System.out.println("");

        CategoryAxis xAxis = new CategoryAxis();
        xAxis.setLabel("Days");

        NumberAxis yAxis = new NumberAxis();
        yAxis.setLabel("Power Usage");

        BarChart barChart = new BarChart(xAxis, yAxis);


        XYChart.Series dataSeries1 = new XYChart.Series();
        dataSeries1.setName("This month");

        for(int i = 0 ; i < 31;i++){
            dataSeries1.getData().add(new XYChart.Data(String.valueOf(i), power[i]/3.6e6f));
        }

        barChart.getData().add(dataSeries1);

        VBox vbox = new VBox(barChart);

        Scene scene = new Scene(vbox, 1200, 400);
        Stage stage = new Stage();
        stage.setScene(scene);
        stage.show();


    }

    public void monthlyAction(ActionEvent actionEvent) {
        /*
        this method is similar to the method written above
         */
        History.readHistory();
        History.printHistory();

        Double[] power= new Double[12];
        for(int i = 0 ; i < 12;i++){
            power[i]=0d;
        }

        String[] today= History.getCurrentTime();

        System.out.println(today[0]+" "+today[1]+" "+today[2]+" "+today[3]+" "+today[4]+" "+today[5]);

        for(History h:History.histories){
            if(h.year.equals(today[0]))
            {
                power[Integer.parseInt(h.month)-1]+=h.power;
            }
        }


        for(int i = 0 ; i < 12; i++){
            System.out.print(power[i]+" ");
        }

        System.out.println("");

        CategoryAxis xAxis = new CategoryAxis();
        xAxis.setLabel("Months");

        NumberAxis yAxis = new NumberAxis();
        yAxis.setLabel("Power Usage");

        BarChart barChart = new BarChart(xAxis, yAxis);


        XYChart.Series dataSeries1 = new XYChart.Series();
        dataSeries1.setName("This month");

        for(int i = 0 ; i < 12;i++){
            dataSeries1.getData().add(new XYChart.Data(String.valueOf(i), power[i]/3.6e6f));
        }

        barChart.getData().add(dataSeries1);

        VBox vbox = new VBox(barChart);

        Scene scene = new Scene(vbox, 800, 400);
        Stage stage = new Stage();
        stage.setScene(scene);
        stage.show();


    }


/*
This is the method which is called when the back button is pressed
 */
    public void backAction(ActionEvent actionEvent) {
        try {
            /*
            change the scene of the main stage
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
