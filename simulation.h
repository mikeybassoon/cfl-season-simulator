/*
 * simulation.h
 *
 *  Created on: Aug. 20, 2019
 *      Author: michaelmacaulay
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

void copySchedule(); // copies 2-D season scheduled array so simulation will not modify original data
void copyLeague(); // copies league array so simulation will not modify original data
void simulateSeason(); // simulates all unplayed games in season
void crunchSeasonResults(); // determines final season ranking, updates team stats in original league array
/* int findWinner()
 * Purpose: finds highest-ranked team (that has not yet been ranked) in a specific division
 * Parameters:
 * 	<1> int - lower bound of indices to be searched
 * 	<2> int - upper bound of indices to be searched
 * Returns: int - index in league array of winner
 * Side effect: ranked set to true for winner
 */
int findWinner(const int, const int);

/* int findWinner()
 * Purpose: finds highest-ranked team in an array or vector
 * Parameters:
 * 	<1> int - pointer to an array
 * Returns: int - index in league array of winner
 * Side effect: ranked set to true for winner
 */
int findWinner(const int*);



#endif /* SIMULATION_H_ */
