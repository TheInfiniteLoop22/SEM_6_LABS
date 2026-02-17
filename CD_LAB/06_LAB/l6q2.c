/*
S→UVW
U →(S) | aSb | d
V → aV | 𝜖
W → cW | 𝜖

NO LEFT RECUSRION
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ptr = 0;
char str[100];
void S();
void U();
void V();
void W();

void reject() {
    printf("ERROR. String Rejected.\n");
    exit(0);
}
void accept(){
    printf("SUCCESS. String Accepted.\n");
    exit(0);
}
void S(){
    U();
    V();
    W();
}
void U(){
    if(str[ptr] == '('){
        ptr++;
        S();
        if(str[ptr] == ')'){
            ptr++;
            return;
        }else reject();
    }
    else if(str[ptr] == 'a'){
        ptr++;
        S();
        if(str[ptr] == 'b'){
            ptr++;
            return;
        }else reject();
    }
    else if(str[ptr] == 'd') {
        ptr++;
        return;
    }
    else reject();
}
void V(){
    if(str[ptr] == 'a'){
        ptr++;
        V();
    }
    return;
}
void W(){
    if(str[ptr] == 'c'){
        ptr++;
        W();
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
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ gcc l6q2.c -o l6q2
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q2
Enter string: d$
SUCCESS. String Accepted.
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q2
Enter string: daaaaccc$
SUCCESS. String Accepted.
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q2
Enter string: adb$
SUCCESS. String Accepted.
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q2
Enter string: (ad$
ERROR. String Rejected.
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q2
Enter string: ad$
ERROR. String Rejected.
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q2
Enter string: dcaa$
ERROR. String Rejected.
*/
