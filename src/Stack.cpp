#include "Stack.hpp"
#include <algorithm>


Stack::Stack (vector<char> aSymbols) {
	symbols = aSymbols;
}

Stack::~Stack () { }


void Stack::push (char symbol) {
        if (find(symbols.begin(), symbols.end(), symbol) != symbols.end())
		content.push_back(symbol);
	else
		cout << "The symbol " << symbol << " is not contained in the stack alphabet" << endl;
}

char Stack::pop () {
	char last = content.back();
	content.pop_back();
	return last;
}

unsigned Stack::getSize () {
  	return content.size();
}

void Stack::show () {
        cout << endl << "TOP" << endl;
 	for (int i = 0; i < getSize(); i++)
		if (i < getSize() - 1)
	  		cout << "    | " << content.at(getSize() - i - 1) << " |" << endl;
		else
	                cout << "    |_" << content.at(getSize() - i - 1) << "_|" << endl;
	cout  << endl;
	
}    



