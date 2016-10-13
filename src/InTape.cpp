#include "InTape.hpp"
#include <fstream>
#include <iostream>

using namespace std;


InTape::InTape () {}

InTape::InTape (string fileName) {
  loadFromFile (fileName);
}


InTape::~InTape (){
   chars_.clear();
}

void InTape::loadFromFile (string fileName) {
  reset();
  inx_ = 0;
  fstream file;
  string symbol;
  fileName_ = fileName;
  file.open(fileName.c_str(), ios::in);

  if(file.is_open()) {
      chars_.clear();
      while(file >> symbol){
        chars_.push_back(symbol);
    }
    file.close();
  }
  else{
      cerr << "El fichero no existe" << endl;
  }
}


void InTape::loadFromKeyboard () {
  reset();
  string input;
  cout << "Put string as input: ";
  cin >> input;
  // Divide the whole string into substrings of size 1 and put them into the input tape.
  for_each (input.begin(), input.end(), [&] (char c) { chars_.push_back(utils::charToString(c)); });
}


// Read input from tape so the head go forward
string InTape::read () {
  if (inx_ < chars_.size())
      return chars_[inx_++];
  else
      return "";
}

// Return true if the head is not still at the end.
bool InTape::hasNext () {
  return inx_ < chars_.size();
}


// return to the first position
void InTape::reset () {
  chars_.clear();
  inx_ = 0;
}

// Show the content of the input tape.
const void InTape::show () {
  cout << "INPUT TAPE: [";
  for (int i = 0;i < chars_.size(); i++) {
    cout << chars_[i];
    if (i < chars_.size() - 1)
      cout << ", ";
  }
  cout << "]" << endl;
}


const void InTape::showInline () {
  for (int i = inx_; i < chars_.size(); i++) {
    cout << chars_[i];
  }
  cout << "$";
}
