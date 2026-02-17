// S →(L) | a
// L → L,S | S

//without left recusrion
// S →(L) | a
// L → SL'
// L' -> ,SL' | epsilon

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ptr = 0;
char str[100];

void S();
void L();
void Lprime();

void reject() {
    printf("ERROR. String Rejected.\n");
    exit(0);
}
void accept(){
    printf("SUCCESS. String Accepted.\n");
    exit(0);
}

void S(){
    if(str[ptr] == '('){
        ptr++;
        L();
        if(str[ptr] == ')'){
            ptr++;
            return;
        }else reject();
    }
    else if(str[ptr] == 'a'){
        ptr++;
        return;
    }
    else reject();
}

void L(){
    S();
    Lprime();
}

void Lprime(){
    if(str[ptr] == ','){
        ptr++;
        S();
        Lprime();
    }
    return;
}

int main(){
    printf("Enter string: ");
    scanf("%s", str);
    S();
    if(str[ptr] == '$') accept();
    else reject();
}

/*
OUTPUT
------
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ gcc l6q4.c -o l6q4
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q4
Enter string: ((a,a),a)$
SUCCESS. String Accepted.
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q4
Enter string: ((a,a),)$
ERROR. String Rejected.
*/


