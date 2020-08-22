package com.company;

import java.util.ArrayList;
import java.util.Random;

public class FivetoThreeStrat extends Strat{

    public FivetoThreeStrat() {
    }

    @Override
    ArrayList<Bet> bet(rouletteTable table) {
        ArrayList<Bet> bets = new ArrayList<>();
        Random random = new Random();
        int i = random.nextInt(2);
        if(i == 1){
            bets.add(new LowHighBet(5, "low"));
            bets.add(new DozenBet(3, 3));
        }
        else{
            bets.add(new LowHighBet(5, "high"));
            bets.add(new DozenBet(1, 3));
        }
        return bets;
    }
}
