/*
 * simulation.h
 *
 *  Created on: Aug. 20, 2019
 *      Author: michaelmacaulay
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void copySchedule(); // copies 2-D season scheduled array so simulation will not modify original data
void copyLeague(); // copies league array so simulation will not modify original data
void simulateSeason(); // simulates all unplayed games in season
/* void crunchSeasonResults()
 * Purpose: determines final season rankings for a simulated season
 * Preconditions:
 * 	<1> All teams "ranked" status must be set to false
 * No parameters
 * No return
 * Side effect: team stats (number of times each final ranking received) updated in ORIGINAL league array
 */
void crunchSeasonResults();

/* int findWinner()
 * Purpose: finds highest ranked out of a set of team
 * Parameters:
 * 	<1> vector<int> - vector containing all teams being compared
 * Returns: int - index in league array of winner
 * Side effect: none
 */
int findWinner(vector<int>&);

/* Tiebreaker functions
 * The following applies to all of the following functions:
 *
 * Parameters:
 * 	<1> vector<int> containing all teams being compared
 * 		each team represented by an int (the team's index in league array)
 * Returns vector<int> containing winning team(s)
 */

// returns team(s) with most playoff points
vector<int> checkPlayoffPoints(vector<int>&);

// returns team(s) with highest win total against entire league
vector<int> checkTotalWins(vector<int>&);

// returns team(s) with highest win percentage against other teams in the vector
vector<int> checkWinPctAgainstTied(vector<int>&);

// returns team(s) with highest net aggregate points against other teams in the vector
vector<int> checkNetAggAgainstTied(vector<int>&);

// returns team(s) with highest net quotient points against other teams in vector
vector<int> checkNetQuotAgainstTied(vector<int>&);

// returns team(s) with highest win percentage against their division
vector<int> checkWinPctAgainstDiv(vector<int>&);

// returns team(s) with highest net aggregate points against their division
vector<int> checkNetAggAgainstDiv(vector<int>&);

// returns team(s) with highest net quotient points against their division
vector<int> checkNetQuotAgainstDiv(vector<int>&);

// returns team(s) with highest net aggregate points against entire league
vector<int> checkNetAggTotal(vector<int>&);

// returns team(s) with highest net quotient points against entire league
vector<int> checkNetQuotTotal(vector<int>&);

// returns randomly selected winner
int coinFlip(vector<int>&);

/* void print_report()
 * Purpose: prints final report following a season simulation
 * Side effect: generates output file "report.txt" with summaries of each team's performance
 */
void print_report();

extern ofstream log; // text file log of program runs

#endif /* SIMULATION_H_ */
