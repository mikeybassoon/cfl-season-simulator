/*
 * read_stats.cpp
 *
 *  Created on: Jul 9, 2019
 *      Author: michaelmacaulay
 */

#include "league_classes.h"
#include "read_stats.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;




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
void readSeasonSchedule(Team league[], GAME seasonSchedule[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]){
	ifstream inputFile;
	string lastStringRead;

	inputFile.open("seasonSchedule.txt");
		assert(inputFile);

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
