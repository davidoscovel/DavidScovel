package Widgets;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;

import java.util.ArrayList;

public abstract class WaveWidget extends Widget {
    //Members
    protected Label frequency_label;
    protected Slider frequency_slider;
    protected HBox content;
    protected VBox con;
    protected Label frequency_value;
    Double[] slider_value;


    protected WaveWidget(String type, Pane cp, ArrayList<Cable> cbs) {
        super(type, cp, cbs);
        get_output_VBox();
    }
    //protected output


    @Override
    protected VBox get_center_VBox(){
        frequency_slider = new Slider(0, 800, 0);
        frequency_label = new Label("Frequency");
        slider_value = new Double[]{frequency_slider.getValue()};
        Label frequency_value = new Label(String.format("%.0f", slider_value[0]));
        frequency_slider.valueProperty().addListener(new ChangeListener<Number>() {
            @Override
            public void changed(ObservableValue<? extends Number> observableValue, Number oldValue, Number NewValue) {
                frequency_value.setText(String.format("%.0f", NewValue));
            }
        });
        VBox content = new VBox();
        content.getChildren().addAll(frequency_label, frequency_slider, frequency_value);

        return content;
    }


}
