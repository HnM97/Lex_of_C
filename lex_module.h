#ifndef LEX_MODULE_H
#define LEX_MODULE_H

#include "dfa.h"

#define pb(n) push_back((n))
#define MAX_N 128

enum tok_type {
    WS, SYMBOLS, OP, LITERAL, INTEGER, FLOAT, KEYWORD, ID, 
};

struct token {
    string tok;
    tok_type tt;
    int line, col;
    union u{
        int n;
        float f;
        char *s;
    } val;
    token(string t, tok_type a, int l, int c, u v) {
        tok = t;
        tt = a;
        line = l;
        col = c;
        val = v;
    }
    ~token() {}
};

struct _trie{
    _trie *child[MAX_N];
    bool isTerminal;

    _trie() : isTerminal(false) {}
    ~_trie() {
        for(int i = 0;i < MAX_N;++i)
            if(child[i]) delete(child[i]);
    }
    void insert(const char *key) {
        if(*key == '\0') isTerminal = true;
        int next = *key;    
        if(!child[next]) child[next] = new _trie();
        child[next]->insert(key + 1);
    }
    bool find(const char *key) {
        if(*key == '\0') return isTerminal;
        int next = *key;
        if(!child[next]) return false;
        return child[next]->find(key + 1);
    }
};

class lex {
public:
    lex();
    ~lex();
    void analyze(string &);
private:
    _trie *keywords;
    map<char, string> symbols;
    dfa identifier, integer, float_number;
    vector<token> tokens;

    int line, col;
    ifstream source;

    void init();
    void error_occur(char *, int, int);
    void get_char(char &);
    bool isWS(char);
    bool isSymbol(char);
    bool isOp(char);
    bool isKeyword(string &);
    void get_tok(string &);
};

#endif