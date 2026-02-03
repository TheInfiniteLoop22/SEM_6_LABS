%{
#include <stdio.h>

int scanCount = 0;
int printCount = 0;

FILE *yyin, *yyout;
%}

%%
"scanf"        { scanCount++; fprintf(yyout, "READ"); }
"printf"       { printCount++; fprintf(yyout, "WRITE"); }
.|\n           { fprintf(yyout, "%s", yytext); }
%%

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <inputfile> <outputfile>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin)
    {
        perror("Input file open failed");
        return 1;
    }

    yyout = fopen(argv[2], "w");
    if (!yyout)
    {
        perror("Output file open failed");
        return 1;
    }

    yylex();

    fclose(yyin);
    fclose(yyout);

    printf("Number of scanf: %d\n", scanCount);
    printf("Number of printf: %d\n", printCount);

    return 0;
}

int yywrap()
{
    return 1;
}

