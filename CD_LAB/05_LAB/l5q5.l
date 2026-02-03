%{
#include <stdio.h>
#include <stdlib.h>

void printHex(int n)
{
    char hex[20];
    int i = 0, r;

    if(n == 0)
    {
        printf("Hex value: 0\n");
        return;
    }

    while(n > 0)
    {
        r = n % 16;

        if(r < 10)
            hex[i++] = r + '0';
        else
            hex[i++] = r - 10 + 'A';

        n = n / 16;
    }

    printf("Hex value: ");

    for(int j = i-1; j >= 0; j--)
        printf("%c", hex[j]);

    printf("\n");
}
%}

%%
[0-9]+      { printHex(atoi(yytext)); }
.|\n        { }
%%

int main()
{
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}

