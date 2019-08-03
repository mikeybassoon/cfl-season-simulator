/*
 * league_classes.h
 *
 *  Created on: Jul. 30, 2019
 *      Author: michael
 */

#ifndef LEAGUE_CLASSES_H_
#define LEAGUE_CLASSES_H_

#define NUMBER_OF_TEAMS 9

#include <iostream>
#include <string>

using namespace std;

class Team{
private:
	string name;
	string division; // "west" or "east"
	int teamID;
	// win/loss/tie records against each team
	// sorted by team ID
	int winsAgainst[NUMBER_OF_TEAMS];
	int lossesAgainst[NUMBER_OF_TEAMS];
	int tiesAgainst[NUMBER_OF_TEAMS];
	int gamesPlayed; // in whole season
	int pointsScoredAgainst[NUMBER_OF_TEAMS];
	int pointsAllowedAgainst[NUMBER_OF_TEAMS];
public:
	/*	Team
	 *
	 * 	Purpose: constructor
	 * 	Parameters:
	 * 		<1> string - team name
	 * 		<2> string - division
	 * 		<3> int - team id
	 *	Preconditions: division is either "west" or "east"
	 *		team id between 0 and LEAGUE_SIZE
	 */
	Team(string, string, int); // constructor
	~Team(); // destructor
	string get_name();
	string get_division();
	int get_teamID();

	// playoff tiebreaker criteria
	int get_playoffPoints() const;
	int get_ties() const;
	int get_wins() const; // wins against all teams
	int get_winPercentage(int) const; // returns win percentage against(teamID)
	int get_winPercentage(string&) const; // returns win percentage against ("division")
	int get_netAggregate() const; // returns net aggregate of points against league
	int get_netAggregate(int) const; // returns net aggregate of points against (teamID)
	int get_netAggregate(string&) const; // returns net aggregate of points against ("division)
	double get_netQuotient() const; // returns net quotient of points against league
	double get_netQuotient(int) const; // returns net quotient  of points against (teamID)
	double get_netQuotient(string&) const; // returns net quotient of points against (teamID)
};





#endif /* LEAGUE_CLASSES_H_ */

