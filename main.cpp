/*
  	main.cpp
 	
 */

#include "league_classes.h"
#include "initialize.h"
#include "read_stats.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){

	Team riders, esks, stamps, bombers, lions, redblacks, argos, als, ticats;
	Team league[] = {riders, esks, stamps, bombers, lions, redblacks, argos, als, ticats};

	assignTeamNames(league); // declare formal names for all teams

	Game seasonSchedule[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]; // declare array to hold season schedule

	// read the season schedule file and initialize game values accordingly

	for(int i = 0; i < NUMBER_OF_SIMULATIONS; i++){
		// copy season schedule to a new array
		// simulate season
		// record results
	}


	// print report

	return 0;
}




