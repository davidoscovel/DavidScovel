package com.company;

public class ColorBet extends Bet{
    int amount;
    String color;
    int[] blacks = {2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};
    int[] reds = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};

    public ColorBet(String col, int amoun){
        color = col;
        amount = amoun;
    }

    @Override
    public boolean won(int number) {
        if(color.equals("red")){
            for(int i: reds){
                if(i == number)
                    return true;
            }
        }
        else {
            for (int i : blacks) {
                if (i == number)
                    return true;
            }
        }
            return false;
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
