package com.company;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class BirthdayOnlyStrat extends Strat {

    @Override
    ArrayList<Bet> bet(rouletteTable table) {
        ArrayList<Bet> bets = new ArrayList<>();
        ArrayList<Integer> list = table.getPastNumDisplay();
        if(!hasRepeats(table.getPastNumDisplay())){
            for(int i = list.size() - 1; i > list.size() - 8; i--){
                bets.add(new StraightUpBet(list.get(i), 2));
            }
        }
        if(bets.isEmpty())
            bets.add(new StraightUpBet(1, 0));
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
