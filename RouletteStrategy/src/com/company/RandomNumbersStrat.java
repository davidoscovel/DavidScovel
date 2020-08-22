package com.company;

import java.util.ArrayList;
import java.util.Random;

public class RandomNumbersStrat extends Strat{
    @Override
    ArrayList<Bet> bet(rouletteTable table) {
        ArrayList<Bet> bets = new ArrayList<>();
        Random random = new Random();
        bets.add(new StraightUpBet(random.nextInt(38), 1));
        bets.add(new StraightUpBet(random.nextInt(38), 1));
        bets.add(new StraightUpBet(random.nextInt(38), 1));
        bets.add(new StraightUpBet(random.nextInt(38), 1));
        bets.add(new StraightUpBet(random.nextInt(38), 1));
        bets.add(new StraightUpBet(random.nextInt(38), 1));
        bets.add(new StraightUpBet(random.nextInt(38), 1));
        bets.add(new StraightUpBet(random.nextInt(38), 1));
        return bets;
    }
}
