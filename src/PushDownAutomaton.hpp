/***
* @author: Rudolf Cicko
* @email: alu0100824780@ull.edu.es / cickogames@gmail.com
* @subject: Complejidad computacional at Universidad de La Laguna
* @year: 2016
* @description: The Pushdown automaton class
*
***/
#ifndef _PUSH_DOWN_AUTOMATON_HPP_
#define _PUSH_DOWN_AUTOMATON_HPP
#include <iostream>
#include <fstream>
#include <sstream>    // stringstream
#include <exception>
#include <iomanip>    // setw
#include <algorithm>  // any_of
#include <string>
#include "Utils.hpp"  // lineToString, charToString
#include <utility>    // pair class
#include "Stack.hpp"
#include "InTape.hpp"

using namespace std;

typedef pair<string, string> transition_t;

// Pushdown automaton that works by final state
class PushDownAutomaton {
	vector<string> states_;
	vector<string> inputSymbols_;
	vector<string> finalStates_;
	vector<transition_t> transitions_;
	string initialState_;

	Stack* stack_;
	InTape* inputTape_;
	string actualState_;
	bool acceptedInput_;

public:
	PushDownAutomaton(string fileName);
	PushDownAutomaton (string automatonFile, string inputFile);
	~PushDownAutomaton();

	void loadInput (string fileName);
	void loadInputByKeyboard ();
	void loadAutomaton (string fileName);
	void nextStep (string actualState, InTape input, Stack stack, int readCount, bool trace);
	bool checkInput (bool trace);
	vector<transition_t> getAllowedTransitionsForState (string state, InTape input, Stack stack);
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
	void showActualTraceInfo (string state, InTape input, Stack stack, vector<transition_t> allowed);
	void showAllowedTransitions (vector<transition_t> transitions);
};

#endif
