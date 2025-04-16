#include <string>
#include <iostream>

#ifndef __H_TOKEN
#define __H_TOKEN


/* Binary Operation Tokens 
*/
#define _TOKEN_BINOP_PLUS        0x0001
#define _TOKEN_BINOP_MINUS       0x0002
#define _TOKEN_BINOP_MUL         0x0003
#define _TOKEN_BINOP_DIV         0x0004
#define _TOKEN_EQUAL_EQUAL       0x0005
#define _TOKEN_BANG_EQUAL        0x0006
#define _TOKEN_LESS_EQUAL        0x0007
#define _TOKEN_GREATER_EQUAL     0x0008
#define _TOKEN_STRICTLY_LESS     0x0009
#define _TOKEN_STRICTLY_GREATER  0x000a
#define _TOKEN_LOGICAL_OR        0x000b
#define _TOKEN_LOGICAL_AND       0x000c

/* Literals and Identifier Tokens
*/
#define _TOKEN_LITERAL_NUMBER    0x0010
#define _TOKEN_LITERAL_STRING    0x0020
#define _TOKEN_LITERAL_TRUE      0x0030
#define _TOKEN_LITERAL_FALSE     0x0040
#define _TOKEN_IDENTIFIER        0x0050
#define _TOKEN_LITERAL_NIL       0x0060

/* Unary Operation Tokens
*/
#define _TOKEN_UNARY_MINUS       0x0100
#define _TOKEN_UNARY_BANG        0x0200

/* Special Tokens
*/
#define _TOKEN_OPEN_PARENTHESES  0x1000
#define _TOKEN_CLOSE_PARENTHESES 0x2000
#define _TOKEN_ASSIGNMENT_EQUAL  0x3000
#define _TOKEN_SEMICOLON         0x4000
#define _TOKEN_STMT_PRINT        0x5000
#define _TOKEN_DECLARATION_VAR   0x6000
#define _TOKEN_UNKNOWN           0xffff

using namespace std;


class Token{

public:

    /* Constructor */
    Token(int type, string lexeme, int line): _type(type), _lexeme(lexeme), _line(line) {}

    /* getters */
    const int type() const { return _type; }
    const string lexeme() const { return _lexeme; }
    const int line() const { return _line; }

    string tok2str() { return(to_string(type()) + ", " + lexeme()); }

private:

    int _type;
    string _lexeme;
    int _line;

};

#endif