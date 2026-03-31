%{
#include "l10q1.tab.h" /* Matches the generated header filename */
%}

%%
"int"|"float"|"char"|"double" { return TYPE; }
[a-zA-Z][a-zA-Z0-9_]* { return ID; }
","                           { return COMMA; }
";"                           { return SC; }
[ \t\n]                       { /* Skip whitespace */ }
.                             { return yytext[0]; }
%%

int yywrap() {
    return 1;
}