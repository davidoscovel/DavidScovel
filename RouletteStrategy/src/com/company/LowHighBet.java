package com.company;

public class LowHighBet extends Bet {
    int amount;
    String choice;

    public LowHighBet(int amount, String choice) {
        this.amount = amount;
        this.choice = choice;
    }

    @Override
    public boolean won(int number) {
        if(choice.equals("low")){
            return number <= 18 && number != 0;
        }
        else
            return number > 18 && number != 37;
    }

    @Override
    public int payout() {
        return 2 * amount;
    }

    @Override
    public int getAmount() {
        return amount;
    }
}
