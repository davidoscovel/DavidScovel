package com.company;

public class EvenorOddBet extends Bet {
    int amount;
    String choice;

    public EvenorOddBet(int amount, String choice) {
        this.amount = amount;
        this.choice = choice;
    }

    @Override
    public boolean won(int number) {
        if(choice.equals("even")){
            return (number % 2) == 0;
        }
        else{
            return (number % 2) == 1;
        }
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
