package Synth;

public class VolumeFilter implements AudioComponent {
    public double scale;
    public AudioComponent input;
    //Constructor
    public VolumeFilter(double volume){
        scale = (volume / 10);
    }
    @Override
    public AudioClip getClip() {
        AudioClip original = input.getClip();
        for(int i = 0; i < original.getSampleRate(); i++) {
            int sample = original.getSample(i);
            int adjusted = (int) (sample * scale);
            if(adjusted > Short.MAX_VALUE){
                adjusted = Short.MAX_VALUE;
            }
            if(adjusted < Short.MIN_VALUE){
                adjusted = Short.MIN_VALUE;
            }
            original.setSample(i, adjusted);

        }
        return original;
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
        this.input = input;
    }

    public void setVolume(double vol){
        scale = vol/5;
    }
}
