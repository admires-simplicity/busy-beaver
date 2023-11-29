#include <bits/stdc++.h>
using namespace std;

#define RIGHT true
#define LEFT false
#define ONE true
#define ZERO false


class Rule {
public:
	const bool write; // F == 0, T == 1
	const bool move;  // F == L, T == R
	const int next_rule;
	Rule(bool write, bool move, int next_rule) : write(write), move(move), next_rule(next_rule) {}
	Rule() : write(ZERO), move(LEFT), next_rule(0) {}
};

class State {
public:
	Rule zero;
	Rule one;
	State(Rule zero, Rule one) : zero(zero), one(one) {}
	State() {}
};

int main() {
  vector<State> states { 
	State(), // "null" (terminal) state
    	State(Rule(ONE, RIGHT, 2), Rule(ONE, LEFT, 2)),
        State(Rule(ONE, LEFT, 1),  Rule(ZERO, LEFT, 3)),
        State(Rule(ONE, RIGHT, 0), Rule(ONE, LEFT, 4)),
        State(Rule(ONE, RIGHT, 4), Rule(ZERO, RIGHT, 1))
  };

  //vector<State> states {
  //	State(Rule(false, false, 0), Rule(false, false, 0)), //"null" state
  //	State(Rule(true, true, 0), Rule(true, true, 0))
  //};

  deque<bool> tape {ZERO};

  int read_head = 0;
  int state = 1;

  // initial write (just "0")
  for (auto b : tape) {
    if (b == ZERO) cout << '0';
    else cout << '1';
  }
  cout << '\n';

  while (state) {
    bool read = tape[read_head];
    Rule &rule = read ? states[state].one : states[state].zero;

    //write
    tape[read_head] = rule.write;

    //move
    if (rule.move == LEFT) {
      if (read_head == 0) tape.push_front(ZERO);
      else --read_head;
    }
    else {
      ++read_head;
      if (read_head == tape.size()) tape.push_back(ZERO);
    }

    //next state
    state = rule.next_rule;

    //display tape
    for (auto b : tape) {
      if (b == ZERO) cout << '0';
      else cout << '1';
    }
    cout << '\n';
  }
}
