/*
  	main.cpp
 	
 */

#include "league_classes.h"
#include "initialize.h"
#include "simulation.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){

	srand(time(0)); // set random number seed

	assignTeamNames(); // set names for all teams in league array

	readSchedule(); // read all game details into schedule array, update team statistics

	for(int i = 0; i < NUMBER_OF_SIMULATIONS; i++){
		copySchedule(); // copy season schedule to a new array
		copyLeague(); // copy league array to new array
		simulateSeason(); // simulate all unplayed games in season
		crunchSeasonResults();// record results
	}


	// print report

	return 0;
}




