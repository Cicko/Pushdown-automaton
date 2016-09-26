/***
* @author: Rudolf Cicko
* @email: alu0100824780@ull.edu.es / cickogames@gmail.com
* @subject: Complejidad computacional at Universidad de La Laguna
* @year: 2016
* @description: Stack class used for the Automaton to push and pop characters depending on the transition functions.
*
***/

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class Stack {
  vector<char> symbols;  // Símbolos que acepta la pila.
  vector<char> content; // Contenido de la pila.

public:
  Stack (vector<char> aSymbols);
  ~Stack ();

  void push (char symbols);
  char pop ();
  unsigned getSize();
  void show ();
};
