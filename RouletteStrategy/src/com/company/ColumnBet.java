package com.company;

public class ColumnBet extends Bet {
    int amount;
    int column;
    int[][] columns = {
            {1,4,7,10,13,16,19,22,25,28,31,34},
            {2,5,8,11,14,17,20,23,26,29,32,35},
            {3,6,9,12,15,18,21,24,27,30,33,36}  };

    public ColumnBet(int col, int amoun){
        amount = amoun;
        column = col;
    }

    @Override
    public boolean won(int number) {
        for(int i: columns[column - 1]){
            if(i == number)
                return true;
        }
        return false;
    }

    @Override
    public int payout() {
        return 3 * amount;
    }

    @Override
    public int getAmount() {
        return amount;
    }
}
