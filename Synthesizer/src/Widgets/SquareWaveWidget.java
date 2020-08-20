package Widgets;

import Synth.SquareWave;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;

import java.util.ArrayList;

public class SquareWaveWidget extends WaveWidget{
    //Members
    SquareWave wave;
    Double[] slider_value;

    //Constructor
    public SquareWaveWidget(String type, Pane cp, ArrayList<Cable> cbs) {
        super("SquareWave", cp, cbs);
        wave = new SquareWave(0,10000);
        slider_value = new Double[]{frequency_slider.getValue()};
        Label frequency_value = new Label(String.format("%.0f", slider_value[0]));
        frequency_slider.valueProperty().addListener(new ChangeListener<Number>() {
            @Override
            public void changed(ObservableValue<? extends Number> observableValue, Number oldValue, Number NewValue) {
                wave.setFrequency(NewValue.doubleValue());
            }
        });
        setAudioComponent(wave);
        }


}
