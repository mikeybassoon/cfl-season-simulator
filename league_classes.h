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
protected:
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
	Team(); // default constructor
	~Team(); // destructor
	string get_name();
	string get_division();
	int get_teamID();
	bool is_ranked(); // true if ranked, false if not yet ranked
	void set_name(const string&);
	void set_division(const string&); // parameter must be "east" or "west"
	void set_teamID(int);
	void set_ranked(bool);

	// functions to adjust statistics
	void add_winAgainst(int); // parameter: teamID of opponent
	void add_lossAgainst(int); // parameter: opponent ID
	void add_tieAgainst(int); // parameter: opponent ID
	void add_gamePlayed(); // increment gamesPlayed
	void add_pointsScoredAgainst(int, int); // parameters: opponent ID, # of points
	void add_pointsAllowedAgainst(int, int); // parameters: opponent ID, # of points
	void add_firstPlace();
	void add_secondPlace();
	void add_thirdPlace();
	void add_crossover();
	void add_missedPlayoffs();

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
};

class Game{
protected:
	int homeTeamID;
	int awayTeamID;
	bool scheduled; // game scheduled at this time?
	bool completed; // game played already in simulation?
	int homeTeamScore;
	int awayTeamScore;
public:
	Game(); // default constructor - game unscheduled, not completed, no score
	~Game(); // destructor
	bool is_scheduled(); // return true if game scheduled in this time slot
	bool was_played(); // return true if game already played
	int homeTeam(); // return home team ID
	int awayTeam(); // return home team ID
	void set_homeTeam(int); // parameter: home team ID
	void set_awayTeam(int); // parameter: away team ID
	void set_scheduled(bool);
	void set_hasBeenPlayed(bool);
	void set_homeTeamScore(int);
	void set_awayTeamScore(int);
	void simulate_game(); // generates scores for both teams [0, 66] and updates statistics
};

/*	Order of teams in the league array:
 *
 * 	WEST DIVISION
 * 	<0> Saskatchewan Roughriders
 * 	<1> Edmonton Eskimos
 * 	<2> Calgary Stampeders
 * 	<3> Winnipeg Blue Bombers
 * 	<4> BC Lions
 *
 * 	EAST DIVISION
 * 	<5> Ottawa Redblacks
 * 	<6> Toronto Argonauts
 * 	<7> Montreal Alouettes
 * 	<8> Hamilton Tiger Cats
 */
extern Team league[]; // array of teams in the league
extern Team sim_league[]; // copy of league for simulations
extern Game seasonSchedule[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]; // season schedule
extern Game sim_seasonSchedule[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]; // copy of schedule for simulations

#endif /* LEAGUE_CLASSES_H_ */

