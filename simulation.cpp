/*
 * simulation.cpp
 *
 * Contains functions to simulate CFL season at various levels of abstraction
 *
 *  Created on: Jul 9, 2019
 *      Author: michaelmacaulay
 */


#include "league_classes.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <cassert>
/* void copySchedule
 *
 * Purpose:	Copies the season schedule to a new identically sized array so that season simulations
 * 			can be run without modifying the original schedule array
 */
void copySchedule(GAME destination[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK], const GAME source[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]){
	for(int i = 0; i < NUMBER_OF_WEEKS; i++){
		for(int j = 0; j < MAX_GAMES_PER_WEEK; j++){
			destination[i][j] = source[i][j];
		}
	}
}
/* void createOutputFile
 *
 * Purpose:	Creates a file "readout.txt" and prints each team's result breakdown to it
 */
void createOutputFile(){
	ofstream outputFile;
	outputFile.open("readout.txt");
		assert(outputFile); // error check output file stream

		// print out team records!

	outputFile.close();
}
/* void crunchSeasonStats
 *
 * Purpose:	Processes a full simulated season and returns all necessary stats to break ties
 *
 * Stats that need to be captured for each team:
 *			*Number of playoff points
 *			*Number of games won against all clubs
 *		Winning percentage against each individual club
 *			*Wins against each individual club
 *			*Games played against each individual club
 *			(*)Percentage against each club
 *		Net aggregate of points (points scored - points against) against each individual club
 *			*Points scored vs each individual club
 *			*Points against by each individual club
 *			(*)Net aggregate against each club
 *		Net quotient of points (points scored / points against) against each individual club
 *			(*)Net quotient against each club
 *		Winning percentage against entire division
 *			(*)Wins against division
 *			(*)Games played against division
 *			(*)Percentage against division
 *		Net aggregate against division
 *			(*)Points scored against division
 *			(*)Points against within division
 *			(*)Net aggregate against division
 *		Net quotient against division
 *			(*)Net quotient against division
 *		Net aggregate points against whole league
 *			(*)Points scored against league
 *			(*)Points against within league
 *			(*)Net aggregate within league
 *		Net quotient points against whole league
 *			(*)Net quotient within league
 *			(coin toss if all of above have failed)
 *
 */
void crunchSeasonStats(TEAM league[], GAME schedule[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]){
	// initialize all ranking statistics to 0
	for(int i = 0; i < NUMBER_OF_TEAMS; i++){
		league[i].playoffPoints = 0;
		league[i].totalWins = 0;
		league[i].winsInDivision = 0;
		league[i].gamesAgainstDivision = 0;
		league[i].pctWinsAgainstDivision = 0;
		league[i].pointsForInDivision = 0;
		league[i].pointsAgainstInDivision = 0;
		league[i].netAggregateAgainstDivision = 0;
		league[i].netQuotientAgainstDivision = 0;
		league[i].totalPointsFor = 0;
		league[i].totalPointsAgainst = 0;
		league[i].netAggregateAgainstLeague = 0;
		league[i].netQuotientAgainstLeague = 0;
		for(int j = 0; j < NUMBER_OF_TEAMS; j++){
			league[i].pointsForCertainTeam[j] = 0;
			league[i].pointsAgainstCertainTeam[j] = 0;
			league[i].winsAgainstCertainTeam[j] = 0;
			league[i].gamesAgainstCertainTeam[j] = 0;
			league[i].pctWinsAgainstCertainTeam[j] = 0;
			league[i].netAggregateAgainstCertainTeam[j] = 0;
			league[i].netQuotientAgainstCertainTeam[j] = 0;
		}
	}
	// read every game in the completed season schedule and update all relevant statistics
	for(int i = 0; i < NUMBER_OF_WEEKS; i++){ // loop through each week
		for(int j = 0; j < MAX_GAMES_PER_WEEK; j++){ // loop through each game
			crunchGameStats(league, schedule[i][j]); // process the game stats for that game
		}
	}

	// calculate each team's wins against division
	// calculate each team's total games against division
	// calculate points for in division
	// calculate points against in division
	// calculate total points scored in league
	// calculate total points scored against in league
	CalculateTotals(league);

	// calculate each team's win percentage against each opponent
	// calculate each team's percentage wins against division
	CalculateWinPercentage(league);

	// calculate each team's net aggregate points against each opponent
	// calculate net aggregate for division
	// calculate league net aggregate points
	CalculateNetAggregate(league);

	// calculate each team's net quotient against each opponent
	// calculate net quotient for division
	// calculate league net quotient points
	CalculateNetQuotient(league);

	// rank division playoff standings
	TEAM westDivisionRanking[5], eastDivisionRanking[4];
	// sort west division
	sortDivision(league, westDivisionRanking, eastDivisionRanking);

	// increment all non-crossover counters
	// check crossover
	// final counter increment
}

