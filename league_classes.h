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
	bool is_ranked(); // true if ranked, false if not yet ranked
	void set_name(string&);
	void set_ranked(bool);

	// playoff tiebreaker criteria
	int get_playoffPoints() const;
	int get_ties() const; // ties against all teams
	int get_wins() const; // wins against all teams
	int get_winPercentage(int) const; // returns win percentage against(teamID)
	int get_winPercentage(string&) const; // returns win percentage against ("division") <division must be "west" or "east">
	int get_netAggregate() const; // returns net aggregate of points against league
	int get_netAggregate(int) const; // returns net aggregate of points against (teamID)
	int get_netAggregate(string&) const; // returns net aggregate of points against ("division) <division must be "west" or "east">
	double get_netQuotient() const; // returns net quotient of points against league
	double get_netQuotient(int) const; // returns net quotient  of points against (teamID)
	double get_netQuotient(string&) const; // returns net quotient of points against ("division") <division must be "west" or "east">
	
	// require get functions for season ranking results, isRanked
	// require set functions for everything
};

class Game{
private:
	int homeTeamID;
	int awayTeamID;
	bool scheduled; // game scheduled at this time?
	bool completed; // game played already in simulation?

public:
	Game(); // default constructor (no actual game scheduled)
	Game(int, int); // schedules unplayed game between two teams
	Game(int, int, bool); // schedules game between two teams - completed if bool is true
	~Game(); // destructor
	bool is_scheduled(); // return true if game scheduled in this time slot
	bool hasBeenPlayed(); // return true if game already played
	int homeTeam(); // return home team ID
	int awayTeam(); // return home team ID
	bool set_homeTeam(int); // return true if successful
	bool set_awayTeam(int); // return true if successful
	bool set_scheduled(bool); // return true if successful
	bool set_hasBeenPlayed(bool); // return true if successful
};


// function prototypes to be moved to other files

void crunchGameStats(Team[], Game&);
void crunchSeasonStats(Team[], Game[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]);
void readSeasonSchedule(Team[], Game[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]);
void simulateGame(Game&);
void simulateSeason(Team[], Game[][MAX_GAMES_PER_WEEK]);
void simulateWeek(Team[], Game[]);
int getTeamId(string& const);
void CalculateWinPercentage(Team[]);
void CalculateTotals(Team[]);
void CalculateNetAggregate(Team[]);
void CalculateNetQuotient(Team[]);
void sortDivision(Team[], Team[], Team[]);
Team breakTie(Team, Team);





#endif /* LEAGUE_CLASSES_H_ */

