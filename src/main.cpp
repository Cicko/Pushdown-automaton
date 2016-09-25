#include "Stack.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main () {
	vector<char> symbols;
	symbols.push_back('a');
	symbols.push_back('b');
	symbols.push_back('c');

	Stack stack(symbols);

	stack.push('a');
	stack.push('b');
  	stack.push('b');
	stack.push('d');

	stack.show();

	stack.pop();

	stack.show();

}
