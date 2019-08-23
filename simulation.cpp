/*
 * simulation.cpp
 *
 *  Created on: Aug. 20, 2019
 *      Author: michaelmacaulay
 */

#include "simulation.h"
#include "league_classes.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

void copySchedule(){
	log << "Copying season schedule" << endl;
	log << "Copied schedule details:" << endl << endl;
	for(int x = 0; x < NUMBER_OF_WEEKS; x++){ // for each week of season
		log << "Week " << x + 1 << endl;
		for(int y =0; y < MAX_GAMES_PER_WEEK; y++){ // for each game in week
			sim_seasonSchedule[x][y] = seasonSchedule[x][y]; // copy all game details to sim_seasonSchedule
			if(sim_seasonSchedule[x][y].was_played())
				log << "Game " << y + 1 << ": Team " << sim_seasonSchedule[x][y].awayTeam() << " "
					<< sim_seasonSchedule[x][y].get_awayScore() << " @ Team " << sim_seasonSchedule[x][y].homeTeam()
					<< " " << sim_seasonSchedule[x][y].get_homeScore() << endl;
			else if(sim_seasonSchedule[x][y].is_scheduled()){
				log << "Game " << y + 1 << " (not yet played): Team " << sim_seasonSchedule[x][y].awayTeam()
						<< " @ " << sim_seasonSchedule[x][y].homeTeam() << endl;
			}
			else log <<"Game " << y + 1 << " not scheduled" << endl;
		}
	}
	log << endl << "copySchedule() completed, returning to calling function" << endl;
}

void copyLeague(){
	log << "Now in copyLeague()" << endl;
	log << "Copied team statistics:" << endl << endl;
	for(int x = 0; x < NUMBER_OF_TEAMS; x++){ // for each team in league
		sim_league[x] = league[x]; // copy all team details to sim_league
		Team thisTeam = sim_league[x];
		log << thisTeam.get_name() << "\t" << thisTeam.get_wins() << "\t" << thisTeam.get_losses()
				<< "\t" << thisTeam.get_ties() << "\t" << thisTeam.get_pointsScored()
				<< "\t" << thisTeam.get_pointsAllowed() << endl;
	}
	log << "copyLeague() completed, returning to calling function" << endl;
}

void simulateSeason(){
	log << "Now in simulateSeason()" << endl;
	log << "Setting team ranked status to false" << endl;
	log << "Value of \"ranked\":" << endl;
	// set all teams "ranked" status to false
	for(int x = 0; x < NUMBER_OF_TEAMS; x++){
		sim_league[x].set_ranked(false);
		log << sim_league[x].get_name() << ": " << sim_league[x].is_ranked() << endl;
	}
	log << "Simulating unplayed games in season" << endl;
	for(int x = 0; x < NUMBER_OF_WEEKS; x++){ // for each week of season
		for(int y = 0; y < MAX_GAMES_PER_WEEK; y++){ // for each game in week
			if(sim_seasonSchedule[x][y].is_scheduled() // game scheduled?
					and !sim_seasonSchedule[x][y].was_played()){ // game not yet played?
				sim_seasonSchedule[x][y].simulate_game(); // simulate the game
			}
		}
	}

	// print game results to log
	log << "Season results following simulation:" << endl << endl;
	for(int x = 0; x < NUMBER_OF_WEEKS; x++){ // for each week in season
		log << endl << "Week " << x + 1 << endl << endl;
		for(int y = 0; y < MAX_GAMES_PER_WEEK; y++){ // for each game in week
			if(sim_seasonSchedule[x][y].was_played()){
				log << "Game " << y + 1 << ": Team " << sim_seasonSchedule[x][y].awayTeam() << " "
						<< sim_seasonSchedule[x][y].get_awayScore() << " @ Team " << sim_seasonSchedule[x][y].homeTeam()
						<< " " << sim_seasonSchedule[x][y].get_homeScore() << endl;
			}
			else log << "Game " << y + 1 << " not scheduled" << endl;
		}
	}
	log << endl << "Team statistics following simulation:" << endl << endl;
	// print team results
	for(int i = 0; i < NUMBER_OF_TEAMS; i++){
		Team thisTeam = sim_league[i];
		log << thisTeam.get_name() << "\t" << thisTeam.get_wins() << "\t" << thisTeam.get_losses()
				<< "\t" << thisTeam.get_ties() << "\t" << thisTeam.get_pointsScored()
				<< "\t" << thisTeam.get_pointsAllowed() << "\t" << thisTeam.get_teamID() << endl;
	}
	log << "simulateSeason() completed, returning to calling function" << endl;
}

