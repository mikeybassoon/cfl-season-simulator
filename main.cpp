/*
  	main.cpp
 	
 */

#include "league_classes.h"
#include "initialize.h"
#include "simulation.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

int main(){
	cout << "CFL Playoff Calculator" << endl;

	srand(time(0)); // set random number seed
	assignTeamNames(); // set names for all teams in league array
	cout << "Reading schedule . . . " << endl;
	readSchedule(); // read all game details into schedule array, update team statistics
	cout << "Beginning simulation . . ." << endl;

	for(int i = 0; i < NUMBER_OF_SIMULATIONS; i++){
		copySchedule(); // copy season schedule to a new array

		copyLeague(); // copy league array to new array

		simulateSeason(); // simulate all unplayed games in season

		crunchSeasonResults();// record results

	}

	cout << "100%! Simulation completed, printing report . . ." << endl;

	// print summary of simulation
	print_report();

	cout << "Report saved as seasonSchedule.txt. Ending program." << endl;

	return 0;
}
