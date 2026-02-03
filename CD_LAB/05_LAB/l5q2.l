%{
#include <stdio.h>
#include <string.h>

int charCount = 0;
int wordCount = 0;
int lineCount = 0;
int blankCount = 0;
%}

%%
[a-zA-Z]+      { wordCount++; charCount += strlen(yytext); }
\n             { lineCount++; charCount++; }
[ \t]          { blankCount++; charCount++; }
.              { charCount++; }
%%

int main()
{
    yylex();
    printf("Lines: %d\n", lineCount);
    printf("Words: %d\n", wordCount);
    printf("Characters: %d\n", charCount);
    printf("Blanks: %d\n", blankCount);
    return 0;
}

int yywrap()
{
    return 1;
}
