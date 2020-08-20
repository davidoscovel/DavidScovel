package Widgets;

import Synth.SineWave;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;

import java.util.ArrayList;

public class SinWaveWidget extends WaveWidget {
    //Members
    SineWave wave;
    Double[] slider_value;


    //Constructor
    public SinWaveWidget(String type, Pane cp, ArrayList<Cable> cbs){
        super("SinWave", cp, cbs);
        wave = new SineWave(0,10000);
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
