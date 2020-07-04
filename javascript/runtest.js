// unit tests for back-end code

// import code being tested
var leagueFile = require('./server/league.js');

console.log('Initiating tests...');

testResults = new Array(); // Boolean array of individual test results


// 1
// Test that declaration of league object works

var testLeague = leagueFile.League;

if(typeof testLeague === undefined){
    testResults.push(false);
}
else{
    testResults.push(true);
}

// print results
console.log('\nTEST\tRESULT');

for(i = 0; i<testResults.length; i++){
    console.log(`${i+1}\t${testResults[i]}`);
}
