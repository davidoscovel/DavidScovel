package Widgets;

import Synth.AudioComponent;
import javafx.application.Platform;
import javafx.geometry.Point2D;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Line;

public class Cable {
    //Members
    Line line;
    Widget in_widget;
    Widget out_widget;
    AudioComponent audio_out;
    AudioComponent audio_in;
    Pane pane;


    public Cable(Widget out, Widget in, Pane p){
        //Connect Members
        in_widget = in;
        out_widget = out;
        pane = p;

        //Connect Audio
        audio_out = out_widget.getAudioComponent();
        audio_in = in_widget.getAudioComponent();
        audio_in.connectInput(0, audio_out);

        //Draw Line
        draw_line();
    }

    public Line getLine(){
        return line;
    }

    public void update_line(){
//        Platform.runLater(()-> {
        //Create Line from circles in widgets
        Point2D initial_point = out_widget.get_output_jack().localToScene(out_widget.get_output_jack().getCenterX(), out_widget.get_output_jack().getCenterY());
        Point2D end_point = in_widget.get_input_jack().localToScene(in_widget.get_input_jack().getCenterX(), in_widget.get_input_jack().getCenterY());
        line.setStartX(initial_point.getX());
        line.setStartY(initial_point.getY());
        line.setEndX(end_point.getX());
        line.setEndY(end_point.getY());
//        line = new Line(initial_point.getX(), initial_point.getY(), end_point.getX(), end_point.getY());
//        line.setStyle("-fx-stroke-width: 3;" +
//                "-fx-stroke: MAGENTA;");
//
//        //Drawing Line
//        pane.getChildren().add(line);
//    });
    }

    public void draw_line(){
        Platform.runLater(() ->update_line());
        line = new Line();
        line.setStyle("-fx-stroke-width: 3;" +
                "-fx-stroke: MAGENTA;");
        pane.getChildren().add(line);
        }


}
