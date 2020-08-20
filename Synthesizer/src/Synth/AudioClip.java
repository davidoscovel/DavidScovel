package Synth;

public class AudioClip {
    //Member Variables
    private byte[] soundArray = new byte[88200];
    private int duration = 1;
    private int sampleRate = 44100;

    //Default constructor -- full of 0s
    public AudioClip(){
        for(int i = 0; i < 44100; i++){
            soundArray[i] = (byte)0xff;
        }
    }

    //Method
    public short getSample(int index){
        short ret = 0x0000;
        byte first_half = soundArray[(index*2) + 1];
        int second_half = soundArray[index*2] & 0xFF;
        ret = (short)((first_half << 8) | second_half);
        return ret;
    }

    public void setSample(int index, int value){
        byte byte1 = (byte)value ;
        byte byte2 = (byte)(value >> 8);
        soundArray[(index*2)] = byte1;
        soundArray[(index*2) + 1] = byte2;
    }

    public byte[] getData(){
        byte[] copy = new byte[88200];
        for(int i = 0; i < 88200; i++){
            copy[i] = soundArray[i];
        }
        return copy;
    }

    public int getSampleRate(){
        return sampleRate;
    }
}
