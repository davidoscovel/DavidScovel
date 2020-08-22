package com.company;

public class StraightUpBet extends Bet {
    int amount;
    int number;

    public StraightUpBet(int chosenNum, int am){
        amount = am;
        number = chosenNum;
    }

    @Override
    public boolean won(int num) {
        return number == num;
    }

    @Override
    public int payout() {
        return 36 * amount;
    }

    @Override
    public int getAmount() {
        return amount;
    }
}
