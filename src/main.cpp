#include <iostream>
#include <string>
#include "./lexer/Lexer.h"
#include "Parser.h"
#include "AST.h"

using namespace std;

int main() {

    /* expression to be evaluated */

    string text = "1 + 2 / 5 * (2.5 + 1)";

    // tokenize the text

    tokenList tokens;

    Lexer lexer(text, tokens);

    lexer.lexify();
    lexer.printTokens();

    // parse the tokens 
    
    Parser parser(tokens);

    ASTNode* tree = parser.parse();

    // evaluate the result
    
    EvaluatingVisitor visitor;

    visitor.evaluateExpression(tree);
    visitor.printResult();

    return 0;
}