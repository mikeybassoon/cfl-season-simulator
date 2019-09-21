/*
 * simulation.cpp
 *
 *  Created on: Aug. 20, 2019
 *      Author: michaelmacaulay
 */

#include "simulation.h"
#include "league_classes.h"
#include "initialize.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cassert>

using namespace std;

void copySchedule(){
	for(int x = 0; x < NUMBER_OF_WEEKS; x++){ // for each week of season
		for(int y =0; y < MAX_GAMES_PER_WEEK; y++){ // for each game in week
			sim_seasonSchedule[x][y] = seasonSchedule[x][y]; // copy all game details to sim_seasonSchedule
		}
	}
}

void copyLeague(){
	for(int x = 0; x < NUMBER_OF_TEAMS; x++){ // for each team in league
		sim_league[x] = league[x]; // copy all team details to sim_league
	}
}

void simulateSeason(){
	// set all teams "ranked" status to false
	for(int x = 0; x < NUMBER_OF_TEAMS; x++){
		sim_league[x].set_ranked(false);
	}
	for(int x = 0; x < NUMBER_OF_WEEKS; x++){ // for each week of season
		for(int y = 0; y < MAX_GAMES_PER_WEEK; y++){ // for each game in week
			if(sim_seasonSchedule[x][y].is_scheduled() // game scheduled?
					and !sim_seasonSchedule[x][y].was_played()){ // game not yet played?
				sim_seasonSchedule[x][y].simulate_game(); // simulate the game
			}
		}
	}
}

void crunchSeasonResults(){
	bool eastCrossesOver;
	bool westCrossesOver;
	int westDivision[5], eastDivision[4]; // create arrays to hold teamIDs of rankings in each division

	vector<int> eastTeams, westTeams; // division vectors to pass to findWinner function
	eastTeams.resize(4);
	westTeams.resize(5);

	// store team IDs to division vectors
	for(int i = 0; i <= 4; i++){
		westTeams[i] = i;
	}
	for(int i = 0; i <= 3; i++){
		eastTeams[i] = i + 5;
	}

	// find the top four teams in each division
	for(int i = 0; i < 4; i ++){
		westDivision[i] = findWinner(westTeams);
		assert(westTeams.size() == 5);
		assert(eastTeams.size() == 4);
		eastDivision[i] = findWinner(eastTeams);
		assert(westTeams.size() == 5);
		assert(eastTeams.size() == 4);
	}

	// set fifth-place west team
	westDivision[4] = findWinner(westTeams); // only one team should be left unranked

	// update results for first, second, fifth-place teams
	league[westDivision[0]].add_firstPlace();
	league[eastDivision[0]].add_firstPlace();
	league[westDivision[1]].add_secondPlace();
	league[eastDivision[1]].add_secondPlace();
	league[westDivision[4]].add_missedPlayoffs();

	// test if crossover in effect

	// declare vectors to hold the teams being compared in the crossover checks
	vector<int> eastCrossoverCheck(2);
	vector<int> westCrossoverCheck(2);
	eastCrossoverCheck[0] = eastDivision[3];
	eastCrossoverCheck[1] = westDivision[2];

	westCrossoverCheck[0] = westDivision[3];
	westCrossoverCheck[1] = eastDivision[2];

	// set teams in crossover checks to unranked
	for(int i = 0; i < 2; i++){
		sim_league[eastCrossoverCheck[i]].set_ranked(false);
		sim_league[westCrossoverCheck[i]].set_ranked(false);
	}

	if(findWinner(eastCrossoverCheck) >= 5){
		eastCrossesOver = true;
		westCrossesOver = false;
	}
	else if(findWinner(westCrossoverCheck) <= 4){
		westCrossesOver = true;
		eastCrossesOver = false;
	}
	else{
		eastCrossesOver = false;
		westCrossesOver = false;
	}

	// update third and fourth place team results according to crossover status
	if(eastCrossesOver){
		league[westDivision[2]].add_missedPlayoffs();
		league[westDivision[3]].add_missedPlayoffs();
		league[eastDivision[2]].add_thirdPlace();
		league[eastDivision[3]].add_crossover();
	}
	else if(westCrossesOver){
		league[westDivision[2]].add_thirdPlace();
		league[westDivision[3]].add_crossover();
		league[eastDivision[2]].add_missedPlayoffs();
		league[eastDivision[3]].add_missedPlayoffs();
	}
	else{
		league[westDivision[2]].add_thirdPlace();
		league[westDivision[3]].add_missedPlayoffs();
		league[eastDivision[2]].add_thirdPlace();
		league[eastDivision[3]].add_missedPlayoffs();
	}
}

