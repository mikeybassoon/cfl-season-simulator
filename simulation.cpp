/*
 * simulation.cpp
 *
 *  Created on: Aug. 20, 2019
 *      Author: michaelmacaulay
 */

#include "simulation.h"
#include "league_classes.h"
#include <iostream>
#include <vector>

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
	for(int x = 0; x < NUMBER_OF_WEEKS; x++){ // for each week of season
		for(int y =0; y < MAX_GAMES_PER_WEEK; y++){ // for each game in week
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

	// find the top four teams in each division
	for(int i = 0; i < 5; i ++){
		westDivision[i] = findWinner(0, 4);
		eastDivision[i] = findWinner(5, 8);
	}

	// set fifth-place west team
	westDivision[4] = findWinner(0, 4);

	// update results for first, second, fifth-place teams
	league[westDivision[0]].add_firstPlace();
	league[eastDivision[0]].add_firstPlace();
	league[westDivision[1]].add_secondPlace();
	league[eastDivision[1]].add_secondPlace();
	league[westDivision[4]].add_missedPlayoffs();

	// test if crossover in effect

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

int findWinner(const int minIndex, const int maxIndex){
	string division;
	if(minIndex == 0) division = "west";
	else if(minIndex ==5) division = "east";


	vector<int> winners; // holds league array indices of all currently tied winners

	// check playoff points
	int winningValue = 0;
	for(int x = minIndex; x <= maxIndex; x++){
		if(!sim_league[x].is_ranked()){ // not yet ranked?
			if(sim_league[x].get_playoffPoints() > winningValue){ // new winner?
				winningValue = sim_league[x].get_playoffPoints(); // set new winning value
				winners.resize(1); // set winners vector size to 1
				winners[0] = x; // place new winner in winners vector
			}
			else if(sim_league[x].get_playoffPoints() == winningValue){ // tied with winner?
				winners.push_back(x); // add x to end of vector
			}
		}
	}
	if(winners.size() == 1){ // only one winner?
		sim_league[winners[0]].set_ranked(true); // set winner to ranked
		return winners[0]; // return winning index
	}

	// if no winner, check highest number of games won against whole league
	winningValue = 0; // reset winning value
	vector<int> gamesWinners; // vector to hold winners of second stage
	for(int i = 0; i < winners.size(); i++){ // for all teams in winners vector
		if(sim_league[winners[i]].get_wins() > winningValue){ // new winner?
			winningValue = sim_league[winners[i]].get_wins(); // set new winning value
			gamesWinners.resize(1); // set winners vector size to 1
			gamesWinners[0] = winners[i]; // place new winner in winners vector
		}
		else if(sim_league[winners[i]].get_wins() == winningValue){ // tie?
			gamesWinners.push_back(winners[i]); // add tied entry to winners vector
		}
	}
	if(gamesWinners.size() == 1){ // only one winner?
		sim_league[gamesWinners[0]].set_ranked(true); // set winner ranked to true
		return gamesWinners[0];
	}
	winners.resize(0); // erase winners vector (no longer needed)

	// if no single winner, check winning percentages against tied clubs
	winningValue = 0; // reset winning value
	vector<int> pctWinners; // vector to hold winners of third stage

	for(int i = 0; i < gamesWinners.size(); i++){ // for every team in the winner vector
		int wins = 0; // wins against all other teams in the vector
		int losses = 0; // losses against all other teams in the vector
		int winPercentage; // cowmbined win percentage against all other teams in the vector
		for(int j = 0; j < gamesWinners.size(); j++){ // for every team in the winner vector
			if(i != j){ // team not compared against itself?
				wins += sim_league[gamesWinners[i]].get_winsAgainst(gamesWinners[j]); // add wins against this team
				losses += sim_league[gamesWinners[i]].get_lossesAgainst(gamesWinners[j]); // add losses against this team
			}
		}
		winPercentage = (wins * 1000) / losses;
		if(winPercentage > winningValue){ // new winner?
			winningValue = winPercentage; // set new winning value
			pctWinners.resize(1); // set pctWinners vector size to 1
			pctWinners[0] = gamesWinners[i]; // place new winner in pctWinners vector
		}
		else if(winPercentage == winningValue){ // tie?
			pctWinners.push_back(gamesWinners[i]); // add tied index to pctWinners vector
		}
	}
	if(pctWinners.size() == 1){ // only one winner?
		sim_league[pctWinners[0]].set_ranked(true); // set winner to ranked
		return pctWinners[0]; // return winner
	}

	gamesWinners.resize(0); // erase gamesWinners vector, no longer needed

	// if no winner compare combined net aggregate points against all tied clubs
	winningValue = 0; // reset winningValue
	vector<int> netAggWinners; // vector to hold winners of next stage

	for(int i = 0; i < pctWinners.size(); i++){ // for all teams in pctWinners
		int pointsScored = 0;
		int pointsAllowed = 0;
		int netAggregate;
		for(int j = 0; j < pctWinners.size(); j++){ // for all teams in pctWinners
			if(i != j){ // team not being compared to itself?
				pointsScored += sim_league[pctWinners[i]].get_pointsScoredAgainst(pctWinners[j]);
				pointsAllowed += sim_league[pctWinners[i]].get_pointsAllowedAgainst(pctWinners[j]);
			}
		}
		netAggregate = pointsScored - pointsAllowed;
		if(netAggregate > winningValue){ // new winner?
			winningValue = netAggregate; // set new winning value
			netAggWinners.resize(1); // resize winner array
			netAggWinners[0] = pctWinners[i]; // place new winner in winner vector
		}
		else if(netAggregate == winningValue){ // tie?
			netAggWinners.push_back(pctWinners[i]); // add to winner vector
		}
	}
	if(netAggWinners.size() == 1){ // only 1 winner?
		sim_league[netAggWinners[0]].set_ranked(true); // winner set to ranked
		return netAggWinners[0]; // return winning value
	}

	pctWinners.resize(0); // erase pctWinners vector

	// if no winner compare combined net quotient points against all tied clubs
	winningValue = 0; // reset winning value
	vector<int> netQuotWinners; // vector to hold winners

	for(int i = 0; i < netAggWinners.size(); i++){ // for all teams in vector
		int pointsScored = 0;
		int pointsAllowed = 0;
		int netQuotient;
		for(int j = 0; j < netAggWinners.size(); j++){ // for all teams in pctWinners
			if(i != j){ // team not being compared to itself?
				pointsScored += sim_league[netAggWinners[i]].get_pointsScoredAgainst(netAggWinners[j]);
				pointsAllowed += sim_league[netAggWinners[i]].get_pointsAllowedAgainst(netAggWinners[j]);
			}
		}
		netQuotient = (1000 * pointsScored) / pointsAllowed;
		if(netQuotient > winningValue){ // new winner?
			winningValue = netQuotient; // set new winning value
			netQuotWinners.resize(1); // resize winner array
			netQuotWinners[0] = netAggWinners[i]; // place new winner in winner vector
		}
		else if(netQuotient == winningValue){ // tie?
			netQuotWinners.push_back(netAggWinners[i]); // add to winner vector
		}
	}
	if(netQuotWinners.size() == 1){ // only 1 winner?
		sim_league[netQuotWinners[0]].set_ranked(true); // winner set to ranked
		return netQuotWinners[0]; // return winning value
	}
	netAggWinners.resize(0); // erase net agg winners vector

	// if no winner compare division win percentages
	winningValue = 0;
	vector<int> divPctWinners;

	for(int i = 0; i < netQuotWinners.size(); i++){
		if(sim_league[netQuotWinners[i]].get_winPercentage(division) > winningValue){ // new winner?
			winningValue = sim_league[netQuotWinners[i]].get_winPercentage(division);
			divPctWinners.resize(1);
			divPctWinners[0] = netQuotWinners[i];
		}
		else if(sim_league[netQuotWinners[i]].get_winPercentage(division) == winningValue){ // tie?
			divPctWinners.push_back(netQuotWinners[i]); // add to winner vector
		}
	}
	if(divPctWinners.size() == 1){ // only 1 winner?
		sim_league[divPctWinners[0]].set_ranked(true); // set winner to ranked
		return divPctWinners[0];
	}
	netQuotWinners.resize(0); // erase net quotient winners vector

	// if no winner compare net aggregate points against division
	winningValue = 0;

	for(int i = 0; i < divPctWinners.size(); i++){
		if(sim_league[divPctWinners[i]].get_netAggregate(division) > winningValue){ // new winner?
			winningValue = sim_league[divPctWinners[i]].get_netAggregate(division);
			netAggWinners.resize(1);
			netAggWinners[0] = divPctWinners[i];
		}
		else if(sim_league[divPctWinners[i]].get_netAggregate(division) == winningValue){ // tie?
			netAggWinners.push_back(divPctWinners[i]); // add to winner vector
		}
	}
	if(netAggWinners.size() == 1){ // only 1 winner?
		sim_league[netAggWinners[0]].set_ranked(true); // set winner to ranked
		return netAggWinners[0];
	}
	divPctWinners.resize(0); // erase division percentage winner vector

	// if no winner compare net quotient points against division
	winningValue = 0;

	for(int i = 0; i < netAggWinners.size(); i++){
		if(sim_league[netAggWinners[i]].get_netQuotient(division) > winningValue){ // new winner?
			winningValue = sim_league[netAggWinners[i]].get_netQuotient(division);
			netQuotWinners.resize(1);
			netQuotWinners[0] = netAggWinners[i];
		}
		else if(sim_league[netAggWinners[i]].get_netQuotient(division) == winningValue){ // tie?
			netQuotWinners.push_back(netAggWinners[i]); // add to winner vector
		}
	}
	if(netQuotWinners.size() == 1){ // only 1 winner?
		sim_league[netQuotWinners[0]].set_ranked(true); // set winner to ranked
		return netQuotWinners[0];
	}
	netAggWinners.resize(0); // erase old winner vector

	// if no winner compare net aggregate points against league
	winningValue = 0;

	for(int i = 0; i < netQuotWinners.size(); i++){
		if(sim_league[netQuotWinners[i]].get_netAggregate() > winningValue){ // new winner?
			winningValue = sim_league[netQuotWinners[i]].get_netAggregate();
			netAggWinners.resize(1);
			netAggWinners[0] = netQuotWinners[i];
		}
		else if(sim_league[netQuotWinners[i]].get_netAggregate() == winningValue){ // tie?
			netAggWinners.push_back(netQuotWinners[i]); // add to winner vector
		}
	}
	if(netAggWinners.size() == 1){ // only 1 winner?
		sim_league[netAggWinners[0]].set_ranked(true); // set winner to ranked
		return netAggWinners[0];
	}
	netQuotWinners.resize(0); // erase old winner vector

	// if no winner compare net quotient points against league
	winningValue = 0;

	for(int i = 0; i < netAggWinners.size(); i++){
		if(sim_league[netAggWinners[i]].get_netQuotient() > winningValue){ // new winner?
			winningValue = sim_league[netAggWinners[i]].get_netQuotient();
			netQuotWinners.resize(1);
			netQuotWinners[0] = netQuotWinners[i];
		}
		else if(sim_league[netAggWinners[i]].get_netQuotient() == winningValue){ // tie?
			netQuotWinners.push_back(netAggWinners[i]); // add to winner vector
		}
	}
	if(netQuotWinners.size() == 1){ // only 1 winner?
		sim_league[netQuotWinners[0]].set_ranked(true); // set winner to ranked
		return netQuotWinners[0];
	}
	netAggWinners.resize(0);

	// if no winner, determine winner by random coin flip
	while(netQuotWinners.size() > 1){ // while more than one winner remains
		netQuotWinners.erase(netQuotWinners.begin() + (rand() % 2) ); // randomly erase one of the first two elements of the vector
	}
	return netQuotWinners[0]; // return the final winner
}
