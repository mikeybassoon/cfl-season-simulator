# cfl-season-simulator
Simulates Canadian Football League regular season, identifies likely post-season ranking order

LICENSE:
  (C)2019 Michael Macaulay. No commercial use of this program is permitted without written permission from the creator. Permission is granted to use and modify this program for personal or educational purposes.
  
LATEST SEASON PREDICTIONS:
  To see the results of the last simulation run, check out "report.txt"!

PURPOSE: 
  The CFL Season Simulator simulates the Canadian Football League regular season, taking into account the results of any games already played. Once the season has been simulated, the playoff seeding of each team is determined, including whether the "crossover rule" is in effect (fourth place team in one division takes the third place seed in the opposite division). The full season is simulated a significant number of times with each team's playoff seeding results being tracked over the repeated simulations. A report is generated indicating the relative likelihood of each playoff seed result for each team in the league.

SIMULATION DETAILS:
  The full season schedule, including results of games already played, is read from a text file. For each game not yet played, a score between 0 and 66 is assigned to each team. No home field advantage is assigned and teams' historical records are not taken into account. At the conclusion of each season simulation, playoff seeding for the East and West Divisions is determined according to the CFL's official tie-breaking procedure (available on the CFL website and from CFLdb).
  The simulator has been tested on runs of up to 10,000,000 simulations.
