extern int yyparse();
#include "AST/AST.h"
extern Cedomp::AST::AbstractNode* root;
extern FILE * yyin;
int main( int argc, char** argv )
{
	if(argc >= 2)
	{
		yyin = fopen(argv[1], "r");
	}
	yyparse();
	root->printNode();
}