void crunchSeasonResults(){
	log << "Now in crunchSeasonResults" << endl;
	bool eastCrossesOver;
	bool westCrossesOver;
	int westDivision[5], eastDivision[4]; // create arrays to hold teamIDs of rankings in each division

	vector<int> eastTeams, westTeams; // division vectors to pass to findWinner function
	eastTeams.resize(4);
	westTeams.resize(5);

	log << "Sorting teams into division vectors" << endl;
	log << "West division:" << endl;
	// store team IDs to division vectors
	for(int i = 0; i <= 4; i++){
		westTeams[i] = i;
		log << i + 1 << ". " << sim_league[i].get_name() << endl;
	}
	log << endl << "East division:" << endl;
	for(int i = 0; i <= 3; i++){
		eastTeams[i] = i + 5;
		log << i + 5 + 1 << ". " << sim_league[i].get_name() << endl;
	}

	log << endl << "Determining top four teams in each division" << endl;

	// find the top four teams in each division
	for(int i = 0; i < 4; i ++){
		log << "Calling findWinner() from crunchSeasonResults()" << endl;
		westDivision[i] = findWinner(westTeams);
		eastDivision[i] = findWinner(eastTeams);
	}

	log << "Determining fifth-place west team - calling findWinner from crunchSeasonResults()" << endl;

	// set fifth-place west team
	westDivision[4] = findWinner(westTeams); // only one team should be left unranked

	log << "WEST DIVISION RANKINGS" << endl;
	for(int i = 0; i < 5; i++){
		log << i + 1 << ". " << sim_league[westDivision[i]].get_name() << endl;
	}

	log << "EAST DIVISION RANKINGS" << endl;
	for(int i = 0; i < 4; i++){
		log << i + 1 << ". " << sim_league[eastDivision[i+5]].get_name() << endl;
	}

	// update results for first, second, fifth-place teams
	league[westDivision[0]].add_firstPlace();
	league[eastDivision[0]].add_firstPlace();
	league[westDivision[1]].add_secondPlace();
	league[eastDivision[1]].add_secondPlace();
	league[westDivision[4]].add_missedPlayoffs();

	// test if crossover in effect

	vector<int> eastCrossoverCheck, westCrossoverCheck;
	eastCrossoverCheck[0] = eastDivision[3];
	eastCrossoverCheck[1] = westDivision[2];

	westCrossoverCheck[0] = westDivision[3];
	westCrossoverCheck[1] = eastDivision[2];

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

int findWinner(vector<int>& teams){

	log << "starting findWinner() first stage" << endl;

	vector<int>&& playoffPoints = checkPlayoffPoints(teams);
	assert(playoffPoints.size() > 0);
	if(playoffPoints.size() == 1){
		sim_league[playoffPoints[0]].set_ranked(true);
		return playoffPoints[0];
	}
	teams.resize(0);

	log << "starting findWinner() second stage" << endl;
	log << "Number of tied teams remaining: " << playoffPoints.size() << endl;

	vector<int>&& totalWins = checkTotalWins(playoffPoints);
	assert(totalWins.size() > 0);
	if(totalWins.size() == 1){
		sim_league[totalWins[0]].set_ranked(true);
		return totalWins[0];
	}
	playoffPoints.resize(0);

	log << "starting findWinner() third stage" << endl;
	log << "Number of tied teams remaining: " << totalWins.size() << endl;

	vector<int>&& winPctAgainstTied = checkWinPctAgainstTied(totalWins);
	assert(winPctAgainstTied.size() > 0);
	if(winPctAgainstTied.size() == 1){
		sim_league[winPctAgainstTied[0]].set_ranked(true);
		return winPctAgainstTied[0];
	}
	totalWins.resize(0);

	log << "starting findWinner() fourth stage" << endl;
	log << "Number of tied teams remaining: " << winPctAgainstTied.size() << endl;

	vector<int>&& netAggAgainstTied = checkNetAggAgainstTied(winPctAgainstTied);
	assert(netAggAgainstTied.size() > 0);
	if(netAggAgainstTied.size() == 1){
		sim_league[netAggAgainstTied[0]].set_ranked(true);
		return netAggAgainstTied[0];
	}
	winPctAgainstTied.resize(0);

	log << "starting findWinner() fifth stage" << endl;
	log << "Number of tied teams remaining: " << netAggAgainstTied.size() << endl;

	vector<int>&& netQuotAgainstTied = checkNetQuotAgainstTied(netAggAgainstTied);
	assert(netQuotAgainstTied.size() > 0);
	if(netQuotAgainstTied.size() == 1){
		sim_league[netQuotAgainstTied[0]].set_ranked(true);
		return netQuotAgainstTied[0];
	}
	netAggAgainstTied.resize(0);

	log << "starting findWinner() sixth stage" << endl;
	log << "Number of tied teams remaining: " << netQuotAgainstTied.size() << endl;

	vector<int>&& winPctAgainstDiv = checkWinPctAgainstDiv(netQuotAgainstTied);
	assert(winPctAgainstDiv.size() > 0);
	if(winPctAgainstDiv.size() == 1){
		sim_league[winPctAgainstDiv[0]].set_ranked(true);
		return winPctAgainstDiv[0];
	}
	netQuotAgainstTied.resize(0);

	log << "starting findWinner() seventh stage" << endl;
	log << "Number of tied teams remaining: " << winPctAgainstDiv.size() << endl;

	vector<int>&& netAggAgainstDiv = checkNetAggAgainstDiv(winPctAgainstDiv);
	assert(netAggAgainstDiv.size() > 0);
	if(netAggAgainstDiv.size() == 1){
		sim_league[netAggAgainstDiv[0]].set_ranked(true);
		return netAggAgainstDiv[0];
	}
	winPctAgainstDiv.resize(0);

	log << "starting findWinner() eigth stage" << endl;
	log << "Number of tied teams remaining: " << netAggAgainstDiv.size() << endl;

	vector<int>&& netQuotAgainstDiv = checkNetQuotAgainstDiv(netAggAgainstDiv);
	assert(netQuotAgainstDiv.size() > 0);
	if(netQuotAgainstDiv.size() == 1){
		sim_league[netQuotAgainstDiv[0]].set_ranked(true);
		return netQuotAgainstDiv[0];
	}
	netAggAgainstDiv.resize(0);

	log << "starting findWinner() ninth stage" << endl;
	log << "Number of tied teams remaining: " << netQuotAgainstDiv.size() << endl;

	vector<int>&& netAggTotal = checkNetAggTotal(netQuotAgainstDiv);
	assert(netAggTotal.size() > 0);
	if(netAggTotal.size() == 1){
		sim_league[netAggTotal[0]].set_ranked(true);
		return netAggTotal[0];
	}
	netQuotAgainstDiv.resize(0);

	log << "starting findWinner() tenth stage" << endl;
	log << "Number of tied teams remaining: " << netAggTotal.size() << endl;

	vector<int>&& netQuotTotal = checkNetQuotTotal(netAggTotal);
	assert(netQuotTotal.size() > 0);
	if(netQuotTotal.size() == 1){
		sim_league[netQuotTotal[0]].set_ranked(true);
		return netQuotTotal[0];
	}
	netAggTotal.resize(0);

	log << "starting findWinner() eleventh and final stage" << endl;
	log << "Number of tied teams remaining: " << netQuotTotal.size() << endl;

	int winner = coinFlip(netQuotTotal);
	sim_league[winner].set_ranked(true);

	log << "reached end of findWinner()" << endl;

	return winner;
}

vector<int> checkPlayoffPoints(vector<int>& teams){
	log << "Now inside checkPlayoffPoints()" << endl;
	log << "Number of teams being compared: " << teams.size() << endl;
	vector<int> winners;
	int winningValue = 0;
	for(int x = 0; x < teams.size(); x++){
		Team thisTeam = sim_league[teams[x]];
		log << "Team " << x + 1 << " number of playoff points: " << thisTeam.get_playoffPoints()
				<< " Ranked: " << thisTeam.is_ranked() << " ID: " << thisTeam.get_teamID() << endl;
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

vector<int> checkTotalWins(vector<int>& teams){
	assert(teams.size() > 0);
	log << "Now inside checkTotalWins()" << endl;
	log << "Number of teams being compared: " << teams.size() << endl;
	vector<int> winners;
	int winningValue = 0;
	for(int x = 0; x < teams.size(); x++){ // for each tied team
		Team thisTeam = sim_league[teams[x]];
		log << "Team " << x + 1 << " number of wins: " << thisTeam.get_wins()
				<< " Ranked: " << thisTeam.is_ranked() << " ID: " << thisTeam.get_teamID() << endl;
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
	log << "Number of teams being compared after checkTotalWins: " << winners.size() << endl;
	return winners;
}

vector<int> checkWinPctAgainstTied(vector<int>& teams){
	assert(teams.size() > 0);
	log << "Now inside checkWinPctAgainstTied()" << endl;
	log << "Number of teams being compared: " << teams.size() << endl;
	vector<int> winners;
	int winningValue = 0;
	for(int i = 0; i < teams.size(); i++){ // for every team in the winner vector
		int winPercentage; // cowmbined win percentage against all other teams in the vector
		Team thisTeam = sim_league[teams[i]];
		for(int j = 0; j < teams.size(); j++){ // for every team in the winner vector
			if(i != j){ // team not compared against itself?
				winPercentage = thisTeam.get_winPercentage(teams[j]);
			}
		}
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

vector<int> checkNetAggAgainstTied(vector<int>& teams){
	assert(teams.size() > 0);
	log << "Now inside checkNetAggAgainstTied()" << endl;
	log << "\tNumber of teams being compared: " << teams.size() << endl;
	vector<int> winners;
	int winningValue = 0;
	for(int i = 0; i < teams.size(); i++){ // for all teams in pctWinners
		int pointsScored = 0;
		int pointsAllowed = 0;
		int netAggregate;
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

vector<int> checkNetQuotAgainstTied(vector<int>& teams){
	assert(teams.size() > 0);
	log << "Now inside checkNetQuotAgainstTied()" << endl;
	log << "\tNumber of teams being compared: " << teams.size() << endl;
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
		netQuotient = (1000 * pointsScored) - pointsAllowed;
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

vector<int> checkWinPctAgainstDiv(vector<int>& teams){
	assert(teams.size() > 0);
	log << "Now inside checkWinPctAgainstDiv()" << endl;
	log << "\tNumber of teams being compared: " << teams.size() << endl;
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

vector<int> checkNetAggAgainstDiv(vector<int>& teams){
	assert(teams.size() > 0);
	log << "Now inside checkNetAggAgainstDiv()" << endl;
	log << "\tNumber of teams being compared: " << teams.size() << endl;
	vector<int> winners;
	int winningValue = 0;
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

vector<int> checkNetQuotAgainstDiv(vector<int>& teams){
	assert(teams.size() > 0);
	log << "Now inside checkNetQuotAgainstDiv()" << endl;
	log << "\tNumber of teams being compared: " << teams.size() << endl;
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

vector<int> checkNetAggTotal(vector<int>& teams){
	assert(teams.size() > 0);
	log << "Now inside checkNetAggTotal()" << endl;
	log << "\tNumber of teams being compared: " << teams.size() << endl;
	vector<int> winners;
	int winningValue = 0;
	for(int i = 0; i < teams.size(); i++){
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

vector<int> checkNetQuotTotal(vector<int>& teams){
	assert(teams.size() > 0);
	log << "Now inside checkNetQuotTotal()" << endl;
	log << "\tNumber of teams being compared: " << teams.size() << endl;
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

int coinFlip(vector<int>& teams){
	assert(teams.size() > 0);
	log << "Now inside coinFlip()" << endl;
	log << "\tNumber of teams being compared: " << teams.size() << endl;
	int winner = rand() % teams.size();
	log << "\tWinning index as selected by coin flip: " << winner << endl;
	return teams[winner];
}

void print_report(){
#define wide 25
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
		file << setw(wide) << left << "3rd place (made playoffs):" << setw(narrow) << league[i].get_secondPlace()
				<< setw(narrow) << setprecision(3) << league[i].get_thirdPlaceOdds() << endl;
		file << setw(wide) << left << "Crossovers:" << setw(narrow) << league[i].get_crossovers()
				<< setw(narrow) << setprecision(3) << league[i].get_crossoverOdds() << endl;
		file << setw(wide) << left << "Times missed playoffs:" << setw(narrow) << league[i].get_missedPlayoffs()
				<< setw(narrow) << setprecision(3) << league[i].get_missedPlayoffsOdds() << endl;
		file << "% chance of making the playoffs: " << setprecision(3) << league[i].get_playoffOdds() << endl << endl;
	}

	file.close();
}
