/* interface.js
  contains javascript code for web interface page (generally test functions for now)
  */

// object class constructor for team
function Team(name) {
  this.name: name,
  this.rank: 0,
  this.wins: 0,
  this.losses: 0,
  this.ties: 0,

  this.set_rank = function(int) {this.rank = newRank;};
};



// arrays holding teams ranked
var eastDivision = [];
var westDivision = [];
