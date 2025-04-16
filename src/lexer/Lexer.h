#include <vector>
#include "Token.h"

#ifndef __H_LEXER
#define __H_LEXER

#define _M_is_digit(c) ( (c >= '0') && (c <= '9') )
#define _M_is_alpha(c) (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) || (c == '_'))

#define _M_is_tok_binary(token)  ((0x000f & token.type()) > 0)
#define _M_is_tok_literal(token) ((0x00f0 & token.type()) > 0)
#define _M_is_tok_unary(token)   ((0x0f00 & token.type()) > 0)
    
using namespace std;

typedef vector<Token> tokenList;

class Lexer{

public:

    /* Constructor */
    Lexer(string stream, tokenList &tokens): _stream(stream), _tokens(tokens) {}

    /* getters */
    const string stream() const { return _stream; }
    tokenList& tokens()         { return _tokens; }

    /* actions */
    void lexify();
    void printTokens();

    /* helpers */
    
    void addToken(Token tok) { tokens().push_back(Token(tok)); }
    char advance(int &iterator, int streamLength);
    bool match(char second, int &iterator);

    
private:

    string _stream;
    tokenList &_tokens;
};

#endif