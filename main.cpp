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

ofstream log; // logs progress through the program

int main(){

	log.open("runlog.txt");
	if(!log) cerr << "ERROR: unable to open runlog.txt!" << endl;
	log << "CFL Playoff Calculator Run Log" << endl;
	log << "Number of simulations run: " << NUMBER_OF_SIMULATIONS << endl;

	cout << "CFL Playoff Calculator" << endl;

	srand(time(0)); // set random number seed
	log << "Random number seed set to " << time(0) << endl;

	log << "Calling assignTeamNames() from main()" << endl;
	assignTeamNames(); // set names for all teams in league array
	log << "assignTeamNames() completed, returning to main()" << endl;

	cout << "Reading schedule . . . " << endl;
	log << "calling readSchedule() from main()" << endl;
	readSchedule(); // read all game details into schedule array, update team statistics
	log << "readSchedule() completed, returning to main()" << endl;

	log << endl << "TEAM STATISTICS PRIOR TO SIMULATION" << endl;
	log << "Name/Wins/Losses/Ties/Games Played/Points Scored/Points Allowed/ID" << endl << endl;
	for(int i = 0; i < NUMBER_OF_TEAMS; i++){
		Team thisTeam = league[i];
		log << thisTeam.get_name() << "\t" << thisTeam.get_wins() << "\t" << thisTeam.get_losses()
				<< "\t" << thisTeam.get_ties() << "\t" << thisTeam.get_pointsScored()
				<< "\t" << thisTeam.get_pointsAllowed() << "\t" << thisTeam.get_teamID() << endl;
	}
	log << endl << "Beginning simulation process" << endl;

	cout << "Beginning simulation . . ." << endl;

	for(int i = 0; i < NUMBER_OF_SIMULATIONS; i++){
		if((i * 100) / NUMBER_OF_SIMULATIONS == 20) cout << "20% . . ." << endl;
		else if((i * 100) / NUMBER_OF_SIMULATIONS == 40) cout << "40% . . ." << endl;
		else if((i * 100) / NUMBER_OF_SIMULATIONS == 60) cout << "60% . . ." << endl;
		else if((i * 100) / NUMBER_OF_SIMULATIONS == 80) cout << "80% . . ." << endl;

		log << "Calling copySchedule() from main()" << endl;
		copySchedule(); // copy season schedule to a new array
		log << "copySchedule() executed successfully, returning to main()" << endl;

		log << "Calling copyLeague() from main()" << endl;
		copyLeague(); // copy league array to new array
		log << "copyLeague() executed successfully, returning to main()" << endl;

		log << "Calling simulateSeason() from main()" << endl;
		simulateSeason(); // simulate all unplayed games in season
		log << "simulateSeason() executed successfully, returning to main()" << endl;

		log << "Calling crunchSeasonResults() from main()" << endl;
		crunchSeasonResults();// record results
		log << "crunchSeasonResults() executed successfully, returning to main()" << endl;

	}

	cout << "100%! Simulation completed, printing report . . ." << endl;

	log << "Calling print_report() from main()" << endl;

	// print summary of simulation
	print_report();

	log << "print_report() executed successfully, returning to main()" << endl;

	cout << "Report saved as seasonSchedule.txt. Ending program." << endl;

	log.close();
	return 0;
}




