%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(char *s);
%}

%token NUM NL

%%
/* We simplified this to process one line and then exit */
start: exp NL { printf("Result: %d\n", $1); exit(0); }
     ;

/* Postfix rules from your lab manual */
exp: NUM           { $$ = $1; }
   | exp exp '+'   { $$ = $1 + $2; }
   | exp exp '-'   { $$ = $1 - $2; }
   | exp exp '*'   { $$ = $1 * $2; }
   | exp exp '/'   { 
        if($2 == 0) { 
            printf("Error: Division by zero\n"); 
            exit(0); 
        } else {
            $$ = $1 / $2; 
        }
     }
   | exp 'n'       { $$ = -$1; }
   ;
%%

void yyerror(char *s) {
    printf("Invalid Postfix Expression\n");
    exit(0);
}

int main() {
    printf("Enter postfix expression: ");
    yyparse();
    return 0;
}