package Synth;

public interface AudioComponent {



   //Methods
    AudioClip getClip();
    int getNuminputs();
    String getInputName(int index);
    void connectInput(int index, AudioComponent input);

}