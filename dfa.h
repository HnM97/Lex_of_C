#ifndef DFA_H
#define DFA_H

#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

typedef pair<int, char> pic;

class dfa {
public:
    dfa(string);
    ~dfa() {}
    bool accept(string);
private:
    set<int> finalStates;
    set<char> alphabets;
    map<pic, int> transitions;
    int initState;
};

#endif