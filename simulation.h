/*
 * simulation.h
 *
 *  Created on: Aug 5, 2019
 *      Author: michaelmacaulay
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "league_classes.h"
#include "read_stats.h"
#include "initialize.h"

#include <iostream>

using namespace std;

/*  void copySchedule()
 * 	Purpose: copies a two-dimensional season schedule array so that a simulation will not affect original data
 * 	Preconditions: array must be Game[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]
 * 	Parameters:
 * 		<1> Game[][] - Target array to be used in simulation
 * 		<2> Game[][] - Original (source) array
 * 	Returns true if successful
 * 	Side effect: target array's contents changed, now identical to source array
 */
bool copySchedule(Game[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK], const Game[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]);

#endif /* SIMULATION_H_ */
