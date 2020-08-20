package Widgets;

import Synth.AudioComponent;
import Synth.VolumeFilter;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

import java.util.ArrayList;

public abstract class Widget {
    //Members
    private BorderPane container;
    private VBox content;
    private VBox in;
    private VBox out;
    private AudioComponent input;
    private Double[] frequency;
    private VolumeFilter volume;
    private Circle input_jack;
    private Circle output_jack;
    double x_start_location;
    double y_start_location;
    double x_change;
    double y_change;
    boolean out_bool;


    //Wave Widgets

    //Constructor
    public Widget(String type, Pane cp, ArrayList<Cable> cbs) {
        String title = type;
        Label title_label = new Label(title);
        VBox title_Vbox = new VBox(title_label);
        title_Vbox.setAlignment(Pos.TOP_CENTER);
        in = new VBox();
        in.setAlignment(Pos.BOTTOM_LEFT);
        out = new VBox();
        out.setAlignment(Pos.BOTTOM_RIGHT);
        content = get_center_VBox();
        content.setAlignment(Pos.CENTER);
        HBox organize = new HBox();
        VBox organize2 = new VBox();
        organize.getChildren().addAll(title_Vbox, in, content, out);
        organize2.getChildren().addAll(title_Vbox, organize);
        container = new BorderPane(organize2);
        container.setStyle("-fx-border-width: 3;" +
                "-fx-border-color: Silver;" +
                "-fx-spacing: 4;" +
                "-fx-background-color: White;"
        );

        container.addEventHandler(MouseEvent.MOUSE_PRESSED,
                new EventHandler<MouseEvent>() {
                    @Override
                    public void handle(MouseEvent mouseEvent) {
                        x_start_location = mouseEvent.getX();
                        y_start_location = mouseEvent.getY();
                    }


                });
        container.addEventHandler(MouseEvent.MOUSE_DRAGGED,
                new EventHandler<MouseEvent>() {
                    @Override
                    public void handle(MouseEvent mouseEvent) {
                        x_change = mouseEvent.getX() - x_start_location;
                        y_change = mouseEvent.getY() - y_start_location;
                        if (!output_jack.isPressed()) {
                            container.relocate(container.getLayoutX() + x_change, container.getLayoutY() + y_change);
                            cp.getChildren().clear();
                            for(Cable c: cbs){
                                c.draw_line();
                                if(!cp.getChildren().contains(c.getLine())){
                                    cp.getChildren().add(c.getLine());
                                }
                            }
                        }
                    }
                });

    }


    //Methods
    //Gets content for middle VBox in display
    protected abstract VBox get_center_VBox();

    protected VBox get_input_VBox() {
        Label in_label = new Label("In");
        input_jack = new Circle(12.f, Color.FORESTGREEN);
        in.getChildren().addAll(in_label, input_jack);
        return in;
    }

    protected VBox get_output_VBox() {
        Label out_label = new Label("Out");
        output_jack = new Circle(12.f, Color.DEEPSKYBLUE);
        out.getChildren().addAll(out_label, output_jack);
        return out;
    }


    public BorderPane display() {
        return container;
    }

    protected void setAudioComponent(AudioComponent ac) {
        input = ac;
    }

    public AudioComponent getAudioComponent() {
        return input;
    }

    protected void setFrequency(Double[] freq) {
        frequency = freq;
    }

    public Double[] getFrequency() {
        return frequency;
    }

    public Circle get_input_jack() {
        return input_jack;
    }

    public Circle get_output_jack() {
        return output_jack;
    }

    public boolean out_put_jack_pressed(Pane pane) {

        pane.addEventHandler(MouseEvent.MOUSE_PRESSED,
                new EventHandler<MouseEvent>() {
                    @Override
                    public void handle(MouseEvent mouseEvent) {
                        if (output_jack.isPressed()) {
                            out_bool = true;
                        }
                    }

                });
        return out_bool;
    }


}
