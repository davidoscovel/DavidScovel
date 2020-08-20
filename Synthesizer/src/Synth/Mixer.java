package Synth;

import java.util.ArrayList;

public class Mixer implements AudioComponent {

    public ArrayList<AudioComponent> inputs;

   public Mixer(){
       inputs = new ArrayList<AudioComponent>();
   }

    @Override
    public AudioClip getClip() {
       AudioClip result = new AudioClip();
       for(AudioComponent ac: inputs) {
           AudioClip clip = ac.getClip();
           for (int i = 0; i < clip.getSampleRate(); i++) {
               int sum = (clip.getSample(i) + result.getSample(i));
               if(sum > Short.MAX_VALUE){
                   sum = Short.MAX_VALUE;
               }
               if(sum < Short.MIN_VALUE){
                   sum = Short.MIN_VALUE;
               }
               result.setSample(i, (int) (sum));
           }
       }
            return result;
    }

    @Override
    public int getNuminputs() {
        return inputs.size();
    }

    @Override
    public String getInputName(int index) {
        return null;
    }

    @Override
    public void connectInput(int index, AudioComponent in) {
        inputs.add(in);
    }
}
