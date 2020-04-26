#include "dfa.h"

dfa::dfa(string filename) {
    ifstream source(filename);

}

bool dfa::accept(string input) {
    if(!input.length()) return false;

    int curState = initState;

    for(char in : input) {
        if(alphabets.count(in)) {
            auto it = transitions.find(pic(curState, in));
            if(it != transitions.end()) curState = it->second;
            else return false;
        }
        else return false;
    }
    return finalStates.count(curState) > 0;
}