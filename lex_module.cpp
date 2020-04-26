#include "lex_module.h"

lex::lex() : identifier("iden.txt"), integer("int.txt"), float_number("float.txt") {
    keywords = new _trie();
    
    symbols['('] = "LPAREN";
    symbols[')'] = "RPAREN";
    symbols['{'] = "LBRACE";
    symbols['}'] = "RBRACE";
    symbols[';'] = "SEMI COLON";
    symbols[','] = "COMMA";
}

lex::~lex() {

}

void lex::init() {
    line = col = 0;
    tokens.clear();
}

void lex::get_char(char &c) {
    source >> c;
    if(c == '\n') {
        line += 1;
        col = 0;
    }
    else col += 1;
}

void lex::error_occur(char *msg, int l, int c) {
    printf("%s - %d %d\n", msg, l, c);
    exit(-1);
}

bool lex::isWS(char c) {
    return c == ' ' || c == '\n' || c == '\t';
}

bool lex::isOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool lex::isSymbol(char c) {
    return symbols.find(c) != symbols.end();
}

bool lex::isKeyword(string &in) {
    return keywords->find(in.c_str());
}

void lex::get_tok(string &s) {
    if(s.length() == 0) return;
    if(isKeyword(s))
        tokens.pb(token(s, KEYWORD, line, col, {0}));
    else if(identifier.accept(s))
        tokens.pb(token(s, ID, line, col, {0}));
    else if(integer.accept(s))
        tokens.pb(token(s, INTEGER, line, col, {.n = stoi(s)}));
    else if(float_number.accept(s))
        tokens.pb(token(s, FLOAT, line, col, {.f = stof(s)}));
}

void lex::analyze(string &filename) {
    init();

    source.open(filename);
    if(!source.is_open()) {
        printf("FILE ERROR\n");
        exit(-1);
    }

    char c;
    string tok = "";
    int el, ec;
    while(source) {
        get_char(c);
        if(isWS(c)) {
            get_tok(tok);
            tokens.pb(token("WS", WS, line, col, {0}));
        }
        else if(isSymbol(c)) {
            get_tok(tok);
            tokens.pb(token(symbols[c], SYMBOLS, line, col, {0}));
        }
        else if(isOp(c)) {
            get_tok(tok);
            tokens.pb(token(to_string(c), OP, line, col, {0}));
        }
        else if(c == '"') {
            get_tok(tok);
            string s;
            s += c;
            get_char(c);
            while(c != '"' && source) {
                if(c == '\n') error_occur("Invalid literal string format:", line, col);
                s += c;
            }
            s += c;
            char *text = (char *)calloc(s.length + 1, sizeof(char));
            for(int i = 0;i < s.length();++i) text[i] = s[i];
            tokens.pb(token("LITERAL STRING", LITERAL, el, ec, {.s = text}));
        }
        else
            tok += c;
    }

    FILE *out = fopen("output.txt", "w");
    for(auto t : tokens) {

    }
}
