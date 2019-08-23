/*
 * initialize.cpp
 *
 *  Created on: Aug 5, 2019
 *      Author: michaelmacaulay
 */


#include "initialize.h"
#include "league_classes.h"
#include "simulation.h"
#include <iostream>
#include <fstream>

using namespace std;

void assignTeamNames(){
	league[0].set_name("Saskatchewan Roughriders");
	league[1].set_name("Edmonton Eskimos");
	league[2].set_name("Calgary Stampeders");
	league[3].set_name("Winnipeg Blue Bombers");
	league[4].set_name("BC Lions");
	league[5].set_name("Ottawa REDBLACKS");
	league[6].set_name("Toronto Argonauts");
	league[7].set_name("Montreal Alouettes");
	league[8].set_name("Hamilton Tiger Cats");
	for(int i = 0; i < NUMBER_OF_TEAMS; i++){
		league[i].set_teamID(i);
	}
}

void readSchedule(){
	log << "Now in readSchedule()" << endl;
	ifstream file; // input file
	file.open("seasonSchedule.txt");
	if(!file) // failed to open input file?
		cerr << "ERROR: cannot open seasonSchedule.txt!" << endl;
	log << "seasonSchedule.txt opened successfully" << endl;
	file.ignore(256, '\n'); // skip first line of input file

	int week, homeScore, awayScore;
	bool scheduled, played;
	string homeTeam, awayTeam;

	log << "Scheduled details as read from file:" << endl;
	for(int x = 0; x < NUMBER_OF_WEEKS; x++){ // for each week in season
		log << endl << "Week " << x + 1 << endl << endl;
		for(int y = 0; y < MAX_GAMES_PER_WEEK; y++){ // for each game in week
			file >> week >> scheduled >> played >> homeTeam >> homeScore >> awayTeam >> awayScore; // read line from input file
			int homeTeamID = teamNameToID(homeTeam);
			int awayTeamID = teamNameToID(awayTeam);

			seasonSchedule[x][y].set_week(week);
			seasonSchedule[x][y].set_scheduled(scheduled);
			seasonSchedule[x][y].set_hasBeenPlayed(played);
			seasonSchedule[x][y].set_homeTeam(homeTeamID);
			seasonSchedule[x][y].set_homeTeamScore(homeScore);
			seasonSchedule[x][y].set_awayTeam(awayTeamID);
			seasonSchedule[x][y].set_awayTeamScore(awayScore);

			//update stats if the game has been played
			if(played){
				// increment games played stats
				league[homeTeamID].add_gamePlayed();
				league[awayTeamID].add_gamePlayed();
				// update home and away team point totals
				league[homeTeamID].add_pointsScoredAgainst(awayTeamID, homeScore);
				league[homeTeamID].add_pointsAllowedAgainst(awayTeamID, awayScore);
				league[awayTeamID].add_pointsScoredAgainst(homeTeamID, awayScore);
				league[awayTeamID].add_pointsAllowedAgainst(homeTeamID, homeScore);
				// update win/loss/tie statistics
				if(homeScore > awayScore){ // home team won?
					league[homeTeamID].add_winAgainst(awayTeamID);
					league[awayTeamID].add_lossAgainst(homeTeamID);
				}
				else if(awayScore > homeScore){ // away team won?
					league[awayTeamID].add_winAgainst(homeTeamID);
					league[homeTeamID].add_lossAgainst(awayTeamID);
				}
				else{ // game tied?
					league[awayTeamID].add_tieAgainst(homeTeamID);
					league[homeTeamID].add_tieAgainst(awayTeamID);
				}
			}

			if(seasonSchedule[x][y].was_played()){
				log << "Game " << y + 1 << ": Team " << seasonSchedule[x][y].awayTeam() << " "
						<< seasonSchedule[x][y].get_awayScore() << " @ Team " << seasonSchedule[x][y].homeTeam()
						<< " " << seasonSchedule[x][y].get_homeScore() << endl;
			}
			else if(seasonSchedule[x][y].is_scheduled()){
				log << "Game " << y + 1 << " (not yet played): Team " << seasonSchedule[x][y].awayTeam() << " @ Team "
						<< seasonSchedule[x][y].homeTeam() << endl;
			}
			else log << "Game " << y + 1 << " not scheduled" << endl;
		} // end read game from schedule
	} // end read week from schedule

	file.close();
}

int teamNameToID(const string& nickname){
	if(nickname == "riders") return 0;
	else if(nickname == "esks") return 1;
	else if(nickname == "stamps") return 2;
	else if(nickname == "bombers") return 3;
	else if(nickname == "lions") return 4;
	else if(nickname == "redblacks") return 5;
	else if(nickname == "argos") return 6;
	else if(nickname == "als") return 7;
	else if(nickname == "ticats") return 8;
	else return -1;
}
