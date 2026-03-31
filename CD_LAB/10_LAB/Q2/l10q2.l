%{
#include "l10q2.tab.h"
%}

%%
"if"                    { return IF; }
"else"                  { return ELSE; }
[a-zA-Z][a-zA-Z0-9_]* { return ID; }
[0-9]+                  { return NUM; }
"<="|">="|"=="|"!="      { return RELOP; }
[<>]                    { return RELOP; }
\n                      { return NL; } /* The Enter key trigger */
[ \t]                   { /* skip whitespace */ }
.                       { return yytext[0]; }
%%

int yywrap() { return 1; }