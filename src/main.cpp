#include "PushDownAutomaton.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main (int argc, char * argv[]) {
	PushDownAutomaton * automaton = new PushDownAutomaton (argv[1]);

	automaton->show();

	automaton->loadInputByKeyboard();

	automaton->checkInput(false);

}
