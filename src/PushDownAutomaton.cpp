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

void PushDownAutomaton::nextStep (string actualState, InTape input, Stack stack, int readCount, bool trace) {
  bool allowedTransitionsVerbose = false;
  if (!acceptedInput_) {
    try {
        if (!input.hasNext()) {
          if (isFinalState(actualState)) {
            acceptedInput_ = true;
          }
        }

        vector<transition_t> allowedTransitions = getAllowedTransitionsForState (actualState, input, stack, allowedTransitionsVerbose);

        cout << setw(8) << actualState << setw(14);
        input.showInline();
        cout << setw(14);
        stack.showInline();
        cout << setw(14);
        if (allowedTransitions.size() > 0)
          showAllowedTransitions (allowedTransitions);
        else {
          cout << "         NO TRANSITIONS ALLOWED.." << endl;
          cout << "==========================================================================" << endl;
        }


        for (int i = 0; i < allowedTransitions.size(); i++) {
          Stack tempStack = stack;
          InTape tempInput = input;
          string actual = allowedTransitions[i].first;
          string next = allowedTransitions[i].second;

          istringstream iss(actual);

          string readInput;
          iss >> readInput;  // Actual state
          iss >> readInput;  // actual input to read
          if (readInput != "e") {
            readInput = tempInput.read();
          }
          else {
            readInput = "e";  // We don't consume the input
          }

          istringstream iss2(next);
          string nextState;
          vector<string> nextStackSymbols;
          iss2 >> nextState;

          // it can push more than one symbol.
          while (!iss2.eof()) {
            string symbol;
            iss2 >> symbol;
            if (symbol != "" && symbol != "e")
              nextStackSymbols.push_back(symbol);
          }

          tempStack.pop();
          tempStack.push(nextStackSymbols);
          nextStep (nextState, tempInput, tempStack, readCount, trace);
        }
    }
    catch (exception& e) {
      cout << e.what() << '\n';
    }
  }
}

void PushDownAutomaton::showAllowedTransitions (vector<transition_t> transitions) {
  for (int i = 0; i < transitions.size(); i++) {
    cout << transitions[i].second;
    if (i < transitions.size() - 1)
      cout << ", ";
  }
  cout << endl;
}

bool PushDownAutomaton::checkInput (bool trace) {
  acceptedInput_ = false;
  cout << "---- State ---- ---- Input ---- ---- Stack ---- ---- Actions ----" << endl;
  nextStep (actualState_, *inputTape_, *stack_, 0, trace);
  return acceptedInput_;
}

vector<transition_t> PushDownAutomaton::getAllowedTransitionsForState (string actualState, InTape input, Stack stack, bool verbose) {
  string actual = actualState + " " + input.read() + " " + stack.getTop();
  string actualEmpty = actualState + " e " + stack.getTop();

  vector<transition_t> allowed;
  for (int i = 0;i < transitions_.size(); i++)
    if (transitions_[i].first == actual || transitions_[i].first == actualEmpty)
      allowed.push_back(transitions_[i]);

  if (verbose) {
    cout << "Allowed Transitions: " << endl;
    for (int i = 0; i < allowed.size(); i++) {
      cout << allowed[i].first << " --> " << allowed[i].second << endl;
    }
  }

  return allowed;
}


bool PushDownAutomaton::isFinalState (string state) {
  for (int i = 0 ;i < finalStates_.size(); i++) {
    if (state == finalStates_[i])
      return true;
  }
  return false;
}


// Private methods

void PushDownAutomaton::readStates (string states) {
  states_ = lineToStrings (states, " ");
}


void PushDownAutomaton::readInputSymbols (string symbols) {
  inputSymbols_ = lineToStrings (symbols, " ");
}

void PushDownAutomaton::readStackSymbols (string symbols) {
  stack_ = new Stack (lineToStrings (symbols, " "));
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
    finalStates_ = lineToStrings (states, " ");
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
    while (!iss.eof()) {
      iss >> temp;    // next symbol to push to stack
      next += temp ;
      next += " ";
    }

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

// This method divide by a delimiter a whole string into an array of strings.
vector<string> PushDownAutomaton::lineToStrings (string line, string delimiter) {
  vector<string> strings;
  char * pch = strtok ( (char*) line.c_str(),delimiter.c_str());
  while (pch != NULL) {
    strings.push_back(pch);
    pch = strtok (NULL, delimiter.c_str());
  }
  return strings;
}
