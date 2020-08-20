package Synth;

public class SquareWave implements AudioComponent {
    //Members
    private double frequency;
    private double amplitude;

    //Constructor
    public SquareWave(double pitch, double a) {
        frequency = pitch;
        amplitude = a;
    }

    @Override
    public AudioClip getClip() {
        AudioClip clip = new AudioClip();
        for(int i = 0; i < clip.getSampleRate(); i++) {
            if ((frequency * i / clip.getSampleRate() % 1 > 0.5)) {
                clip.setSample(i, ((int)(amplitude)));
            } else {
                clip.setSample(i, ((int)(amplitude * -1)));
            }
        }
        return clip;
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
    public void connectInput(int index, AudioComponent input) {

    }

    public void setFrequency(double freq){
        frequency = freq;
    }
}
