package com.company;

import java.util.ArrayList;
import java.util.Random;

public class RandomColorStrat extends Strat {

    public RandomColorStrat() {
    }

    @Override
    ArrayList<Bet> bet(rouletteTable table) {
        ArrayList<Bet> bets = new ArrayList<>();
        Random random = new Random();
        int i = random.nextInt(2);
        if(i == 0){
            bets.add(new ColorBet("red", 8));
        }
        else{
            bets.add(new ColorBet("black", 8));
        }
        return bets;
    }
}
