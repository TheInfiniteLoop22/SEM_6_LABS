%{
#include <stdio.h>
#include <stdlib.h>
%}

%token NUMBER ID NL
%left '+' '-'
%left '*' '/'

%%
stmt: exp NL { printf("Valid Expression\n"); exit(0); }
    ;

exp: exp '+' term | exp '-' term | term
   ;

term: term '*' factor | term '/' factor | factor
    ;

factor: ID | NUMBER
      ;
%%

int yyerror(char *msg) {
    printf("Invalid Expression\n");
    exit(0);
}

void main() {
    printf("Enter the expression: ");
    yyparse();
}