void sortDivision(TEAM league[], TEAM westDivision[], TEAM eastDivision[]){
	int winnerArrayIndex;
	int divisionIndex = 0;
	int winningValue;
	int numberWinners;

	// check west division
	// step 1: check playoff points
	for(int i = 0; i < 5; i++){ // loop until division array full
		for(int j = 0; j < 5; j++){
			winningValue = 0; // highest value observed so far
			numberWinners = 0; // holds all instances of winning value

			if(league[j].playoffPoints > winningValue && league[j].ranked == false){
				numberWinners = 1;
				winningValue = league[j].playoffPoints; // set new winning value
				winnerArrayIndex = j;
			}
			else if(league[j].playoffPoints == winningValue && league[j].ranked == false){
				numberWinners++;
			}
		}

		// once loop has run through entire division
		assert(numberWinners != 0); // error check - there should be at least one winner
		while(numberWinners > 1){ // run tiebreakers until only one winner
			int nextIndex = 0; // next index to be stored in winning array
			int stillInRunning[5] = {-1}; // create array to store all current winners
			for(int x = 0; x < 5; x++){ // find all winners and put their index in array
				if(league[x].playoffPoints == winningValue){
					stillInRunning[nextIndex] = x;
					nextIndex++;
				}
			}
		}
		westDivision[divisionIndex] = league[winnerArrayIndex];
		league[winnerArrayIndex].ranked = true;
		divisionIndex++; // increment the winner array index
	}
}

TEAM breakTie(TEAM, TEAM){
	TEAM winningTeam;

	return winningTeam;
}

void CalculateNetQuotient(TEAM league[]){
	for(int i = 0; i < NUMBER_OF_TEAMS; i++){
		for(int j = 0; j < NUMBER_OF_TEAMS; j++){
			league[i].netQuotientAgainstCertainTeam[j] = (1000 * league[i].pointsForCertainTeam[j]) /
					(1000 * league[i].pointsAgainstCertainTeam[j]);
		}
		league[i].netQuotientAgainstDivision = (1000 * league[i].pointsForInDivision) /
				(1000 * league[i].pointsAgainstInDivision);
		league[i].netQuotientAgainstLeague = (1000 * league[i].totalPointsFor) /
				(1000 * league[i].totalPointsAgainst);
	}
}

void CalculateNetAggregate(TEAM league[]){
	// calculate each team's net aggregate against each opponent
	// calculate each team's net aggregate against division
	// calculate each team's net aggregate against league
	for(int i = 0; i < NUMBER_OF_TEAMS; i++){
		for(int j = 0; j < NUMBER_OF_TEAMS; j++){
			league[i].netAggregateAgainstCertainTeam[j] = league[i].pointsForCertainTeam[j] -
					league[i].pointsAgainstCertainTeam[j];
		}
		league[i].netAggregateAgainstDivision = league[i].pointsForInDivision -
				league[i].pointsAgainstInDivision;
		league[i].netAggregateAgainstLeague = league[i].totalPointsFor - league[i].totalPointsAgainst;
	}
}
void CalculateTotals(TEAM league[]){
	// calculate west division wins against division, total games against division
		// points for in division, points against in division
	for(int i = 0; i < 5; i++){ // for teams in the west division
		for(int j = 0; j < 5; j++){ // against each west div opponent
			league[i].pointsForInDivision += league[i].pointsForCertainTeam[j];
			league[i].pointsAgainstInDivision += league[i].pointsAgainstCertainTeam[j];
			league[i].winsInDivision += league[i].winsAgainstCertainTeam[j];
			league[i].gamesAgainstDivision += league[i].gamesAgainstCertainTeam[j];
		}
	}

	// calculate east division wins against division, total games against division
		// points for in division, points against in division
	for(int i = 5; i < 9; i++){ // for teams in the east division
		for(int j = 5; j < 9; j++){ // against each east div opponent
			league[i].pointsForInDivision += league[i].pointsForCertainTeam[j];
			league[i].pointsAgainstInDivision += league[i].pointsAgainstCertainTeam[j];
			league[i].winsInDivision += league[i].winsAgainstCertainTeam[j];
			league[i].gamesAgainstDivision += league[i].gamesAgainstCertainTeam[j];
		}
	}

	// calculate points scored in league, points scored against in league
	for(int i = 0; i < NUMBER_OF_TEAMS; i++){ // for all teams in league
		for(int j = 0; j < NUMBER_OF_TEAMS; j++){
			league[i].totalPointsFor += league[i].pointsForCertainTeam[j];
			league[i].totalPointsAgainst += league[i].pointsAgainstCertainTeam[j];
		}
	}
}

