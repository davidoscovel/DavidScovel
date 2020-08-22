package com.company;

public class Main {

	public static void main(String[] args) {
		int oneSum = 0, twoSum = 0, threeSum = 0, fourSum = 0, fiveSum = 0, sixSum = 0, sevenSum = 0, eightSum = 0;
		int oneWins = 0, twoWins = 0, threeWins = 0, fourWins = 0, fiveWins = 0, sixWins = 0, sevenWins = 0, eightWins = 0;
		int iterations = 1000;
		int games = 100;
		for (int i = 0; i < iterations; i++) {
			rouletteTable table = new rouletteTable();
			int start = 500;
			player one = new player(start, new PrevColorStrat(), "Previous Colors", table);
			player two = new player(start, new RandomColorStrat(), "Random Colors", table);
			player three = new player(start, new RandomNumbersStrat(), "Random Numbers", table);
			player four = new player(start, new BirthdayOnlyStrat(), "Birthday only", table);
			player five = new player(start, new BirthdayOrPrevColor(), "Birthday or Prev Color", table);
			player six = new player(start, new RandLowHighStrat(), "Random Low High", table);
			player seven = new player(start, new FivetoThreeStrat(), "5 to 3", table);
			player eight = new player(start, new BirthdayorHighLow(), "Birthday or HighLow", table);
			table.addPlayer(one);
			table.addPlayer(two);
			table.addPlayer(three);
			table.addPlayer(four);
			table.addPlayer(five);
			table.addPlayer(six);
			table.addPlayer(seven);
			table.addPlayer(eight);
			for (int g = 0; g < games; g++) {
				table.playRound();
			}
			oneSum += (one.money - start);
			twoSum += (two.money - start);
			threeSum += (three.money - start);
			fourSum += (four.money - start);
			fiveSum += (five.money - start);
			sixSum += (six.money - start);
			sevenSum += (seven.money - start);
			eightSum += (eight.money - start);
			oneWins += one.wins;
			twoWins += two.wins;
			threeWins += three.wins;
			fourWins += four.wins;
			fiveWins += five.wins;
			sixWins += six.wins;
			sevenWins += seven.wins;
			eightWins += eight.wins;
		}
		System.out.println("Previous Colors Average Profits/Losses: " + oneSum/iterations + " --- Win Percentage: " + oneWins/iterations +'%');
		System.out.println("Random Colors Average Profits/Losses: " + twoSum/iterations + " --- Win Percentage: " + twoWins/iterations +'%');
		System.out.println("Random Numbers Average Profits/Losses: " + threeSum/iterations + " --- Win Percentage: " + threeWins/iterations +'%');
		System.out.println("Birthday Only Average Profits/Losses: " + fourSum/iterations + " --- Win Percentage: " + fourWins/iterations +'%');
		System.out.println("Birthday or Prev Color Average Profits/Losses: " + fiveSum/iterations + " --- Win Percentage: " + fiveWins/iterations +'%');
		System.out.println("Random High Low Average Profits/Losses: " + sixSum/iterations + " --- Win Percentage: " + sixWins/iterations +'%');
		System.out.println("5 to 3 Average Profits/Losses: " + sevenSum/iterations + " --- Win Percentage: " + sevenWins/iterations +'%');
		System.out.println("Birthday or HighLow Profits/Losses: " + eightSum/iterations + " --- Win Percentage: " + eightWins/iterations +'%');
	}

}
