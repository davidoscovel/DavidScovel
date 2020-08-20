package Widgets;

import Synth.DescendingWave;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;

import java.util.ArrayList;

public class DescendingWaveWidget extends WaveWidget {
    //Members
    private DescendingWave wave;
    private Double[] slider_value;


    public DescendingWaveWidget(String type, Pane cp, ArrayList<Cable> cbs) {
        super("Descending Wave", cp, cbs);
        wave = new DescendingWave(0,10000);
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
