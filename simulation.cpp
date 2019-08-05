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
#include <vector>

using namespace std;


bool copySchedule(Game destination[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK], const Game source[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]){
	for(int i = 0; i < NUMBER_OF_WEEKS; i++){
		for(int j = 0; j < MAX_GAMES_PER_WEEK; j++){
			destination[i][j] = source[i][j];
		}
	}
	return true;
}







void sortDivision(Team league[], Team westDivision[], Team eastDivision[]){
	int winnerArrayIndex;
	int divisionIndex = 0;
	int winningValue;
	int numberOfWinners;

	// check west division
	// step 1: check playoff points
	for(int i = 0; i < 5; i++){ // loop until division array full
		for(int j = 0; j < 5; j++){
			winningValue = 0; // highest point value observed so far
			numberOfWinners = 0; // holds all instances of winning value

			if(league[j].get_playoffPoints() > winningValue and league[j].is_ranked() == false){ // new winner?
				numberOfWinners = 1;
				winningValue = league[j].get_playoffPoints(); // set new winning value
				winnerArrayIndex = j; // mark winning index
			}
			else if(league[j].get_playoffPoints() == winningValue and league[j].is_ranked() == false) // tie?
				numberOfWinners++;
		}
		// once loop has run through entire division once
		// check if winner

		vector<Team> tiebreaker; // vector to hold remaining winners
		tiebreaker.resize(numberOfWinners); // set size to number of teams trying to break the tie
		int nextIndex = 0;

		for(int x = 0; x < 5; x++){ // find all winners and put their index in array
			if(league[x].get_playoffPoints() == winningValue){ // is this one of the winners?
				tiebreaker[nextIndex] = x; // store to next available space in vector
				nextIndex++; // increment to first unoccupied space in vector
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

