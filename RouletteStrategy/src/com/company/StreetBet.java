package com.company;

public class StreetBet extends Bet{
    int amount;
    int street;
    int[][] streets = {
            {1,2,3},{4,5,6},{7,8,9},
            {10,11,12},{13,14,15},{16,17,18},
            {19,20,21},{22,23,24},{25,26,27},
            {28,29,30},{31,32,33},{34,35,36}  };

    public StreetBet(int lane, int amoun){
        amount = amoun;
        street = lane;
    }
    @Override
    public boolean won(int number) {
        for(int i: streets[street]){
            if(number == i)
                return true;
        }
        return false;
    }

    @Override
    public int payout() {
        return 12 * amount;
    }

    @Override
    public int getAmount() {
        return amount;
    }
}
