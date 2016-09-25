#include "PushDownAutomaton.hpp"


PushDownAutomaton::PushDownAutomaton (string fileName) {
  loadInput(fileName);
}



void PushDownAutomaton::loadInput (string fileName) {
  ifstream file;
  string fileData = "";
  fileName_ = fileName;
  file.open (fileName.c_str());
  if (file.is_open()) {
    while (!file.eof()) {
      string temp;
      getline (file,temp);
      fileData += temp + "\n";
    }
    file.close();
  }
  else {
    cerr << "El fichero no existe" << endl;
  }
  return fileData;
}
