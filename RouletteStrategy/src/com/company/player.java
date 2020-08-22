package com.company;

import java.util.ArrayList;

public class player {
    int money;
    Strat strategy;
    String name;
    int wins;
    ArrayList<Bet> bets;
    rouletteTable table;

    player(int start, Strat strat, String nam, rouletteTable t){
        money = start;
        strategy = strat;
        name = nam;
        table = t;
        wins = 0;
    }

    ArrayList<Bet> placeBets(){
        bets = strategy.bet(table);
        for(Bet b: bets){
            money -= b.getAmount();
        }
        return bets;
    }

    ArrayList<Bet> getBets(){
        return bets;
    }

}
