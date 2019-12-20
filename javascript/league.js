/* league.js
	Contains class definitions for the league as a whole, and for teams within it
*/

const WEEKS_IN_SEASON = 21;
const GAMES_IN_SEASON = 18;

// class definition for CFL
const CFL = {
	team: [ 'CGY', 'EDM', 'SSK', 'BC', 'WPG', 'HAM', 'OTT', 'TOR', 'MTL' ],
	schedule: [] // each unit in the schedule is an array of games for a particular week	
};

// print out contents of team array to test
