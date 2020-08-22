package com.company;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class BirthdayOrPrevColor extends Strat {
    int[] blacks = {2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};
    int[] reds = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
    @Override
    ArrayList<Bet> bet(rouletteTable table) {
        ArrayList<Bet> bets = new ArrayList<>();
        ArrayList<Integer> list = table.getPastNumDisplay();
        if(!hasRepeats(table.getPastNumDisplay())){
            for(int i = list.size() - 1; i > list.size() - 8; i--){
                bets.add(new StraightUpBet(list.get(i), 1));
            }
        }
        if(bets.isEmpty()) {
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
