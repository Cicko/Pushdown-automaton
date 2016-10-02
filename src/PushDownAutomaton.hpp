/***
* @author: Rudolf Cicko
* @email: alu0100824780@ull.edu.es / cickogames@gmail.com
* @subject: Complejidad computacional at Universidad de La Laguna
* @year: 2016
* @description: Input tape class that will contain the characters to determine if the string
*               pertain to a specific language.
***/
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <string>
#include <utility> // pair class
#include "Stack.hpp"
#include "InTape.hpp"
#include <string.h>

using namespace std;

typedef pair<string, string> transition_t;

class PushDownAutomaton {
	vector<string> states_;
	vector<string> inputSymbols_;
	vector<string> finalStates_;
	vector<transition_t> transitions_;
	//TransitionsHash* transitions_;
	string initialState_;

	Stack* stack_;
	InTape* inputTape_;
	string actualState_;

public:
	PushDownAutomaton(string fileName);
	PushDownAutomaton (string automatonFile, string inputFile);
	~PushDownAutomaton();

	void loadInput (string fileName);
	void loadInputByKeyboard ();
	void loadAutomaton (string fileName);
	void nextStep (string actualState, InTape input, Stack stack, int readCount, bool trace);
	void checkInput (bool trace);
	vector<transition_t> getAllowedTransitionsForState (string state, InTape input, Stack stack, bool verbose);
	bool isFinalState (string state);
	void show ();

private:
	void readStates (string states);
	void readInputSymbols (string symbols);
	void readStackSymbols (string symbols);
	void readInitialState (string state);
	void readInitialStackSymbol (string symbol);
	void readFinalStates (string states);
	void saveTransition (string transition);
	vector<string> lineToStrings (string line);
};
