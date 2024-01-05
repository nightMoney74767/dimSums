#pragma once
#include <iostream>
using namespace std;

/**
*	This class stores each Dim Sum as objects and is declared within this header file
*/
class DimSumClass {
private:
	/**
	*	Constructor which stores each clue and its respective value
	*/
	string clue; /**< Stores each Dim Sum clue */
	int value; /**< Stores each Dim Sum value */
public:
	string getClue() { return clue; } /**< Retrieves the clue pertaining to a Dim Sum */
	int getValue() { return value; } /**< Retrieves the value pertaining to a Dim Sum */
	string setClue(string c) { return clue = c; } /**< Sets the clue pertaining to a Dim Sum */
	int setValue(int v) { return value = v; } /**< Sets the value pertaining to a Dim Sum */
};