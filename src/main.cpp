extern int yyparse();
#include "AST/AST.h"
extern Cedomp::AST::AbstractNode* root;
int main( int argc, char** argv )
{
	yyparse();
	root->printNode();
}
