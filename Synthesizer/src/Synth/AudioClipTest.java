package Synth;

import java.util.Random;

import static org.junit.jupiter.api.Assertions.*;

class AudioClipTest {


    @org.junit.jupiter.api.Test
    void getSampleTest() {
        AudioClip get_test = new AudioClip();
        get_test.setSample(20, (short)-48);
        get_test.setSample(20, (short) -8);
        short x = get_test.getSample(20);
        assert(x == -8);
        Random rand = new Random();
        for(int i = 0; i < 20; i++){
            short r = (short)rand.nextInt();
            get_test.setSample(i, r);
            assertEquals(get_test.getSample(i), r);
        }
    }

    @org.junit.jupiter.api.Test
    void setSampleTest() {
        AudioClip setTest = new AudioClip();
        setTest.setSample(40, 257);
        assert(setTest.getSample(40) == 257);
        setTest.setSample(50, -513);
        assertEquals(setTest.getSample(50), -513);
    }

}