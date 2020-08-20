package Widgets;

import Synth.AscendingWave;
import Synth.DescendingWave;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;

import java.util.ArrayList;

public class AscendingWaveWidget extends WaveWidget {
    //Members
    AscendingWave wave;
    Double[] slider_value;


    protected AscendingWaveWidget(String type, Pane cp, ArrayList<Cable> cbs) {
        super("Ascending Wave", cp, cbs);
        wave = new AscendingWave(0,10000);
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
