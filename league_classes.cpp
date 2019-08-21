/*
 * league_classes.cpp
 *
 *  Created on: Jul. 30, 2019
 *      Author: michael
 */

#include <iostream>
#include "league_classes.h"
#include <cassert>
#include <cctype>

using namespace std;


Team::Team(){
	teamID = -1;
	// initialize all season statistics to zero
	for(auto i : winsAgainst) i = 0;
	for(auto i : lossesAgainst) i = 0;
	for(auto i : tiesAgainst) i = 0;
	gamesPlayed = 0;
	for(auto i : pointsScoredAgainst) i = 0;
	for(auto i : pointsAllowedAgainst) i = 0;
	firstPlaceFinishes = secondPlaceFinishes = thirdPlaceFinishes = crossovers = timesMissedPlayoffs = 0;
	isRanked = false;
}

Team::~Team(){}

string Team::get_name(){
	return name;
}

string Team::get_division(){
	return division;
}

int Team::get_playoffPoints() const{
	return get_wins() * 2 + get_ties();
}

int Team::get_teamID(){
	return teamID;
}

bool Team::is_ranked(){
	if(isRanked == true)
		return true;
	else return false;
}

void Team::set_name(const string& teamName){
	name = teamName;
}

void Team::set_division(const string& divisionName){
	string lowercaseName;
	for(int i = 0; i < divisionName.size(); i++) // for each char in name
		lowercaseName[i] = tolower(divisionName[i]); // convert to lowercase
	if(lowercaseName != "west" and lowercaseName != "east"){ // invalid division name?
		cerr << "ERROR: invalid division name for team: " << name << endl;
	}
	division = lowercaseName; // set division name
}

void Team::set_teamID(int id){
	teamID = id;
}

void Team::set_ranked(bool newValue){
	assert(newValue == true or newValue == false);
	isRanked = newValue;
}

void Team::add_winAgainst(int opponentID){
	winsAgainst[opponentID]++;
}

void Team::add_lossAgainst(int opponentID){
	lossesAgainst[opponentID]++;
}

void Team::add_tieAgainst(int opponentID){
	tiesAgainst[opponentID]++;
}

void Team::add_gamePlayed(){
	gamesPlayed++;
}

void Team::add_pointsScoredAgainst(int opponentID, int points){
	pointsScoredAgainst[opponentID] += points;
}

void Team::add_pointsAllowedAgainst(int opponentID, int points){
	pointsAllowedAgainst[opponentID] += points;
}

void Team::add_firstPlace(){
	firstPlaceFinishes++;
}

void Team::add_secondPlace(){
	secondPlaceFinishes++;
}

void Team::add_thirdPlace(){
	thirdPlaceFinishes++;
}

void Team::add_crossover(){
	crossovers++;
}

void Team::add_missedPlayoffs(){
	timesMissedPlayoffs++;
}

int Team::get_ties() const{
	int totalTies = 0;
	for(auto i:tiesAgainst)
		totalTies += i;
	return totalTies;
}

int Team::get_wins() const{
	int totalWins = 0;
	for(auto i:winsAgainst)
		totalWins += i;
	return totalWins;
}

int Team::get_winsAgainst(int team) const{
	return winsAgainst[team];
}

int Team::get_lossesAgainst(int team) const{
	return lossesAgainst[team];
}

int Team::get_pointsScoredAgainst(int team) const{
	return pointsScoredAgainst[team];
}

int Team::get_pointsAllowedAgainst(int team) const{
	return pointsAllowedAgainst[team];
}

int Team::get_winPercentage(int opponentID) const{
	int winPct = (winsAgainst[opponentID] * 1000) /
			(lossesAgainst[opponentID] + tiesAgainst[opponentID]);
	return winPct;
}

int Team::get_winPercentage(string& division) const{
	assert(division == "east" || division == "west");
	int divisionWins = 0;
	int divisionLosses = 0;
	int divisionTies = 0;
	if(division == "west"){
		for(int x = 0; x <= 4; x++){
			divisionWins += winsAgainst[x];
			divisionLosses += lossesAgainst[x];
			divisionTies += tiesAgainst[x];
		}
	}
	else if(division == "east"){
		for(int x = 5; x <= 8; x++){
			divisionWins += winsAgainst[x];
			divisionLosses += lossesAgainst[x];
			divisionTies += tiesAgainst[x];
		}
	}
	else cerr << "ERROR: invalid division input in get_winPercentage" << endl;
	int divisionPct = (divisionWins * 1000) /
			(divisionLosses + divisionTies);
	return divisionPct;
}

int Team::get_netAggregate() const{
	int netAgg = 0;
	for(auto i:pointsScoredAgainst)
		netAgg += i;
	for(auto j:pointsAllowedAgainst)
		netAgg -= j;
	return netAgg;
}

int Team::get_netAggregate(int opponentID) const{
	int netAgg = pointsScoredAgainst[opponentID] - pointsAllowedAgainst[opponentID];
	return netAgg;
}

int Team::get_netAggregate(string& division) const{
	assert(division == "east" || division == "west");
	int netAgg = 0;
	if(division == "east"){
		for(int i = 5; i <= 8; i++){
			netAgg += pointsScoredAgainst[i];
			netAgg -= pointsAllowedAgainst[i];
		}
	}
	else if(division == "west"){
		for(int i = 0; i <= 4; i++){
			netAgg += pointsScoredAgainst[i];
			netAgg -= pointsAllowedAgainst[i];
		}
	}
	return netAgg;
}

