#include <map>
#include "Lexer.h"



void Lexer::lexify(){
    
    map<string, int> reserved_keywords {

        {"true", _TOKEN_LITERAL_TRUE},
        {"false", _TOKEN_LITERAL_FALSE},
        {"nil", _TOKEN_LITERAL_NIL},
        {"print", _TOKEN_STMT_PRINT},
        {"var", _TOKEN_DECLARATION_VAR},
        {"and", _TOKEN_LOGICAL_AND},
        {"or", _TOKEN_LOGICAL_OR}
    };

    char c;
    string buffer;

    int currentLine = 1;
    size_t streamLength = stream().length();

    for(int i = 0; i < streamLength; ){

        c = stream().at(i);
        
        switch(c){
            
            case '+': { addToken(Token(_TOKEN_BINOP_PLUS,        "+", currentLine)); break; }
            case '*': { addToken(Token(_TOKEN_BINOP_MUL,         "*", currentLine)); break; }
            case '(': { addToken(Token(_TOKEN_OPEN_PARENTHESES,  "(", currentLine)); break; }
            case ')': { addToken(Token(_TOKEN_CLOSE_PARENTHESES, ")", currentLine)); break; }
            case ';': { addToken(Token(_TOKEN_SEMICOLON,         ";", currentLine)); break; }
            case '=': { addToken(match('=', i) ? Token(_TOKEN_EQUAL_EQUAL,   "==", currentLine) : Token(_TOKEN_ASSIGNMENT_EQUAL, "=", currentLine)); break; }
            case '!': { addToken(match('=', i) ? Token(_TOKEN_BANG_EQUAL,    "!=", currentLine) : Token(_TOKEN_UNARY_BANG,       "!", currentLine)); break; }
            case '<': { addToken(match('=', i) ? Token(_TOKEN_LESS_EQUAL,    "<=", currentLine) : Token(_TOKEN_STRICTLY_LESS,    "<", currentLine)); break; }
            case '>': { addToken(match('=', i) ? Token(_TOKEN_GREATER_EQUAL, ">=", currentLine) : Token(_TOKEN_STRICTLY_GREATER, ">", currentLine)); break; }
            case '\n':{ currentLine++; break; }
            case ' ': 
            { 
                // ignore spaces 
                break; 
            }
            case '-': 
            { 
                if((i > 0) && (
                   (tokens().back().type() == _TOKEN_CLOSE_PARENTHESES) || 
                   (_M_is_tok_literal(tokens().back()))))
                {
                    addToken(Token(_TOKEN_BINOP_MINUS, "-", currentLine)); break; 
                }
                addToken(Token(_TOKEN_UNARY_MINUS, "-", currentLine)); break;
            }
            case '/': 
            { 
                // ignore comments
                if(match('/', i)){

                    while((c != '\n') && (c != '\0')){ 
                        
                        c = advance(i, streamLength); 
                    }

                    break;
                }
                
                addToken(Token(_TOKEN_BINOP_DIV, "/", currentLine)); 
                break; 
            }
            case '"':
            {
                buffer = "";

                do{

                    c = advance(i, streamLength);

                    if(c == '\0'){ 
                        
                        cerr << "Unterminated string\n"; 
                        return;
                    }
                    else if(c == '\n'){
                        
                        currentLine++;
                        continue;
                    }

                    buffer = buffer + c;

                } while( c != '"');

                addToken(Token(_TOKEN_LITERAL_STRING, buffer, currentLine));
                break;
            }
            default:  
            { 

                buffer = "";

                if(_M_is_digit(c)){

                    do{

                        buffer = buffer + c;

                        c = advance(i, streamLength);

                        if(c == '\0'){ 

                            break; 
                        }
                        else if(c == '.'){

                            buffer = buffer + c;

                            c = advance(i, streamLength);

                            while(_M_is_digit(c)){

                                buffer = buffer + c;

                                c = advance(i, streamLength);

                                if(c == '\0'){ return; }
                            }
                        }
                    } while(_M_is_digit(c));

                    addToken(Token(_TOKEN_LITERAL_NUMBER, buffer, currentLine));
                    continue;
                }
                else if(_M_is_alpha(c)){

                    do{

                        buffer = buffer + c;

                        if(c = advance(i, streamLength); c == '\0') { break; }

                    } while(_M_is_alpha(c) || _M_is_digit(c));

                    if(auto search = reserved_keywords.find(buffer); search != reserved_keywords.end()){

                        addToken(Token(search->second, search->first, currentLine));
                    }
                    else{

                        addToken(Token(_TOKEN_IDENTIFIER, buffer, currentLine));
                    }

                    continue;
                }
                else{

                    addToken(Token(_TOKEN_UNKNOWN, string(1, c), currentLine));
                    cerr << "Unknown token '" + string(1, c) + "'\n";
                }
            }
        }

        i++;
    }
}

char Lexer::advance(int &iterator, int streamLength){

    if (++iterator >= streamLength) {
        return '\0';
    }

    return stream().at(iterator);
}

bool Lexer::match(char second, int &iterator){

    if(stream().at(iterator + 1) != second){

        return false;
    }

    iterator++;
    return true;
}


void Lexer::printTokens() {

    cout << "Token type, lexeme\n";

    for (auto token: tokens()) {

        cout << token.tok2str() + "\n";

    }
}