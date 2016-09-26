#include <iostream>
#include <fstream>
#include <string>
#include "Stack.hpp"
#include "InTape.hpp"


using namespace std;

class PushDownAutomaton{
	Stack* stack_;
	InTape* inputTape_;
	unsigned actualState_;
	vector<string> transitions_;

public:
	PushDownAutomaton(string fileName);
	~PushDownAutomaton();

	void loadInput (string fileName);
	void loadAutomaton (string fileName);
	void nextStep ();
	void showTrace ();
	bool isTheInputAccepted ();

};
