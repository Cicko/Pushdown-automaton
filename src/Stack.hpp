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
};
