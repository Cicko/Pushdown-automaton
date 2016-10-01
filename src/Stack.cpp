#include "Stack.hpp"
#include <algorithm>


Stack::Stack (vector<string> aSymbols) {
	acceptedSymbols = aSymbols;
}

Stack::~Stack () { }


void Stack::push (string symbol) {
  if (find(acceptedSymbols.begin(), acceptedSymbols.end(), symbol) != acceptedSymbols.end()) {
		if (getSize() == 0) initialSymbol = symbol;
		content.push_back(symbol);
	}
	else
		cout << "The symbol " << symbol << " is not contained in the stack alphabet" << endl;
}

string Stack::pop () {
	if (content.size() > 0) {
		string last = content.back();
		content.pop_back();
		return last;
	}
	return "";
}

string Stack::getTop () {
	return content.back();
}

const unsigned Stack::getSize () {
  return content.size();
}

const string Stack::getInitialSymbol () {
	return initialSymbol;
}

const vector<string> Stack::getAcceptedSymbols () {
	return acceptedSymbols;
}



const void Stack::show () {
        cout << endl << "TOP" << endl;
 	for (int i = 0; i < getSize(); i++)
		if (i < getSize() - 1)
	  		cout << "    | " << content.at(getSize() - i - 1) << " |" << endl;
		else
	                cout << "    |_" << content.at(getSize() - i - 1) << "_|" << endl;
	cout  << endl;

}