int findWinner(const vector<int>& teams){

	vector<int>&& playoffPoints = checkPlayoffPoints(teams);
	assert(playoffPoints.size() > 0);
	if(playoffPoints.size() == 1){
		sim_league[playoffPoints[0]].set_ranked(true);
		return playoffPoints[0];
	}

	vector<int>&& totalWins = checkTotalWins(playoffPoints);
	assert(totalWins.size() > 0);
	if(totalWins.size() == 1){
		sim_league[totalWins[0]].set_ranked(true);
		return totalWins[0];
	}
	playoffPoints.resize(0);

	vector<int>&& winPctAgainstTied = checkWinPctAgainstTied(totalWins);
	assert(winPctAgainstTied.size() > 0);
	if(winPctAgainstTied.size() == 1){
		sim_league[winPctAgainstTied[0]].set_ranked(true);
		return winPctAgainstTied[0];
	}
	totalWins.resize(0);

	vector<int>&& netAggAgainstTied = checkNetAggAgainstTied(winPctAgainstTied);
	assert(netAggAgainstTied.size() > 0);
	if(netAggAgainstTied.size() == 1){
		sim_league[netAggAgainstTied[0]].set_ranked(true);
		return netAggAgainstTied[0];
	}
	winPctAgainstTied.resize(0);

	vector<int>&& netQuotAgainstTied = checkNetQuotAgainstTied(netAggAgainstTied);
	assert(netQuotAgainstTied.size() > 0);
	if(netQuotAgainstTied.size() == 1){
		sim_league[netQuotAgainstTied[0]].set_ranked(true);
		return netQuotAgainstTied[0];
	}
	netAggAgainstTied.resize(0);

	vector<int>&& winPctAgainstDiv = checkWinPctAgainstDiv(netQuotAgainstTied);
	assert(winPctAgainstDiv.size() > 0);
	if(winPctAgainstDiv.size() == 1){
		sim_league[winPctAgainstDiv[0]].set_ranked(true);
		return winPctAgainstDiv[0];
	}
	netQuotAgainstTied.resize(0);

	vector<int>&& netAggAgainstDiv = checkNetAggAgainstDiv(winPctAgainstDiv);
	assert(netAggAgainstDiv.size() > 0);
	if(netAggAgainstDiv.size() == 1){
		sim_league[netAggAgainstDiv[0]].set_ranked(true);
		return netAggAgainstDiv[0];
	}
	winPctAgainstDiv.resize(0);

	vector<int>&& netQuotAgainstDiv = checkNetQuotAgainstDiv(netAggAgainstDiv);
	assert(netQuotAgainstDiv.size() > 0);
	if(netQuotAgainstDiv.size() == 1){
		sim_league[netQuotAgainstDiv[0]].set_ranked(true);
		return netQuotAgainstDiv[0];
	}
	netAggAgainstDiv.resize(0);

	vector<int>&& netAggTotal = checkNetAggTotal(netQuotAgainstDiv);
	assert(netAggTotal.size() > 0);
	if(netAggTotal.size() == 1){
		sim_league[netAggTotal[0]].set_ranked(true);
		return netAggTotal[0];
	}
	netQuotAgainstDiv.resize(0);

	vector<int>&& netQuotTotal = checkNetQuotTotal(netAggTotal);
	assert(netQuotTotal.size() > 0);
	if(netQuotTotal.size() == 1){
		sim_league[netQuotTotal[0]].set_ranked(true);
		return netQuotTotal[0];
	}
	netAggTotal.resize(0);

	int winner = coinFlip(netQuotTotal);
	sim_league[winner].set_ranked(true);

	return winner;
}

