%{
#include <stdio.h>
#include <stdlib.h>

/* Declarations to prevent compiler warnings */
int yylex();
void yyerror(char *s);
%}

%token TYPE ID COMMA SC

%%
/* Grammar Rules */
start: TYPE list SC { printf("Valid Declaration\n"); exit(0); }
     ;

list: ID
    | ID COMMA list
    ;
%%

void yyerror(char *msg) {
    printf("Invalid Declaration\n");
    exit(0);
}

int main() {
    printf("Enter the declaration statement: ");
    yyparse();
    return 0;
}