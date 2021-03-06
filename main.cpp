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

void runSimulation(int& weeksPlayed){

	cout << "Beginning simulation . . ." << endl;

	for(int i = 0; i < NUMBER_OF_SIMULATIONS; i++){
		copySchedule(); // copy season schedule to a new array

		copyLeague(); // copy league array to new array

		simulateSeason(weeksPlayed); // simulate all unplayed games in season

		crunchSeasonResults();// record results

	}

	cout << "Simulation completed, printing report . . ." << endl;

	// print summary of simulation
	print_report();

	cout << "Report saved as seasonSchedule.txt. Returning to main menu." << endl;
}

int main(){
	int weeksPlayed = 0;


	cout << "CFL Playoff Calculator" << endl;
	srand(time(0)); // set random number seed
	assignTeamNames(); // set names for all teams in league array
	cout << "Reading schedule . . . " << endl;
	readSchedule(weeksPlayed); // read all game details into schedule array, update team statistics

	// run main menu
	int selection = -1;

	while(selection != 9){
		cout << endl << "Main Menu" << endl;
		cout << "1. Run Simulation" << endl;
		cout << "9. End Program" << endl;
		cout << "Please enter a selection: ";
		cin >> selection;
		if(selection == 1)
			runSimulation(weeksPlayed);
		else if(selection == 9)
			break;
		else
			cout << "Invalid selection, please try again." << endl;
	}
	cout << "Ending program." << endl;
	return 0;
}
