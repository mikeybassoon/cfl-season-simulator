# cfl-season-simulator
Simulates Canadian Football League regular season, identifies likely post-season ranking order

LICENSE:
  (C)2019 Michael Macaulay. No commercial use of this program is permitted without written permission from the creator. Permission is granted to use and modify this program for personal or educational purposes.

PURPOSE: 
  The CFL Season Simulator simulates the Canadian Football League regular season, taking into account the results of any games already played. Once the season has been simulated, the playoff seeding of each team is determined. The full season is simulated a significant number of times (exact number defined in the header file) with each team's playoff seeding results being tracked. A report is generated indicating the relative likelihood of each playoff seed result for each team in the league.

SIMULATION DETAILS:
  The full season schedule, including results of games already played, is read from a text file. For each game not yet played, a score between 0 and 66 is assigned to each team. No home field advantage is assigned and teams' historical records are not taken into account. At the conclusion of each season simulation, playoff seeding for the East and West Divisions is determined according to the CFL's official tie-breaking procedure (available on the CFL website and from CFLdb).
