/*
  	main.cpp
 	
 */

#include "league_classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){

	TEAM riders, esks, stamps, bombers, lions, redblacks, argos, als, ticats;
	TEAM league[] = {riders, esks, stamps, bombers, lions, redblacks, argos, als, ticats}; // creates an array of teams
	// note that the west division is indices 0-4, east division is indices 5-8

	GAME seasonSchedule[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK];
	readSeasonSchedule(league, seasonSchedule); // read all season statistics and schedule into memory

	// call the earliest clinch week function
	//	- idea: generate a two-dimensional array of remaining games to be played
	//		- work out a logic to which games you assign wins and losses first
	// call the earliest playoff miss function


	simulateSeason(league, seasonSchedule); // call season simulation function

	return 0;
}




