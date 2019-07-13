/*
 * header.h
 *
 *  Created on: Jul 9, 2019
 *      Author: michaelmacaulay
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#define NUMBER_OF_TEAMS 9 // teams in CFL
#define MAX_GAMES_PER_WEEK 4 // maximum number of games possible in any one week
#define NUMBER_OF_WEEKS 21 // weeks in season
#define NUMBER_OF_SIMULATIONS 100 // when season simulated, this constant determines how many times
									// the simulation will run
#define GAMES_PLAYED 18


#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

struct TEAM{
	// stats to date
	string teamName;
	string nickname;
	bool ranked;

	// season ranking statistics
	int playoffPoints;
	int pointsForCertainTeam[NUMBER_OF_TEAMS];
	int pointsAgainstCertainTeam[NUMBER_OF_TEAMS];
	int winsAgainstCertainTeam[NUMBER_OF_TEAMS];
	int gamesAgainstCertainTeam[NUMBER_OF_TEAMS];
	int pctWinsAgainstCertainTeam[NUMBER_OF_TEAMS];
	int netAggregateAgainstCertainTeam[NUMBER_OF_TEAMS];
	int netQuotientAgainstCertainTeam[NUMBER_OF_TEAMS];
	int totalWins;
	int winsInDivision;
	int gamesAgainstDivision;
	int pctWinsAgainstDivision;
	int pointsForInDivision;
	int pointsAgainstInDivision;
	int netAggregateAgainstDivision;
	int netQuotientAgainstDivision;
	int totalPointsFor;
	int totalPointsAgainst;
	int netAggregateAgainstLeague;
	int netQuotientAgainstLeague;

	// results after multiple season simulations - initialized in the season simulation function
	int firstPlaceFinishes, secondPlaceFinishes, thirdPlaceFinishes;
	int crossovers, timesMissedPlayoffs;
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


#endif /* INTERFACE_H_ */