vector<int> checkPlayoffPoints(const vector<int>& teams){
	vector<int> winners;
	int winningValue = 0;
	for(int x = 0; x < teams.size(); x++){
		Team thisTeam = sim_league[teams[x]];
		if(thisTeam.is_ranked() == false){ // not yet ranked?
			if(thisTeam.get_playoffPoints() > winningValue){ // new winner?
				winningValue = thisTeam.get_playoffPoints(); // set new winning value
				winners.resize(1); // set winners vector size to 1
				winners[0] = thisTeam.get_teamID(); // place new winner in winners vector
			}
			else if(thisTeam.get_playoffPoints() == winningValue){ // tied with winner?
				winners.push_back(thisTeam.get_teamID()); // add new winner to vector
			}
		}
	}
	return winners;
}

vector<int> checkTotalWins(const vector<int>& teams){
	assert(teams.size() > 0);
	vector<int> winners;
	int winningValue = 0;
	for(int x = 0; x < teams.size(); x++){ // for each tied team
		Team thisTeam = sim_league[teams[x]];
		if(thisTeam.is_ranked() == false){ // not yet ranked?
			if(thisTeam.get_wins() > winningValue){ // new winner?
				winningValue = thisTeam.get_wins(); // set new winning value
				winners.resize(1); // set winners vector size to 1
				winners[0] = thisTeam.get_teamID(); // place new winner in winners vector
			}
			else if(thisTeam.get_wins() == winningValue){ // tied with winner?
				winners.push_back(thisTeam.get_teamID()); // add new winner to vector
			}
		}
	}
	return winners;
}

vector<int> checkWinPctAgainstTied(const vector<int>& teams){
	assert(teams.size() > 0);
	vector<int> winners;
	int winningValue = 0;
	for(int x = 0; x < teams.size(); x++){ // for every team in the winner vector
		int wins = 0;
		int losses = 0;
		int ties = 0;
		Team thisTeam = sim_league[teams[x]];
		for(int y = 0; y < teams.size(); y++){ // for every team in the winner vector
			if(x != y){ // team not compared against itself?
				wins += thisTeam.get_winsAgainst(teams[y]);
				losses += thisTeam.get_lossesAgainst(teams[y]);
				ties += thisTeam.get_tiesAgainst(teams[y]);
			}
		}
		assert(wins + losses + ties != 0);

		int winPercentage = (wins * 1000) / (wins + losses + ties);
		if(winPercentage > winningValue){ // new winner?
			winningValue = winPercentage; // set new winning value
			winners.resize(1); // set winners vector size to 1
			winners[0] = thisTeam.get_teamID(); // place new winner in winners vector
		}
		else if(winPercentage == winningValue){ // tie?
			winners.push_back(thisTeam.get_teamID()); // add tied team to winners vector
		}
	}
	return winners;
}

