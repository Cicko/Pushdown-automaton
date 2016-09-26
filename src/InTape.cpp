#include "InTape.h"
#include <fstream>
#include <iostream>

using namespace std;


InTape::InTape () {}

InTape::InTape (string fileName) {
  load(fileName);
}


InTape::~InTape (){
   clear();
}

void InTape::loadFromFile (string fileName) {
  inx_ = 0;
  fstream file;
  int aChar;
  fileName_ = fileName;
  file.open(fileName.c_str(), ios::in);

  if(file.is_open()) {
      chars_.clear();
    while(file >> aChar){
      chars_.push_back(aChar);
    }
    file.close();
  }
  else{
      cerr << "El fichero no existe" << endl;
  }
}

void InTape::loadFromKeyboard () {
  cout << "Put characters for the input tape. type 'exit' to finish." << endl;
  string actual;
  unsigned iterator = 0;
  do {
    cout << "Character " << iterator++ << ": ";
    cin >> actual;
    if (actual.compare("exit") != 0)
      chars_.push_back(actual);

  } while (actual.compare("exit") != 0);
}

string InTape::read ()
{
  if (inx_ < chars_.size())
      return chars_[inx_++];
  else
      return 0;
}

bool InTape::hasNext ()
{
  return inx_ < chars_.size();
}


void InTape::reset (string fileName)
{
  load(fileName);
}

// return to the first position
void InTape::reset () {
  inx_ = 0;
}

// Show the content of the input tape.
void InTape::show () {
  cout << "INPUT TAPE: [";
  for (int i = 0;i < chars_.size; i++) {
    cout << chars_[i] << ", ";
  }
  cout << "]" << endl;
}
