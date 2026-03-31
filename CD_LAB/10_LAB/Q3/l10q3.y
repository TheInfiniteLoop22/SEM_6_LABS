%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(char *s);
%}

%token NUMBER NL
/* Standard math precedence: * and / are higher than + and - */
%left '+' '-'
%left '*' '/'

%%
/* $1 refers to the value of the 'exp' result */
stmt: exp NL { printf("Result: %d\n", $1); exit(0); }
    ;

exp: exp '+' exp { $$ = $1 + $3; }
   | exp '-' exp { $$ = $1 - $3; }
   | exp '*' exp { $$ = $1 * $3; }
   | exp '/' exp { 
        if($3 == 0) { 
            printf("Error: Division by zero\n"); 
            exit(0); 
        } else {
            $$ = $1 / $3; 
        }
     }
   | '(' exp ')' { $$ = $2; }
   | NUMBER      { $$ = $1; }
   ;
%%

void yyerror(char *s) {
    printf("Invalid Expression\n");
    exit(0);
}

int main() {
    printf("Enter arithmetic expression: ");
    yyparse();
    return 0;
}