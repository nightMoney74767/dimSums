#pragma once
#include <iostream>
using namespace std;
using namespace boost;

/**
*	This class stores information pertaining to a user's game session as ojbects
*/
class LeaderboardClass {
private:
	/**
	*	Constructor which stores the user's name, score and the date in which the game was played
	*/
	string name; /**< Username of player */
	int score; /**< Number of points gained in a game session */
	string date; /**< The date in which a game session was played */
public:
	LeaderboardClass(string n, int s, string d) :name(n), score(s), date(d) {}
	LeaderboardClass() {}
	/**
	*	Friend class - allows for serialisation
	*/
	friend class serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& name;
		ar& score;
		ar& date;
	}
	string getName() { return name; } /**< Retrieves username */
	int getScore() { return score; } /**< Retrieves number of points gained in a game session */
	string getDate() { return date; } /**< Retrieves the date in which a game session was played */
	string setName(string n) { return name = n; } /**< Sets username */
	int setScore(int s) { return score = s; } /**< Sets number of points gained in a game session */
	string setDate(string d) { return date = d; } /**< Sets the date in which a game session was played */
	/**
	*	Sort the leaderboard by score
	* 
	*	Adapted from C++ Reference (coder777, 2016)
	*/
	bool operator<(const LeaderboardClass& leaderboardClass) const {
		return (score < leaderboardClass.score);
	}
	/**
	*	End of adapted code
	*/
};