vector<int> checkNetAggAgainstTied(const vector<int>& teams){
	assert(teams.size() > 0);
	vector<int> winners;
	int winningValue;

	int pointsScored = 0;
	int pointsAllowed = 0;
	int netAggregate;

	// calculate default winningValue (first team's net aggregate)
	for (int i = 1; i < teams.size(); i++) {
		pointsScored += sim_league[teams[0]].get_pointsScoredAgainst(i);
		pointsAllowed += sim_league[teams[0]].get_pointsAllowedAgainst(i);
	}
	Team thisTeam = sim_league[teams[0]];
	netAggregate = pointsScored - pointsAllowed;
	winners.resize(1); // resize winner array
	winners[0] = thisTeam.get_teamID(); // place first team in winner vector

	winningValue = netAggregate; // default winning score set

	for(int i = 1; i < teams.size(); i++){ // for all teams in pctWinners except the first
		pointsScored = 0;
		pointsAllowed = 0;
		Team thisTeam = sim_league[teams[i]];
		for(int j = 0; j < teams.size(); j++){ // for all teams in pctWinners
			if(i != j){ // team not being compared to itself?
				pointsScored += thisTeam.get_pointsScoredAgainst(teams[j]);
				pointsAllowed += thisTeam.get_pointsAllowedAgainst(teams[j]);
			}
		}
		netAggregate = pointsScored - pointsAllowed;
		if(netAggregate > winningValue){ // new winner?
			winningValue = netAggregate; // set new winning value
			winners.resize(1); // resize winner array
			winners[0] = thisTeam.get_teamID(); // place new winner in winner vector
		}
		else if(netAggregate == winningValue){ // tie?
			winners.push_back(thisTeam.get_teamID()); // add to winner vector
		}
	}
	return winners;
}

vector<int> checkNetQuotAgainstTied(const vector<int>& teams){
	assert(teams.size() > 0);
	vector<int> winners;
	int winningValue = 0;
	for(int i = 0; i < teams.size(); i++){ // for all teams in pctWinners
		int pointsScored = 0;
		int pointsAllowed = 0;
		int netQuotient;
		Team thisTeam = sim_league[teams[i]];
		for(int j = 0; j < teams.size(); j++){ // for all teams in pctWinners
			if(i != j){ // team not being compared to itself?
				pointsScored += thisTeam.get_pointsScoredAgainst(teams[j]);
				pointsAllowed += thisTeam.get_pointsAllowedAgainst(teams[j]);
			}
		}
		if (pointsAllowed == 0)
			pointsAllowed = 1; // avoid divide by zero
		netQuotient = (1000 * pointsScored) / pointsAllowed;
		if(netQuotient > winningValue){ // new winner?
			winningValue = netQuotient; // set new winning value
			winners.resize(1); // resize winner array
			winners[0] = thisTeam.get_teamID(); // place new winner in winner vector
		}
		else if(netQuotient == winningValue){ // tie?
			winners.push_back(thisTeam.get_teamID()); // add to winner vector
		}
	}
	return winners;
}

vector<int> checkWinPctAgainstDiv(const vector<int>& teams){
	assert(teams.size() > 0);
	vector<int> winners;
	int winningValue = 0;
	for(int i = 0; i < teams.size(); i++){ // for every team in the winner vector
		Team thisTeam = sim_league[teams[i]];
		int winPercentage = thisTeam.get_winPercentage(thisTeam.get_division());
		if(winPercentage > winningValue){ // new winner?
			winningValue = winPercentage; // set new winning value
			winners.resize(1); // set winners vector size to 1
			winners[0] = thisTeam.get_teamID(); // place new winner in winners vector
		}
		else if(winPercentage == winningValue){ // tie?
			winners.push_back(thisTeam.get_teamID()); // add tied index to winners vector
		}
	}
	return winners;
}

vector<int> checkNetAggAgainstDiv(const vector<int>& teams){
	assert(teams.size() > 0);
	vector<int> winners;
	int winningValue;

	Team thisTeam = sim_league[teams[0]];
	winningValue = thisTeam.get_netAggregate(thisTeam.get_division()); // set default value to first team
	winners.resize(1);
	winners[0] = 0; // first team is placed into winner vector

	for(int i = 0; i < teams.size(); i++){
		Team thisTeam = sim_league[teams[i]];
		int netAggregate = thisTeam.get_netAggregate(thisTeam.get_division());
		if(netAggregate > winningValue){ // new winner?
			winningValue = netAggregate;
			winners.resize(1);
			winners[0] = thisTeam.get_teamID();
		}
		else if(netAggregate == winningValue){
			winners.push_back(thisTeam.get_teamID());
		}
	}
	return winners;
}

