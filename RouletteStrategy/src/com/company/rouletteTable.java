package com.company;

import java.util.ArrayList;
import java.util.Queue;
import java.util.Random;
import java.util.concurrent.LinkedBlockingQueue;

public class rouletteTable {
    int numPlayers;
    ArrayList<player> players;
    int revenue;
    ArrayList<Integer> pastNumDisplay;

    //Constructor
    rouletteTable(){
        numPlayers = 0;
        players = new ArrayList<>();
        revenue = 0;
        pastNumDisplay = new ArrayList<>();
    }

    //Methods
    void takeBets(){
        for(player p: players){
            ArrayList<Bet> bets = p.placeBets();
            for(Bet b: bets){
                revenue += b.getAmount();
            }
        }
    }

    void payBets(int number){
        for(player p: players){
            ArrayList<Bet> bets = p.getBets();
            for(Bet b: bets) {
                if (b.won(number)) {
                    int payout = b.payout();
                    p.wins += 1;
                    p.money += payout;
                    revenue -= payout;
                }
            }
        }
    }

    public void playRound(){
        takeBets();
        Random random = new Random();
        int number = random.nextInt(39);
        if(pastNumDisplay.size() > 17)
            pastNumDisplay.remove(0);
        pastNumDisplay.add(number);
        payBets(number);
    }

    public void addPlayer(player playa){
        players.add(playa);
        numPlayers ++;
    }

    public ArrayList<Integer> getPastNumDisplay() {
        return pastNumDisplay;
    }
}
