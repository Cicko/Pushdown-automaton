#include "Utils.hpp"



// This method divide a string by the delimiter and put them into a vector of strings
vector<string> utils::lineToStrings (string line, string delimiter) {
  vector<string> strings;
  char * pch = strtok ( (char*) line.c_str(),delimiter.c_str());
  while (pch != NULL) {
    strings.push_back(pch);
    pch = strtok (NULL, delimiter.c_str());
  }
  return strings;
}

// Convert simple char to string
string utils::charToString (char c) {
  stringstream ss;
  string s;
  ss << c;
  ss >> s;
  return s;
}
