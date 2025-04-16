#include "Parser.h"
#include "AST.h"

using namespace std;


/* 
 * Initiate parsing with the iterator and the right binding power at zero, and 'left' as nullptr.
 * After parsing all tokens, return the last instance of 'left' as the root of the AST. 
 */
ASTNode* Parser::parse(){

    int iterator = 0;
    ASTNode* left;

    while(iterator < tokens().size()){
        
        left = recursiveParse(iterator, 1, nullptr);
    }

    return left;
}

/*
 * Create node and update 'left', and evaluate the left binding power of the next token. 
 * Return the last instance of 'left' at the end of tokens or when rbp < lbp is not true.
 */
ASTNode* Parser::recursiveParse(int &iterator, int rbp, ASTNode* left){

    try{

        left = createNode(iterator, rbp, left);

        if(iterator >= tokens().size()){

            return left;
        }

        Token led = tokens().at(iterator); 
        int lbp = _M_tok_binding_power(led);
        
        if(lbp < 1){

            throw ParsingException("Cannot get lbp of '" + led.lexeme() + "' at position " + to_string(iterator) +  " \n");
        }

        while(rbp < lbp){

            left = createNode(iterator, lbp, left);

            if(iterator >= tokens().size()){
                break;
            }   

            led = tokens().at(iterator); 
            lbp = _M_tok_binding_power(led);
        }

        return left;
    }
    catch(ParsingException &e){

        cerr << "Parsing Error: " << e.what() << "\n";
    }
    catch(out_of_range& e)
    {
        cerr << "Out-of-range Error: " << e.what() << "\n";
        iterator--;
    }
    
    return nullptr; 
}

/* 
 * Create a node from current token, increment the iterator, and 
 * call recursive parse with the rbp of current token for nodes with children.
 * 
 * Throws parsing exceptions for syntax errors.
 */
ASTNode* Parser::createNode( int &iterator, int rbp, ASTNode* left){

    Token token = tokens().at(iterator++);

    if(_M_is_tok_literal(token)){

        if((iterator < tokens().size()) &&
          ((tokens().at(iterator).type() == _TOKEN_OPEN_PARENTHESES) || 
           (_M_is_tok_literal(tokens().at(iterator))))){

            throw ParsingException("Cannot follow '" + token.lexeme() +  "' with '" + tokens().at(iterator).lexeme() + "' at position " + to_string(iterator - 1) + "\n");
        }

        return new LiteralNode(token);
    }
    else if(token.type() == _TOKEN_OPEN_PARENTHESES){

        if(_M_is_tok_binary(tokens().at(iterator))){

            throw ParsingException("Cannot follow '(' with '" + tokens().at(iterator).lexeme() + "' at position " + to_string(iterator) + "\n");
        }

        /* parse the expression until parentheses get closed or reach end of tokens */
        
        do{

            left = recursiveParse(iterator, _M_tok_binding_power(token), left);

        }while((iterator < tokens().size()) && (tokens().at(iterator++).type() != _TOKEN_CLOSE_PARENTHESES));

        if(tokens().at(iterator - 1).type() != _TOKEN_CLOSE_PARENTHESES){

            throw ParsingException("Expected ')' at position " + to_string(iterator - 1) + ", got '" + tokens().at(iterator - 1).lexeme() + "'\n");
        }
        
        return left;
    }
    else if(_M_is_tok_unary(token)){

        if((iterator < tokens().size()) && _M_is_tok_binary(tokens().at(iterator))){

            throw ParsingException("Cannot follow '" + token.lexeme() +  "' with '" + tokens().at(iterator).lexeme() + "' at position " + to_string(iterator - 1) + "\n");
        }

        /* recursively get the node to which the prefix is applied */

        return new UnaryNode(token, recursiveParse(iterator, _M_tok_binding_power(token), left));
    }
    else if(_M_is_tok_binary(token)){

        if(left == nullptr){

            throw ParsingException("Binary operation '" + token.lexeme() + "' at position " + to_string(iterator - 1) + " is missing a left argument\n");
        }
        if((iterator < tokens().size()) && _M_is_tok_binary(tokens().at(iterator))){

            throw ParsingException("Cannot follow '" + token.lexeme() +  "' with '" + tokens().at(iterator).lexeme() + "' at position " + to_string(iterator - 1) + "\n");
        }

        /* recursively get the other node to which the binop is applied */

        return new BinaryNode(token, left, recursiveParse(iterator, _M_tok_binding_power(token), left));
    }

    throw ParsingException("Unknown character '" + token.lexeme() + "' at position " + to_string(iterator - 1) +  " \n");
    return nullptr;
}


