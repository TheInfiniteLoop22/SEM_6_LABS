%{
#include "l10q3.tab.h"
extern int yylval; 
%}

%%
[0-9]+          { yylval = atoi(yytext); return NUMBER; }
\n              { return NL; }
[ \t]           { /* skip whitespace */ }
.               { return yytext[0]; }
%%

int yywrap() { return 1; }