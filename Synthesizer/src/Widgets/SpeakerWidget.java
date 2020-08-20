package Widgets;

import Synth.Speaker;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;

import java.util.ArrayList;

public class SpeakerWidget extends Widget{
    //Members
    Label speaker_label;
    Speaker speaker;


    public SpeakerWidget(String type, Pane cp, ArrayList<Cable> cbs) {
        super("Speaker", cp, cbs);
        speaker = new Speaker();
        get_input_VBox();
        setAudioComponent(speaker);
    }

    @Override
    protected VBox get_center_VBox() {
        VBox content = new VBox();
        return content;
    }


}
