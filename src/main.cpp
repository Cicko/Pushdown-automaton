#include "Stack.hpp"
#include "InTape.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main () {
	InTape * myTape = new InTape();


	myTape->loadFromKeyboard();

	myTape->show();

}
