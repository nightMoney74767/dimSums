/**
*	Header files for this project
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <random>
#include <string>
/**
*	Header files for Boost
*/
#include <boost/serialization/list.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/asio.hpp>
/**
*	Dates and times - adapted from C++ Reference (Corpus, 2008)
*/
#include <time.h>
/**
*	End of adapted code
*/
/**
*	Get DimSumClass and LeaderboardClass object definitions from header files
*/
#include "DimSumServer.h"
#include "LeaderboardServer.h"
/**
*	Namespaces for standard library and Boost
*/
using namespace std;
using namespace boost;
using asio::ip::tcp;

vector<DimSumClass> getDimSums(vector<string>& dimSums) {
	/**
	*	This function stores all Dim Sums in a vector using the class
	* 
	*	In the text file, clues appear first while the values follow
	*	
	*	Vectors with objects created with the guidance of C++ Reference (nonzenze, 2009)
	*	@param dimSums as vector of strings - vector of Dim Sums loaded from Boost as strings
	*	@return dimSumClassVector as vector of DimSumClass objects - vector of DimSums represented as objects under the DimSumClass
	* 
	*	Time complexity:
	*	-	the code in this function occurs n times (depending on how many Dim Sums need to be parsed into objects)
	*	-	this leads to the linear time complexity or O(n)
	*/
	vector<DimSumClass> dimSumClassVector;
	for (int i = 0; i < dimSums.size(); i += 2) {
		DimSumClass currentInstance;
		/**
		*	Set the clue of the Dim Sum as a string
		*/
		currentInstance.setClue(dimSums[i]);
		int j = i + 1;
		/**
		*	Set the value of the Dim Sum as an integer using stoi. Adapted from C++ Reference (std::stoi, std::stol, std::stoll, 2021)
		*/
		currentInstance.setValue(stoi(dimSums[j]));
		dimSumClassVector.push_back(currentInstance);
		/**
		*	End of adapted code
		*/
	}
	return dimSumClassVector;
}

vector<DimSumClass> chooseDimSums(vector<DimSumClass>& dimSumClassVector, int& numOfClues) {
	/**
	*	Randomly choose four, six or eight Dim Sums for each question depending on difficulty
	*	@param dimSumClassVector as vector of DimSumClass objects
	*	@param numOfClues as integer - this is set to 4, 6 or 8 depending on difficulty
	*	@return dimSumsToReturn as a vector of DimSumClass objects - a vector of chosen Dim Sums
	* 
	*	Time complexity:
	*	-	the code before the first for loop occurs once
	*	-	the first for loop executes n times (depending on how many Dim Sums were previously parsed as objects)
	*	-	the second for loop executed n times (a Dim Sum could be chosen multiple times until 4, 6, or 8 unique Dim Sums have been chosen (depending on difficulty))
	* 
	*	As a result, long execution times could occur as both loops occur at linear time or O(n). O notation of this function: 2(O(n)) + O(n)
	*/
	vector<DimSumClass> dimSumsToReturn(numOfClues);
	/**
	*	Create a vector at the same size as the clues vector to determine whether a clue has been used. Each index has a boolean value that is set to true when the associated clue is used
	*	This ensures that each clue can only appear once
	*/
	vector<bool> usedClues(dimSumClassVector.size());
	for (int i = 0; i < usedClues.size(); i++) {
		usedClues[i] = false;
	}
	/**
	*	Randomly choose an index of a Dim Sum using pseudo-random numbers. Code adapted from C++ Reference (Pseudo-random number generation, 2021)
	*/
	for (int i = 0; i < numOfClues; ) {
		random_device device;
		default_random_engine engine(device());
		uniform_int_distribution<int> uniformDistribution(0, (dimSumClassVector.size() - 1));
		int randomNumber = uniformDistribution(engine);
		/**
		*	End of adapted code
		*/

		/**
		*	If the Dim Sum has not been previously chosen, add it to the return vector
		*/
		if (!usedClues[randomNumber]) {
			dimSumsToReturn[i] = dimSumClassVector[randomNumber];
			usedClues[randomNumber] = true;
			i++;
		}
	}
	return dimSumsToReturn;
}

int outputDimSums(vector<DimSumClass>& chosenDimSums) {
	/**
	*	Output randomly chosen Dim Sums
	*	@param chosenDimSums as vector of DimSumClass objects - Dim Sums that were chosen in the chooseDimSums function
	*	@return an integer of 0
	* 
	*	Time complexity:
	*	-	the code before the for loop occurs once (constant time or O(1))
	*	-	the for loop occurs n times (4, 6 or 8 depending on difficulty), resulting in linear time or O(n)
	*	-	O notation: O(n) + O(1)
	*/
	std::cout << "Your chosen clues are:" << endl;
	int j;
	for (int i = 0; i < chosenDimSums.size(); i++) {
		j = i + 1;
		std::cout << j << ": " << chosenDimSums[i].getClue() << endl;
	}
	return 0;
}

