package com.company;

import java.util.ArrayList;

public class PrevColorStrat extends Strat {
    int[] blacks = {2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};
    int[] reds = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};

    public PrevColorStrat() {
    }

    @Override
    ArrayList<Bet> bet(rouletteTable table) {
        ArrayList<Bet> bets = new ArrayList<>();
        if(table.getPastNumDisplay().isEmpty()){
            bets.add(new ColorBet("red", 8));
            return bets;
        }
        int prev = table.getPastNumDisplay().get(0);
        for(int i: reds){
            if(i == prev){
                bets.add(new ColorBet("red", 8));
                return bets;
            }
        }
        bets.add(new ColorBet("black", 8));
        return bets;
    }

}