vector<int> checkNetQuotAgainstDiv(const vector<int>& teams){
	assert(teams.size() > 0);
	vector<int> winners;
	int winningValue = 0;
	for(int i = 0; i < teams.size(); i++){
		Team thisTeam = sim_league[teams[i]];
		int netQuotient = thisTeam.get_netQuotient(thisTeam.get_division());
		if(netQuotient > winningValue){ // new winner?
			winningValue = netQuotient;
			winners.resize(1);
			winners[0] = thisTeam.get_teamID();
		}
		else if(netQuotient == winningValue){
			winners.push_back(thisTeam.get_teamID());
		}
	}
	return winners;
}

vector<int> checkNetAggTotal(const vector<int>& teams){
	assert(teams.size() > 0);
	vector<int> winners;
	int winningValue;

	// first team is winner by default
	Team thisTeam = sim_league[teams[0]];
	winningValue = thisTeam.get_netAggregate(); // get total net aggregate for first time
	winners.resize(1);
	winners[0] = 0;

	for(int i = 1; i < teams.size(); i++){ // for every team after first
		Team thisTeam = sim_league[teams[i]];
		int netAggregate = thisTeam.get_netAggregate();
		if(netAggregate > winningValue){ // new winner?
			winningValue = netAggregate;
			winners.resize(1);
			winners[0] = thisTeam.get_teamID();
		}
		else if(netAggregate == winningValue){
			winners.push_back(thisTeam.get_teamID());
		}
	}
	return winners;
}

vector<int> checkNetQuotTotal(const vector<int>& teams){
	assert(teams.size() > 0);
	vector<int> winners;
	int winningValue = 0;
	for(int i = 0; i < teams.size(); i++){
		Team thisTeam = sim_league[teams[i]];
		int netQuotient = thisTeam.get_netQuotient();
		if(netQuotient > winningValue){
			winningValue = netQuotient;
			winners.resize(1);
			winners[0] = thisTeam.get_teamID();
		}
		else if(netQuotient == winningValue){
			winners.push_back(thisTeam.get_teamID());
		}
	}
	return winners;
}

int coinFlip(const vector<int>& teams){
	assert(teams.size() > 0);
	int winner = rand() % teams.size();
	return teams[winner];
}

void print_report(){
#define wide 30
#define narrow 10
	ofstream file;
	file.open("report.txt");
	file << "=== CFL SEASON SIMULATION: SUMMARY ===" << endl << endl;
	file << "Simulations run: " << NUMBER_OF_SIMULATIONS << endl << endl;
	file << "TEAM RESULTS" << endl << endl;

	for(int i = 0; i < NUMBER_OF_TEAMS; i++){
		file << fixed;
		file << league[i].get_name() << endl;
		file << "Division: " << league[i].get_division() << endl << endl;
		file << setw(wide) << left << "1st place finishes:" << setw(narrow) << league[i].get_firstPlace()
				<< setw(narrow) << setprecision(3) << league[i].get_firstPlaceOdds() << endl;
		file << setw(wide) << left << "2nd place finishes:" << setw(narrow) << league[i].get_secondPlace()
				<< setw(narrow) << setprecision(3) << league[i].get_secondPlaceOdds() << endl;
		file << setw(wide) << left << "3rd place (made playoffs):" << setw(narrow) << league[i].get_thirdPlace()
				<< setw(narrow) << setprecision(3) << league[i].get_thirdPlaceOdds() << endl;
		file << setw(wide) << left << "Crossovers:" << setw(narrow) << league[i].get_crossovers()
				<< setw(narrow) << setprecision(3) << league[i].get_crossoverOdds() << endl;
		file << setw(wide) << left << "Times missed playoffs:" << setw(narrow) << league[i].get_missedPlayoffs()
				<< setw(narrow) << setprecision(3) << league[i].get_missedPlayoffsOdds() << endl;
		file << "% chance of making the playoffs: " << setprecision(3) << league[i].get_playoffOdds() << endl << endl;
	}

	file.close();
}
