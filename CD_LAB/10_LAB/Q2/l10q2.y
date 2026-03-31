%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(char *s);
%}

%token IF ELSE ID NUM RELOP NL

%%
/* The 'NL' at the end makes it process as soon as you hit Enter */
start: if_stmt NL { printf("Valid Decision Making Statement\n"); exit(0); }
     ;

if_stmt: IF '(' cond ')' '{' body '}' 
       | IF '(' cond ')' '{' body '}' ELSE '{' body '}'
       ;

cond: ID RELOP ID 
    | ID RELOP NUM
    ;

body: ID ';' 
    | /* empty body */
    ;
%%

void yyerror(char *s) {
    printf("Invalid Decision Making Statement\n");
    exit(0);
}

int main() {
    printf("Enter the if statement: ");
    yyparse();
    return 0;
}