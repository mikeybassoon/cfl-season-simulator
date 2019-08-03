/*
 * league_classes.cpp
 *
 *  Created on: Jul. 30, 2019
 *      Author: michael
 */

#include <iostream>
#include "league_classes.h"
#include <cassert>

using namespace std;


Team::Team(string teamName, string div, int id){
	name = teamName;
	division = div;
	teamID = id;
	for(int i = 0; i < NUMBER_OF_TEAMS; i++){
		winsAgainst[i] = 0;
		lossesAgainst[i] = 0;
		tiesAgainst[i] = 0;
	}
	gamesPlayed = 0;
	isRanked = false;
	firstPlaceFinishes = secondPlaceFinishes = thirdPlaceFinishes = crossovers = timesMissedPlayoffs = 0;
}

string Team::get_name(){
	return name;
}

string Team::get_division(){
	return division;
}

int Team::get_playoffPoints() const{
	return get_wins() * 2 + get_ties();
}

int Team::get_teamID(){
	return teamID;
}

int Team::get_ties() const{
	int totalTies = 0;
	for(auto i:tiesAgainst)
		totalTies += i;
	return totalTies;
}

int Team::get_wins() const{
	int totalWins = 0;
	for(auto i:winsAgainst)
		totalWins += i;
	return totalWins;
}

int Team::get_winPercentage(int opponentID) const{
	int winPct = (winsAgainst[opponentID] * 1000) /
			(lossesAgainst[opponentID] + tiesAgainst[opponentID]);
	return winPct;
}

int Team::get_winPercentage(string& division) const{
	assert(division == "east" || division == "west");
	int divisionWins = 0;
	int divisionLosses = 0;
	int divisionTies = 0;
	if(division == "west"){
		for(int x = 0; x <= 4; x++){
			divisionWins += winsAgainst[x];
			divisionLosses += lossesAgainst[x];
			divisionTies += tiesAgainst[x];
		}
	}
	else if(division == "east"){
		for(int x = 5; x <= 8; x++){
			divisionWins += winsAgainst[x];
			divisionLosses += lossesAgainst[x];
			divisionTies += tiesAgainst[x];
		}
	}

	int divisionPct = (divisionWins * 1000) /
			(divisionLosses + divisionTies);
	return divisionPct;
}

int Team::get_netAggregate() const{
	int netAgg = 0;
	for(auto i:pointsScoredAgainst)
		netAgg += i;
	for(auto j:pointsAllowedAgainst)
		netAgg -= j;
	return netAgg;
}

int Team::get_netAggregate(int opponentID) const{
	int netAgg = pointsScoredAgainst[opponentID] - pointsAllowedAgainst[opponentID];
	return netAgg;
}

int Team::get_netAggregate(string& division) const{
	assert(division == "east" || division == "west");
	int netAgg = 0;
	if(division == "east"){
		for(int i = 5; i <= 8; i++){
			netAgg += pointsScoredAgainst[i];
			netAgg -= pointsAllowedAgainst[i];
		}
	}
	else if(division == "west"){
		for(int i = 0; i <= 4; i++){
			netAgg += pointsScoredAgainst[i];
			netAgg -= pointsAllowedAgainst[i];
		}
	}
	return netAgg;
}

double Team::get_netQuotient() const{
	double pointsFor;
	double pointsAgainst;
	for(auto i:pointsScoredAgainst) // points scored against all opponents
		pointsFor += i;
	for(auto j:pointsAllowedAgainst) // points allowed against all opponents
		pointsAgainst += j;
	return pointsFor / pointsAgainst;
}

double Team::get_netQuotient(int opponent) const{
	return (double)pointsScoredAgainst[opponent] /
			(double)pointsAllowedAgainst[opponent];
}

double Team::get_netQuotient(string& division) const{
	assert(division == "east" || division == "west");
	double pointsFor;
	double pointsAgainst;
	if(division == "east"){
		for(int i = 5; i <= 8; i++){ // for all teams in east division
			pointsFor += pointsScoredAgainst[i];
			pointsAgainst += pointsAllowedAgainst[i];
		}
	}
	else if(division == "west"){
		for(int i = 0; i <=5; i++){ // for all teams in west division
			pointsFor += pointsScoredAgainst[i];
			pointsAgainst += pointsAllowedAgainst[i];
		}
	}
	return pointsFor/pointsAgainst;
}
