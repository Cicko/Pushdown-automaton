#include <iostream>
#include <fstream>
#include <string>
#include "Stack.hpp"
#include "ITape.hpp"


using namespace std;

class PushDownAutomaton{
	Stack stack;
	ITape inputTape;
	unsigned actualState;

public:
	PushDownAutomaton(string fileName);
	~PushDownAutomaton();

	void loadInput (string fileName);
	void loadAutomaton (string fileName);
	void nextStep ();
	void showTrace ();
	bool isTheInputAccepted ();

};