void CalculateWinPercentage(TEAM league[]){
	for(int i = 0; i < NUMBER_OF_TEAMS; i++){ // for each team in league
		for(int j = 0; j < NUMBER_OF_TEAMS; j++){
			// determine win percentage against each opponent
			league[i].pctWinsAgainstCertainTeam[j] = (1000 * league[i].winsAgainstCertainTeam[j]) /
					(1000 * league[i].gamesAgainstCertainTeam[j]);
			// determine win percentage against league
			league[i].pctWinsAgainstDivision = (1000 * league[i].winsInDivision) /
					(1000 * league[i].gamesAgainstDivision);
		}
	}
}
void crunchGameStats(TEAM league[], GAME& game){
	int homeTeamId = getTeamId(game.homeTeam.nickname);
	int awayTeamId = getTeamId(game.awayTeam.nickname);

	// increment games played against particular club
	game.homeTeam.gamesAgainstCertainTeam[awayTeamId]++;
	game.awayTeam.gamesAgainstCertainTeam[homeTeamId]++;

	// update points for, points against totals
	game.homeTeam.pointsForCertainTeam[awayTeamId] += game.homeScore;
	game.homeTeam.pointsAgainstCertainTeam[awayTeamId] += game.awayScore;
	game.awayTeam.pointsForCertainTeam[homeTeamId] += game.awayScore;
	game.awayTeam.pointsAgainstCertainTeam[homeTeamId] += game.homeScore;

	// assign playoff points
	if(game.homeScore == game.awayScore){ // if game tied
		game.homeTeam.playoffPoints++;
		game.awayTeam.playoffPoints++;
	}
	else if(game.homeScore > game.awayScore){ // if home team wins
		game.homeTeam.playoffPoints += 2;
		game.homeTeam.totalWins++;
		game.homeTeam.winsAgainstCertainTeam[awayTeamId]++;
	}
	else if(game.homeScore < game.awayScore){ // if away team wins
		game.awayTeam.playoffPoints += 2;
		game.awayTeam.totalWins++;
		game.awayTeam.winsAgainstCertainTeam[homeTeamId]++;
	}
}

/* void simulateGame
 *
 * Purpose:	Simulates results (score and winner) for a single game
 */
void simulateGame(GAME& game){
	srand(time(0)); // seed random variable
	game.homeScore = rand() % 65; // generate random score for home team
	game.awayScore = rand() % 65; // generate random score for away team
}

/* void simulateSeason
 *
 */
void simulateSeason(TEAM leagueStats[], GAME seasonSchedule[][MAX_GAMES_PER_WEEK]){
	// initialize full season record stats to zero for all teams
	for(int i = 0; i < NUMBER_OF_TEAMS; i++){
		leagueStats[i].firstPlaceFinishes = 0;
		leagueStats[i].secondPlaceFinishes = 0;
		leagueStats[i].thirdPlaceFinishes = 0;
		leagueStats[i].crossovers = 0;
		leagueStats[i].timesMissedPlayoffs = 0;
	}

	cout << "Simulating season . . . " << endl;
	for(int i = 0; i < NUMBER_OF_SIMULATIONS; i++){ // run full season simulation n times
		// copy the season schedule to a new array
		GAME seasonSchedule_copy[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK];
		copySchedule(seasonSchedule_copy, seasonSchedule);
		// initialize all teams to not ranked (will be used to determine finishing order at end of season)
		for(int x = 0; x < NUMBER_OF_TEAMS; x++) leagueStats[x].ranked = false;
		for(int j = 0; j < NUMBER_OF_WEEKS; j++){ // simulate each week
			simulateWeek(leagueStats, seasonSchedule_copy[j]);
		}

		// calculate final division rankings
		crunchSeasonStats(leagueStats, seasonSchedule_copy);
		// update each team's stats

		// update user on number of procedures incompleted
		int percentageComplete = ( (i + 1) / NUMBER_OF_SIMULATIONS)* 100;
		if(percentageComplete == 20) cout << "20% . . ." << endl;
		else if(percentageComplete == 40) cout << "40% . . ." << endl;
		else if(percentageComplete == 60) cout << "60% . . ." << endl;
		else if(percentageComplete == 80) cout << "80% . . ." << endl;
	}
	cout << "Season simulation complete!" << endl;

	createOutputFile(); // generate output file of season results

	cout << "Simulation results output as readout.txt" << endl;
}

/* void simulateWeek
 *
 * Purpose:
 * 		Simulates a single week in the CFL schedule
 *
 */
void simulateWeek(TEAM league[], GAME weekSchedule[]){
	for(int i = 0; i < MAX_GAMES_PER_WEEK; i++){ // loop through all 4 possible games per week
		if(weekSchedule[i].scheduled == true) // check if game scheduled
			if(weekSchedule[i].completed == false) // check if game already played
				simulateGame(weekSchedule[i]); // simulate the game if scheduled and not already played
	}
}

