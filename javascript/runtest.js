// unit tests for back-end code

// import code being tested
var leagueFile = require('./server/league.js');

console.log('Initiating tests...');

testResults = new Array(); // Boolean array of individual test results

let testLeague = leagueFile.League;

/*  Test 1

    Fails if testLeague has undefined type
*/

if(typeof testLeague === undefined){
    testResults.push(false);
}
else{
    testResults.push(true);
}

/*  Test 2

    Attempts to use the get/set functions of League to set the current season
    to an arbitrary year. Fails unless the get_season() method returns the
    same value that was set using the set_season() method.
*/

testLeague.set_season(2020);

if(testLeague.get_season === 2020){
    testResults.push(true);
}
else{
    testResults.push(false);
}



// print results
console.log('\nTEST\tRESULT');

for(i = 0; i<testResults.length; i++){
    console.log(`${i+1}\t${testResults[i]}`);
}
