package Synth;

public class SineWave implements AudioComponent{
    //Members
    private double frequency;
    private double amplitude;

    //Constructor
    public SineWave(double pitch, double a){
        frequency = pitch;
        amplitude = a;
    }

    @Override
    public AudioClip getClip() {
        AudioClip clip = new AudioClip();
        for(int i = 0; i < clip.getSampleRate(); i++) {
            clip.setSample(i, (int)(amplitude * Math.sin(2 * Math.PI * frequency * i / clip.getSampleRate())));
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
