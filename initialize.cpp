/*
 * initialize.cpp
 *
 *  Created on: Aug 5, 2019
 *      Author: michaelmacaulay
 */


#include "initialize.h"
#include "league_classes.h"
#include <iostream>

using namespace std;

void assignTeamNames(Team* league){
	string teamName = "Saskatchewan Roughriders";
	league[0].set_name(teamName);
	teamName = "Edmonton Eskimos";
	league[1].set_name(teamName);
	teamName = "Calgary Stampeders";
	league[2].set_name(teamName);
	teamName = "Winnipeg Blue Bombers";
	league[3].set_name(teamName);
	teamName = "BC Lions";
	league[4].set_name(teamName);
	teamName = "Ottawa REDBLACKS";
	league[5].set_name(teamName);
	teamName = "Toronto Argonauts";
	league[6].set_name(teamName);
	teamName = "Montreal Alouettes";
	league[7].set_name(teamName);
	teamName = "Hamilton Tiger Cats";
	league[8].set_name(teamName);
}
