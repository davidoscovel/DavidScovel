package Synth;

public class Speaker implements AudioComponent {
    //Member

    private AudioComponent input;
    @Override
    public AudioClip getClip() {
        return input.getClip();
    }

    @Override
    public int getNuminputs() {
        return 0;
    }

    @Override
    public String getInputName(int index) {
        return null;
    }

    @Override
    public void connectInput(int index, AudioComponent in) {
        this.input = in;
    }
}
