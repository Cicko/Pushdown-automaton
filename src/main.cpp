#include "PushDownAutomaton.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main (int argc, char * argv[]) {
	if (argc == 2) {
		PushDownAutomaton * automaton = new PushDownAutomaton (argv[1]);

		automaton->show();

		automaton->loadInputByKeyboard();

		if (automaton->checkInput(false))
		cout << endl << "Input is accepted" << endl;
		else
		cout << endl << "Input is NOT accepted" << endl;

		return 0;
	}
	else {
		cout << "Usage: ./PushDownAutomaton <automaton_file>" << endl;
		return -1;
	}

}
