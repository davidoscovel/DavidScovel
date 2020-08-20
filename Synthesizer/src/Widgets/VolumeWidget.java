package Widgets;

import Synth.VolumeFilter;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.geometry.Orientation;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;

import java.util.ArrayList;

public class VolumeWidget extends Widget {
    //Members
    Slider volume_slider;
    Label volume_label;
    VBox content;
    VolumeFilter volume;

    public VolumeWidget(String type, Pane cp, ArrayList<Cable> cbs){
        super("Volume", cp, cbs);
    }

    @Override
    protected VBox get_center_VBox() {
       // Volume Widget
        volume = new VolumeFilter(0);
        setAudioComponent(volume);
        volume_slider = new Slider(0,10,0);
        get_input_VBox();
        get_output_VBox();
        final double[] volume_value= {volume_slider.getValue()};
        Label volume_display = new Label(String.format("%.0f", volume_value[0]));
        volume_slider.valueProperty().addListener(new ChangeListener<Number>() {
            @Override
            public void changed(ObservableValue<? extends Number> observableValue, Number oldValue, Number NewValue) {
                volume_display.setText(String.format("%.0f", NewValue));
                volume.setVolume(NewValue.doubleValue());
            }
        });
        volume_slider.setOrientation(Orientation.VERTICAL);
        content = new VBox();
            content.getChildren().addAll(volume_slider, volume_display);
            return content;
    }

}
