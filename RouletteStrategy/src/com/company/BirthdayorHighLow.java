package com.company;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;

public class BirthdayorHighLow extends Strat {

    public BirthdayorHighLow() {
    }

    @Override
    ArrayList<Bet> bet(rouletteTable table) {
        ArrayList<Bet> bets = new ArrayList<>();
        ArrayList<Integer> list = table.getPastNumDisplay();
        if(!hasRepeats(table.getPastNumDisplay())){
            for(int i = list.size() - 1; i > list.size() - 8; i--){
                bets.add(new StraightUpBet(list.get(i), 1));
            }
        }
        else{
            Random random = new Random();
            int i = random.nextInt(2);
            if(i == 0){
                bets.add(new LowHighBet(8, "low"));
            }
            else{
                bets.add(new LowHighBet(8, "high"));
            }
        }
        return bets;
    }

    boolean hasRepeats(ArrayList<Integer> list){
        if(list.size() < 8)
            return true;
        Set<Integer> set = new HashSet<>();
        for(int i = list.size() - 1; i > list.size() - 8; i--){
            if(!set.add(list.get(i)))
                return false;
        }
        return true;
    }
}