int chooseCorrectSum(vector<DimSumClass>& chosenDimSums, int& numOfClues) {
	/**
	*	Choose the target number by randomly choosing two of the chosen DimSums. A while loop is used to ensure that these numbers are different
	* 
	*	Generate pseudo-random numbers using code adapted from C++ Reference (Pseudo-random number generation, 2021)
	*	@param chosenDimSums as vector of DimSumClass objects - Dim Sums that were chosen in the chooseDimSums function
	*	@param numOfClues as integer - this is set to 4, 6 or 8 depending on difficulty
	*	@return the value of chosenDimSums[rand1] + the value of chosenDimSums[rand2].getValue() - return the sum of the values of each clue chosen as the correct answer
	* 
	*	Time complexity:
	*	-	the code before and after the while loop occur once (constant time or O(1))
	*	-	the while loop occurs n times (the loop repeats if both randomly chosen numbers are the same), resulting in linear time or O(n)
	*	-	O notation: O(1) + O(n)
	*/
	random_device device;
	default_random_engine engine(device());
	uniform_int_distribution<int> uniformRandom(0, (numOfClues - 1));
	int rand1 = uniformRandom(engine);
	int rand2 = uniformRandom(engine);
	/**
	*	End of adapted code
	*/
	while (rand1 == rand2) {
		rand2 = uniformRandom(engine);
	}
	return chosenDimSums[rand1].getValue() + chosenDimSums[rand2].getValue();
}

vector<string> getFile() {
	/**
	*	Load the clues file from Boost
	*	@return output as a vector of strings - all clues from the Boost file are parsed into this variable
	*
	*	The following clues have been added to the clues file:
	* 
	*	From Facts.Net (Sophia, 2022):
	*	-	a number whose value is equivalent to the number of letters in the spelling: 4
	*	-	shortest number of days to count to 1 million: 89
	*	-	an unlucky number in eastern Asia: 4
	*	-	the century in which the lottery system was cracked: 18
	*	-	number of colours in typical road maps: 4
	*	-	the fear of a certain number is known as triskaidekaphobia: 13

	*	From BestLife (Daniel, 2019):
	*	-	the only prime number that is even: 2
	*	-	the Pythagoras Constant is the name for the square root of a certain number: 2
	*	-	the only number with no representation in Roman numerals0
	*	-	number of zeros in a googlol: 100
	* 
	*	Time complexity:
	*	-	the code before the for loop occurs once (constant time or O(1))
	*	-	the for loop occurs n times (depending on how many Dim Sums need to be retrieved using Boost), leading to O(n) or linear time
	*	-	O notation: O(1) + O(n)
	*/

	list<string> dimSums;
	/**
	*	Initial code included for importing data from the prototype's text file
	*/
	/*
	ifstream file("clues.txt");
	string dimSum;
	// Store each line of the clues file into the vector dimSums
	while (getline(file, dimSum)) {
		dimSums.push_back(dimSum);
	}

	// Export clues file for Boost serialization
	{
		ofstream out("boostFile.txt");
		archive::text_oarchive arch(out);
		arch << dimSums;
		std::cout << "Exported contents to Boost" << endl;
	}
	*/
	/**
	*	Import data from Boost file
	*/
	try {
		ifstream in("boostFile.txt");
		archive::text_iarchive arch(in);
		arch >> dimSums;
	}
	catch (std::exception e) {
		cerr << e.what();
	}
	vector<string> output;
	for (string instance : dimSums) {
		output.push_back(instance);
	}

	return output;
}

int getNumOfClues() {
	/**
	*	Accept an integer to the server based on difficulty
	*	@return numOfClues as integer numOfClues as integer - this is set to 4, 6 or 8 depending on difficulty
	*	
	*	Time complexity:
	*	-	the code in this function occurs once (resulting in constant time or O(1))
	*/
	asio::io_service ios;
	tcp::endpoint endpoint(tcp::v4(), 7000);
	tcp::acceptor acceptor(ios, endpoint);
	tcp::iostream serverStream;
	acceptor.accept(*serverStream.rdbuf());
	int numOfClues;
	serverStream >> numOfClues;
	return numOfClues;
}

int sendTargetSum(int& targetSum) {
	/**
	*	Send the target sum to the client
	*	@param targetSum as integer - this is the target number chosen by the function chooseCorrectSum (in server)
	*	@return an integer of 0
	* 
	*	Time complexity:
	*	-	the code in this function occurs once (resulting in constant time or O(1))
	*/
	tcp::iostream clientStream("127.0.0.1", "7001");
	clientStream << int(targetSum);
	return 0;
}