int Team::get_netQuotient() const{
	int pointsFor = 0;
	int pointsAgainst = 0;
	for(auto i:pointsScoredAgainst) // points scored against all opponents
		pointsFor += i;
	for(auto j:pointsAllowedAgainst) // points allowed against all opponents
		pointsAgainst += j;
	return (1000 * pointsFor) / pointsAgainst;
}

int Team::get_netQuotient(int opponent) const{
	return (1000 * pointsScoredAgainst[opponent]) /
			pointsAllowedAgainst[opponent];
}

int Team::get_netQuotient(string& division) const{
	int pointsFor = 0;
	int pointsAgainst = 0;
	if(division == "east"){
		for(int i = 5; i <= 8; i++){ // for all teams in east division
			pointsFor += pointsScoredAgainst[i];
			pointsAgainst += pointsAllowedAgainst[i];
		}
	}
	else if(division == "west"){
		for(int i = 0; i <=5; i++){ // for all teams in west division
			pointsFor += pointsScoredAgainst[i];
			pointsAgainst += pointsAllowedAgainst[i];
		}
	}
	return (1000 * pointsFor) / pointsAgainst;
}

void Team::operator=(const Team& original){
	name = original.name;
	division = original.division;
	teamID = original.teamID;
	for(int i = 0; i < NUMBER_OF_TEAMS; i++){
		winsAgainst[i] = original.winsAgainst[i];
		lossesAgainst[i] = original.lossesAgainst[i];
		tiesAgainst[i] = original.tiesAgainst[i];
		pointsScoredAgainst[i] = original.pointsScoredAgainst[i];
		pointsAllowedAgainst[i] = original.pointsAllowedAgainst[i];
	}
	gamesPlayed = original.gamesPlayed;
	firstPlaceFinishes = original.firstPlaceFinishes;
	secondPlaceFinishes = original.secondPlaceFinishes;
	thirdPlaceFinishes = original.thirdPlaceFinishes;
	crossovers = original.crossovers;
	timesMissedPlayoffs = original.timesMissedPlayoffs;
	isRanked = original.isRanked;
}

Game::Game(){
	scheduled = false;
	completed = false;
	homeTeamScore = 0;
	awayTeamScore = 0;
	homeTeamID = -1;
	awayTeamID = -1;
	week = -1;
}

Game::~Game(){

}

bool Game::is_scheduled(){
	return scheduled;
}

bool Game::was_played(){
	return completed;
}

int Game::homeTeam(){
	return homeTeamID;
}

int Game::awayTeam(){
	return awayTeamID;
}

void Game::set_homeTeam(int homeID){
	homeTeamID = homeID;
}

void Game::set_awayTeam(int awayID){
	awayTeamID = awayID;
}

void Game::set_scheduled(bool status){
	scheduled = status;
}

void Game::set_hasBeenPlayed(bool status){
	completed = status;
}

void Game::set_homeTeamScore(int score){
	homeTeamScore = score;
}

void Game::set_awayTeamScore(int score){
	awayTeamScore = score;
}

void Game::set_week(int gameWeek){
	week = gameWeek;
}

void Game::simulate_game(){
	homeTeamScore = rand() % 67; // generate score in [0, 66]
	awayTeamScore = rand() % 67; // generate score in [0, 66]
	completed = true;

	// increment games played counters
	sim_league[homeTeamID].add_gamePlayed();
	sim_league[awayTeamID].add_gamePlayed();

	// update win/loss/tie statistics
	if(homeTeamScore > awayTeamScore){ // home team wins?
		sim_league[homeTeamID].add_winAgainst(awayTeamID);
		sim_league[awayTeamID].add_lossAgainst(homeTeamID);
	}
	else if(awayTeamScore > homeTeamScore){ // away team wins?
		sim_league[awayTeamID].add_winAgainst(homeTeamID);
		sim_league[homeTeamID].add_lossAgainst(awayTeamID);
	}
	else{ // tie?
		sim_league[homeTeamID].add_tieAgainst(awayTeamID);
		sim_league[awayTeamID].add_tieAgainst(homeTeamID);
	}

	// update point statistics
	sim_league[homeTeamID].add_pointsScoredAgainst(awayTeamID, homeTeamScore);
	sim_league[homeTeamID].add_pointsAllowedAgainst(awayTeamID, awayTeamScore);
	sim_league[awayTeamID].add_pointsScoredAgainst(homeTeamID, awayTeamScore);
	sim_league[awayTeamID].add_pointsAllowedAgainst(homeTeamID, homeTeamScore);

}

void Game::operator= (const Game& original){
	homeTeamID = original.homeTeamID;
	awayTeamID = original.awayTeamID;
	scheduled = original.scheduled;
	completed = original.completed;
	homeTeamScore = original.homeTeamScore;
	awayTeamScore = original.awayTeamScore;
	week = original.week;
}


Team league[9]; // array of teams in the league
Team sim_league[9]; // copy of league array for simulations
Game seasonSchedule[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]; // schedule array
Game sim_seasonSchedule[NUMBER_OF_WEEKS][MAX_GAMES_PER_WEEK]; // copy of schedule for simulations
