/*
 * initialize.h
 *
 *  Created on: Aug 5, 2019
 *      Author: michaelmacaulay
 */

#ifndef INITIALIZE_H_
#define INITIALIZE_H_

#include "league_classes.h"
#include <fstream>

using namespace std;


/*	void assignTeamNames()
 * 	Purpose: sets name for all instances of Team
 * 	Preconditions:
 * 		<1> teams must appear in same hardcoded order in which they appear in the array
 * 	Parameters: n/a
 * 	No return
 * 	Side effect:
 * 		<1> for each instance of Team in array, team name set
 */
void assignTeamNames();

/* void readSchedule()
 * Purpose: reads season schedule text file, saves to schedule array
 * Preconditions:
 * 	<1> Input file properly formatted
 * 	<2> seasonSchedule 2-D array initialized
 * 	<3> league array initialized
 * Parameters: n/a
 * No return
 * Side effect:
 * 	<1> seasonSchedule array filled with scheduled game details
 * 	<2> league array updated with information from games previously played
 */
void readSchedule();

/* int teamNameToID()
 * Purpose: takes team nickname (string), returns teamID (int)
 * Preconditions:
 * 	<1> nickname is correctly spelled
 * Parameters:
 * 	<1> string - team nickname
 * Returns teamID for that team
 */
int teamNameToID(const string&);


#endif /* INITIALIZE_H_ */