int sendChosenDimSums(int& value) {
	/**
	*	Send the chosen Dim Sum values to the client
	*	@param value as integer - the value of each Dim Sum that was chosen by the server (one-by-one)
	*	@return an integer of 0
	* 
	*	Time complexity:
	*	-	the code in this function occurs once (resulting in constant time or O(1))
	*/
	tcp::iostream clientStream("127.0.0.1", "7002");
	clientStream << int(value);
	return 0;
}

string getClientResponse() {
	/**
	*	Get a string from the client that gives the server an instruction
	* 
	*	If the string is:
	*	-	"start" then the server asks a question and the client answers
	*	-	"stop" then the server exits and the leaderboard functionality is executed by the client
	*	@return connect as string - the string obtained from the client
	* 
	*	Time complexity:
	*	-	the code in this function occurs once (resulting in constant time or O(1))
	*/
	asio::io_service ios;
	tcp::endpoint endpoint(tcp::v4(), 7003);
	tcp::acceptor acceptor(ios, endpoint);
	tcp::iostream connectStream;
	acceptor.accept(*connectStream.rdbuf());
	string connect;
	connectStream >> connect;
	return connect;
}

int main() {
	/**
	*	This file contains the code for the server. This should be executed before running the client. To run this file in Visual Studio:
	*	-	select the "Local Windows Debugger" button in the Visual Studio window
	*	Alternatively:
	*	-	right-click the server project file
	*	-	select debug then start new instance
	*
	*	Please note that the following folders have been included in the client and server projects, granting the use of Boost:
	*	-	Additional Include Directories: C:\Users\jclif\Documents\Extracted Apps\Boost\boost_1_77_0
	*	-	Additional Include Library Directories: C:\Users\jclif\Documents\Extracted Apps\Boost\boost_1_77_0\stage\lib
	*	These folders link to a copy of Boost downloaded via ZIP file (later extracted) to the Documents folder allocated to a Windows account. For this reason, this solution may not run on other devices
	*
	*	You may wish to change the directories if needed using the following steps (where <Project Name> is the name of the client and server projects - these are called Server and Client respectively)
	*	-	to modify the Additional Include Directories, go to Project in the menu bar, select <Project Name> Properties and choose C/C++ in the window that appears
	*	-	to modify the Additional Include Library Directories, go to Project in the menu bar, select <Project Name> Properties and choose Linker in the window that appears
	*
	*	***
	* 
	*	This function calls other methods in this file
	*	@return an integer of 0
	* 
	*	Time complexity:
	*	-	the while loop occurs n times, leading to linear time or O(n)
	*	-	however, other methods that are called also cause linear time
	*	-	Therefore, the resulting O notation is O(n^8), considering the number of loops in the called functions
	*/
	std::cout << "This is the Server" << endl;
	/**
	*	Set the following colours for this project. This allows the player to identify which program is the server and which is the client (when both are running). Code adapted from C++ Reference (rcast, 2013)
	*	-	background: 0 (black)
	*	-	foreground (text): b (light aqua)
	*/
	std::system("color 0b");
	/**
	*	End of adapted code
	*/
	while (true) {
		/**
		*	Get a string from the client that gives the server an instruction
		*/
		asio::io_service ios;
		tcp::endpoint endpoint(tcp::v4(), 7003);
		tcp::acceptor acceptor(ios, endpoint);
		tcp::iostream connectStream;
		std::cout << "" << endl;
		std::cout << "Waiting for a response from the client..." << endl;
		acceptor.accept(*connectStream.rdbuf());
		string connect;
		connectStream >> connect;
		if (connect == "stop") {
			break;
		}
		/**
		*	Accept an integer to the server based on difficulty
		*/
		int numOfClues = getNumOfClues();
		/**
		*	Get data from Boost serialisation
		*/
		vector<string> dataFromFile = getFile();
		/**
		*	Generate a vector of Dim Sums as DimSumClass objects
		*/
		vector<DimSumClass> dimSumClassVector = getDimSums(dataFromFile);
		/**
		*	Select difficulty and determine number of clues to output
		*/
		vector<DimSumClass> chosenDimSums = chooseDimSums(dimSumClassVector, numOfClues);
		/**
		*	Output each chosen Dim Sum
		*/
		outputDimSums(chosenDimSums);
		/**
		*	Specify target number and send it to client
		*/
		int targetSum = chooseCorrectSum(chosenDimSums, numOfClues);
		std::cout << "Your target is " << targetSum << endl;
		sendTargetSum(targetSum);
		/**
		*	Send chosen Dim Sums to the client
		*/
		for (DimSumClass instance : chosenDimSums) {
			int value = instance.getValue();
			sendChosenDimSums(value);
		}
	}
	std::cout << "This program has finished executing. You may now close this window." << endl;
	return 0;
}