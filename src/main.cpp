#include "PushDownAutomaton.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>

#define EXIT 7

using namespace std;

int showMenu () {
	int option;

	cout << "--- Welcome to Pushdown Automaton ---" << endl;
	cout << "1. Load automaton." << endl;
	cout << "2. Show automaton." << endl;
	cout << "3. Load input from file." << endl;
	cout << "4. Load input from keyboard." << endl;
	cout << "5. Accepted input?" << endl;
	cout << "6. Accepted input? (with trace)" << endl;
	cout << "7. Exit" << endl << endl;

	cout << "Insert option (1-7): ";
	cin >> option;

  return option;
}

void executeAutomaton (PushDownAutomaton* automaton, bool trace) {
	if (automaton->checkInput(trace))
		cout << endl << "Input is accepted" << endl << endl;
	else
		cout << endl << "Input is NOT accepted" << endl << endl;
}

int main (int argc, char * argv[]) {
	string automatonFileName;
	string inputFileName;
	int option;

	PushDownAutomaton * automaton;
	do {
		option = showMenu();

		switch (option) {
			case 1:
			  cout << "Insert the automaton filename: ";
				cin >> automatonFileName;
				automaton = new PushDownAutomaton (automatonFileName);
				break;
			case 2:
				automaton->show();
				break;
			case 3:
				cout << "Insert the input filename: ";
				cin >> inputFileName;
				automaton->loadInput(inputFileName);
				break;
			case 4:
				automaton->loadInputByKeyboard();
				break;
			case 5:
				executeAutomaton (automaton, false);
				break;
			case 6:
				executeAutomaton (automaton, true);
				break;
			case 7:
				cout << "Exiting..." << endl;
				break;
			default:
				cout << "Option " << option << " doesn't exist.." << endl;
		}
	}while (option != EXIT);

	return 0;

}
