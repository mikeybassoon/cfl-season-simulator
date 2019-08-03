/*
 * league_classes.h
 *
 *  Created on: Jul. 30, 2019
 *      Author: michael
 */

#ifndef LEAGUE_CLASSES_H_
#define LEAGUE_CLASSES_H_

#define NUMBER_OF_TEAMS 9
#define MAX_GAMES_PER_WEEK 4 // maximum number of games possible in any one week
#define NUMBER_OF_WEEKS 21 // weeks in season
#define NUMBER_OF_SIMULATIONS 100 // number of simulations to run
#define GAMES_PLAYED 18

#include <iostream>
#include <string>

using namespace std;

class Team{
private:
	string name;
	string division; // "west" or "east"
	int teamID;
	int winsAgainst[NUMBER_OF_TEAMS]; // wins against specific teams
	int lossesAgainst[NUMBER_OF_TEAMS]; // losses against specific teams
	int tiesAgainst[NUMBER_OF_TEAMS]; // ties against specific teams
	int gamesPlayed; // in whole season
	int pointsScoredAgainst[NUMBER_OF_TEAMS]; // points scored against specific teams
	int pointsAllowedAgainst[NUMBER_OF_TEAMS]; // points allowed against specific teams
	int firstPlaceFinishes, secondPlaceFinishes, thirdPlaceFinishes, 
		crossovers, timesMissedPlayoffs; // how many times has team had each final ranking result?
	bool isRanked; // has team been assigned a final ranking for the season?
public:
	/*	Team constructor
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
	
	// require get functions for season ranking results, isRanked
	// require set functions for everything
};

struct GAME{
	bool scheduled;
	bool completed;
	TEAM homeTeam;
	TEAM awayTeam;
	int week; // the week the game is scheduled in
	int homeScore;
	int awayScore;
};

// function prototypes from previous version of code - some or all of these may be redundant

void assignTeamNames(TEAM[]);
void createOutputFile();
void crunchGameStats(TEAM[], GAME&);
void crunchSeasonStats(TEAM[], GAME[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]);
void copySchedule(GAME[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK], const GAME[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]);
void readSeasonSchedule(TEAM[], GAME[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]);
void simulateGame(GAME&);
void simulateSeason(TEAM[], GAME[][MAX_GAMES_PER_WEEK]);
void simulateWeek(TEAM[], GAME[]);
int getTeamId(string);
void CalculateWinPercentage(TEAM[]);
void CalculateTotals(TEAM[]);
void CalculateNetAggregate(TEAM[]);
void CalculateNetQuotient(TEAM[]);
void sortDivision(TEAM[], TEAM[], TEAM[]);
TEAM breakTie(TEAM, TEAM);





#endif /* LEAGUE_CLASSES_H_ */

