%{
    #include <string>
    #include <vector>
    #include <map>
    #include <iostream>
    extern int yylex();
    extern int yyparse();
    extern void yyerror(const char* s, ...);
    using std::cout;
    using std::endl;
%}



%union {
    double* floattype;
    long* inttype;
    std::string* strtype;
    std::vector<void*>* listtype;
    std::map<std::string, void*>* maptype;
    char* id;
}

%token T_DEF T_END T_RETURN T_FOR T_IF T_MAP T_LIST T_TRUE T_FALSE T_AND T_XOR T_OR T_MOD T_NOT T_STRING T_ID T_INT T_FLOAT
%token T_SEMICOLON T_COMMA T_LEFT_PAR T_RIGHT_PAR T_LEFT_BRACKET T_RIGHT_BRACKET T_EQUALS T_DIFFERENT T_GREATER_EQUAL T_LESS_EQUAL T_ASSIGN
%token T_GREATER T_LESS T_COLON T_PLUS T_STAR T_SLASH T_MINUS T_ERROR

%type<strtype> T_STRING
%type<inttype> T_INT
%type<id> T_ID
%type<floattype> T_FLOAT
%type<maptype> T_MAP
%type<listtype> T_LIST

%%

head:
statements
{
}
;

statements:
statements statement
{
}
|
statement
{
}
;

statement:
T_STRING
{
    cout << "string" << endl;
    cout << *$1 << endl;
}
|
T_DEF 
{
    cout << "def" << endl;
}
|
T_END
{
    cout << "end" << endl;
}
|
T_RETURN
{
    cout << "return" << endl;
}
|
T_FOR
{
    cout << "for" << endl;
}
|
T_IF
{
    cout << "if" << endl;
} 
|
T_MAP
{
    cout << "map" << endl;
}
| 
T_LIST
{
    cout << "list" << endl;
}
|
T_TRUE
{
    cout << "true" << endl;
}
|
T_FALSE
{
    cout << "false" << endl;
}
|
T_AND
{
    cout << "and" << endl;
}
|
T_XOR
{
    cout << "xor" << endl;
}
|
T_OR
{
    cout << "or" << endl;
}
|
T_MOD
{
    cout << "mod" << endl;
}
|
T_NOT
{
    cout << "not" << endl;
}
|
T_ID
{
    cout << "id" << endl;
    cout << $1 << endl;
}
|
T_INT
{
    cout << "int" << endl;
    cout << *$1 << endl;
}
|
T_FLOAT
{
    cout << "float" << endl;
    cout << *$1 << endl;
}
|
T_SEMICOLON 
{
    cout << "semicolon" << endl;
}
|
T_COMMA
{
    cout << "comma" << endl;
}
|
T_LEFT_PAR
{
    cout << "left par" << endl;
} 
|
T_RIGHT_PAR
{
    cout << "right par" << endl;
}
|
T_LEFT_BRACKET
{
    cout << "left bracket" << endl;
}
|
T_RIGHT_BRACKET
{
    cout << "right bracket" << endl;
}
|
T_EQUALS
{
    cout << "equals" << endl;
}
|
T_DIFFERENT
{
    cout << "different" << endl;
}
|
T_ERROR
{
}
|
T_GREATER_EQUAL
{
    cout << "greater equal" << endl;
}
|
T_LESS_EQUAL
{
    cout << "less equal" << endl;
}
|
T_ASSIGN
{
    cout << "assign" << endl;
}
|
T_GREATER
{
    cout << "greater" << endl;
}
| 
T_LESS
{
    cout << "less" << endl;
}
| 
T_COLON
{
    cout << "colon" << endl;
} 
|
T_PLUS
{
    cout << "plus" << endl;
}
|
T_STAR 
{
    cout << "star" << endl;
}
|
T_SLASH
{
    cout << "slash" << endl;
}
|
T_MINUS
{
    cout << "minus" << endl;
}
;


%%
