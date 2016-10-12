/***
* @author: Rudolf Cicko
* @email: alu0100824780@ull.edu.es / rudolfcicko2011@gmail.com
* @subject: Complejidad computacional at Universidad de La Laguna
* @year: 2016
* @description: Bunch of helpers methods. Specially for string manipulation.
*
***/
#ifndef _UTILS_HPP_
#define _UTILS_HPP_
#include <string>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

namespace utils {
  // This method divide by a delimiter a whole string into an array of strings.
	vector<string> lineToStrings (string line, string delimiter);
	string charToString (char c);
}


#endif
