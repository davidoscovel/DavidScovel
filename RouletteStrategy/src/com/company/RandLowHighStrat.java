package com.company;

import java.util.ArrayList;
import java.util.Random;

public class RandLowHighStrat extends Strat {

    public RandLowHighStrat() {
    }

    @Override
    ArrayList<Bet> bet(rouletteTable table) {
        ArrayList<Bet> bets = new ArrayList<>();
        Random random = new Random();
        int i = random.nextInt(2);
        if(i == 0){
            bets.add(new LowHighBet(8, "low"));
        }
        else{
            bets.add(new LowHighBet(8, "high"));
        }
        return bets;
    }
}
