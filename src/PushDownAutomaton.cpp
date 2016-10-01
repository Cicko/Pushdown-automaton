#include "PushDownAutomaton.hpp"


PushDownAutomaton::PushDownAutomaton (string fileName) {
  inputTape_ = new InTape();
  loadAutomaton(fileName);
}

PushDownAutomaton::PushDownAutomaton (string automatonFile, string inputFile) {
  inputTape_ = new InTape();
  loadAutomaton(automatonFile);
  loadInput(inputFile);
}

void PushDownAutomaton::loadInput (string fileName) {
  inputTape_->loadFromFile(fileName);
}


void PushDownAutomaton::loadInputByKeyboard () {
    inputTape_->loadFromKeyboard();
}

void PushDownAutomaton::loadAutomaton (string fileName) {
  ifstream file;
  file.open(fileName.c_str());
  if (file.is_open()) {
      string temp;
      getline (file, temp);
      readStates (temp);
      getline (file, temp);
      readInputSymbols(temp);
      getline (file, temp);
      readStackSymbols(temp);
      getline (file, temp);
      readInitialState(temp);
      getline (file, temp);
      readInitialStackSymbol (temp);
      getline (file, temp);
      readFinalStates (temp);
      while (!file.eof()) {
        getline (file, temp);
        saveTransition (temp);
      }
      file.close();
  }
  else {
    cerr << "El fichero no existe" << endl;
  }
}


void PushDownAutomaton::nextStep (string actualState, InTape input, Stack stack, bool trace) {
  vector<transition_t> allowedTransitions = getAllowedTransitionsForState (actualState, input, stack);
  cout << "Allowed Transitions: " << endl;
  for (int i = 0; i < allowedTransitions.size(); i++) {
    cout << allowedTransitions[i].first << " --> " << allowedTransitions[i].second << endl;
  }
}

vector<transition_t> PushDownAutomaton::getAllowedTransitionsForState (string actualState, InTape input, Stack stack) {
  string actual = actualState + " " + input.read() + " " + stack.getTop();
  string actualEmpty = actualState + " e " + stack.getTop();

  vector<transition_t> allowed;
  for (int i = 0;i < transitions_.size(); i++)
    if (transitions_[i].first == actual || transitions_[i].first == actualEmpty)
      allowed.push_back(transitions_[i]);
  return allowed;
}


void PushDownAutomaton::checkInput (bool trace) {
  nextStep (actualState_, *inputTape_, *stack_, trace);
}



// Private methods

void PushDownAutomaton::readStates (string states) {
  states_ = lineToStrings (states);
}


void PushDownAutomaton::readInputSymbols (string symbols) {
  inputSymbols_ = lineToStrings (symbols);
}

void PushDownAutomaton::readStackSymbols (string symbols) {
  stack_ = new Stack (lineToStrings (symbols));
}

void PushDownAutomaton::readInitialState (string state) {
  initialState_ = state;
  actualState_ = initialState_;
}

void PushDownAutomaton::readInitialStackSymbol (string symbol) {
  stack_->push(symbol);
}

void PushDownAutomaton::readFinalStates (string states) {
  if (states != "")
    finalStates_ = lineToStrings (states);
  else
    finalStates_.push_back("NO_FINAL");
}

void PushDownAutomaton::saveTransition (string transition) {
  //transitions_.push_back(transition);
  string actual = "";
  string next = "";
  istringstream iss(transition);

  string temp;
  iss >> temp;  // Actual state
  if (temp.size() > 1) {
    actual += temp;
    actual += " ";
    iss >> temp;  // actual input character
    actual += temp;
    actual += " ";
    iss >> temp;  // actual stack symbol
    actual += temp;

    iss >> temp;    // next state
    next += temp;
    next += " ";
    iss >> temp;    // next symbol to push to stack
    next += temp;

    transition_t trans;
    trans.first = actual;
    trans.second = next;
    transitions_.push_back(trans);
  }
}


// Show all description of the automaton.
void PushDownAutomaton::show () {
  vector<string> acceptedSymbols = stack_->getAcceptedSymbols();
  string initialStackSymbol = stack_->getInitialSymbol ();

  cout << "States: {";
  for (int i = 0;i < states_.size(); i++) {
    cout << states_[i];
    if (i < states_.size() - 1)
      cout << ", ";
    else
      cout << "}" << endl;

  }

  cout << "Input symbols: {";
  for (int i = 0; i < inputSymbols_.size(); i++) {
    cout << inputSymbols_[i];
    if (i < inputSymbols_.size() - 1)
      cout << ", ";
    else
      cout << "}" << endl;
  }

  cout << "Stack symbols: {";
  for (int i = 0; i < acceptedSymbols.size(); i++) {
    cout << acceptedSymbols[i];
    if (i < acceptedSymbols.size() - 1)
      cout << ", ";
    else
      cout << "}" << endl;
  }

  cout << "Initial state: " << initialState_ << endl;

  cout << "Initial stack symbol: " << initialStackSymbol << endl;

  if (finalStates_[0] != "NO_FINAL") {
    cout << "Final States: {";
    for (int i = 0; i < finalStates_.size(); i++) {
      cout << finalStates_[i];
      if (i < finalStates_.size() - 1)
        cout << ", ";
      else
        cout << "}" << endl;
    }
  }

  cout << "Transitions: "<< endl;
  for (int i = 0;i < transitions_.size(); i++) {
    cout << "(" << transitions_[i].first << ") -->  (" << transitions_[i].second << ")" << endl;
  }
  cout << endl;
}

vector<string> PushDownAutomaton::lineToStrings (string line) {
  vector<string> strings;
  char * pch;
  pch = strtok ( (char*) line.c_str()," ");
  while (pch != NULL) {
    strings.push_back(pch);
    pch = strtok (NULL, " ");
  }
  return strings;
}
