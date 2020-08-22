package com.company;

public class SplitBet extends Bet{
    int amount;
    int num1;
    int num2;

    public SplitBet(int one, int two, int amoun){
        num1 = one;
        num2 = two;
        amount = amoun;
    }
    @Override
    public boolean won(int number) {
        return (number == num1 || number == num2);
    }

    @Override
    public int payout() {
        return 18 * amount;
    }

    @Override
    public int getAmount() {
        return amount;
    }
}
