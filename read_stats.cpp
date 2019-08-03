/*
 * read_stats.cpp
 *
 *  Created on: Jul 9, 2019
 *      Author: michaelmacaulay
 */

#include "league_classes.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void assignTeamNames(TEAM league[]){
	league[0].teamName = "Saskatchewan Roughriders";
	league[1].teamName = "Edmonton Eskimos";
	league[2].teamName = "Calgary Stampeders";
	league[3].teamName = "Winnipeg Blue Bombers";
	league[4].teamName = "BC Lions";
	league[5].teamName = "Ottawa REDBLACKS";
	league[6].teamName = "Toronto Argonauts";
	league[7].teamName = "Montreal Alouettes";
	league[8].teamName = "Hamilton Tiger Cats";
}

void assignNicknames(TEAM league[]){
	league[0].nickname = "riders";
	league[1].nickname = "esks";
	league[2].nickname = "stamps";
	league[3].nickname = "bombers";
	league[4].nickname = "lions";
	league[5].nickname = "redblacks";
	league[6].nickname = "argos";
	league[7].nickname = "als";
	league[8].nickname = "ticats";
}
/* void getTeamId
 *
 * Purpose:	Takes a string shorthand for a team's name
 * 			Returns that team's int code, which can then be used to access the league array
 *
 */
int getTeamId(string teamName){
	int teamId = -1;

	if (teamName == "riders")teamId = 0;
	else if (teamName == "esks") teamId = 1;
	else if (teamName == "stamps") teamId = 2;
	else if (teamName == "bombers") teamId = 3;
	else if (teamName == "lions") teamId = 4;
	else if (teamName == "redblacks") teamId = 5;
	else if (teamName == "argos") teamId = 6;
	else if (teamName == "als") teamId = 7;
	else if (teamName == "ticats") teamId = 8;
	else cerr << "Invalid team name in seasonSchedule.txt!" << endl;
	assert(0 <= teamId && teamId <= 8);
	return teamId;
}

/* void readSeasonSchedule
 *
 * Purpose:
 *		Read information from seasonSchedule.txt to the array of teams and the future schedule array
 */
void readSeasonSchedule(TEAM league[], GAME seasonSchedule[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]){
	ifstream inputFile;
	string lastStringRead;

	inputFile.open("seasonSchedule.txt");
		assert(inputFile);

	assignTeamNames(league); // assigns formal name of each team to their respective record
	assignNicknames(league); // assigns nickname strings to each team

	// read detail of all games into schedule, whether or not those games have been played yet
	for(int i = 0; i < NUMBER_OF_WEEKS; i++){
		for(int j = 0; j < MAX_GAMES_PER_WEEK; j++){
			cin >> seasonSchedule[i][j].week;
			cin >> seasonSchedule[i][j].scheduled;
			cin >> seasonSchedule[i][j].completed;
			cin >> lastStringRead;
			seasonSchedule[i][j].homeTeam = league[getTeamId(lastStringRead)];
			cin >> seasonSchedule[i][j].homeScore;
			cin >> lastStringRead;
			seasonSchedule[i][j].awayTeam = league[getTeamId(lastStringRead)];
			cin >> seasonSchedule[i][j].awayScore;
		}
	}
	inputFile.close();
}
