package Widgets;

import Synth.Mixer;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;

import java.util.ArrayList;

public class MixerWidget extends Widget{
    Mixer mixer;


    public MixerWidget(String type, Pane cp, ArrayList<Cable> cbs) {
        super("Mixer", cp, cbs);
        mixer = new Mixer();
        setAudioComponent(mixer);
        get_input_VBox();
        get_output_VBox();
    }

    @Override
    protected VBox get_center_VBox() {
        Label spacing = new Label("               ");
        VBox empty = new VBox();
        empty.getChildren().add(spacing);
        return empty;
    }

}
