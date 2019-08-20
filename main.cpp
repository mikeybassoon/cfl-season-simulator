/*
  	main.cpp
 	
 */

#include "league_classes.h"
#include "initialize.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){

	srand(time(0)); // set random number seed

	assignTeamNames(league); // declare formal names for all teams

	// read the season schedule file and initialize game values accordingly
		// simultaneously update team statistic values from schedule

	for(int i = 0; i < NUMBER_OF_SIMULATIONS; i++){
		// copy season schedule to a new array
		// simulate season
		// record results
	}


	// print report

	return 0;
}




