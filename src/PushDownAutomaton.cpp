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

// Initialization methods
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


// Execution methods
bool PushDownAutomaton::checkInput (bool trace) {
  if (!inputTape_->isEmpty()) {
    acceptedInput_ = false;
    if (trace)
      cout << "---- State ---- ---- Input ---- ---- Stack ---- ---- Actions ----" << endl;
      nextStep (actualState_, *inputTape_, *stack_, 0, trace);
      return acceptedInput_;
  }
  else {
    cout << endl << "You have to load input first." << endl;
    return false;
  }
}

void PushDownAutomaton::nextStep (string actualState, InTape input, Stack stack, int readCount, bool trace) {
  if (!acceptedInput_) {
    try {
        if (!input.hasNext()) {
          if (isFinalState(actualState)) {
            acceptedInput_ = true;
          }
        }

        vector<transition_t> allowedTransitions = getAllowedTransitionsForState (actualState, input, stack);

        if (trace)
          showActualTraceInfo (actualState, input, stack, allowedTransitions);

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
          string symbols;
          iss2 >> symbols;

          tempStack.pop();
          for (int i = symbols.size() - 1; i >= 0; i--) {
            string symbol = utils::charToString(symbols[i]);
            if (symbol != "e")
              tempStack.push (symbol);
          }

          nextStep (nextState, tempInput, tempStack, readCount, trace);
        }
    }
    catch (exception& e) {
      cout << e.what() << '\n';
    }
  }
}


vector<transition_t> PushDownAutomaton::getAllowedTransitionsForState (string actualState, InTape input, Stack stack) {
  string actual = actualState + " " + input.read() + " " + stack.getTop();
  string actualEmpty = actualState + " e " + stack.getTop(); // This transition is used to check e-transitions

  vector<transition_t> allowed;
  for (int i = 0;i < transitions_.size(); i++)
    if (transitions_[i].first == actual || transitions_[i].first == actualEmpty)
      allowed.push_back(transitions_[i]);

  return allowed;
}

void PushDownAutomaton::showActualTraceInfo (string actualState, InTape input, Stack stack, vector<transition_t> allowedTransitions) {
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
}

void PushDownAutomaton::showAllowedTransitions (vector<transition_t> transitions) {
  for (int i = 0; i < transitions.size(); i++) {
    cout << transitions[i].second;
    if (i < transitions.size() - 1)
      cout << ", ";
  }
  cout << endl;
}





bool PushDownAutomaton::isFinalState (string state) {
  return any_of(finalStates_.begin(), finalStates_.end(), [&state](string finalState) { return state == finalState; });
}


// Private methods

void PushDownAutomaton::readStates (string states) {
  states_ = utils::lineToStrings (states, " ");
}


void PushDownAutomaton::readInputSymbols (string symbols) {
  inputSymbols_ = utils::lineToStrings (symbols, " ");
}

void PushDownAutomaton::readStackSymbols (string symbols) {
  stack_ = new Stack (utils::lineToStrings (symbols, " "));
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
    finalStates_ = utils::lineToStrings (states, " ");
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
