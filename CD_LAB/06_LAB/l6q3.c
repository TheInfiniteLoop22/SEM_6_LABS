// S→aAcBe
// A→Ab|b
// B→d

//without left recusrion
// S→aAcBe
// A→bA'
// A'-> bA'| epsilon
// B→d

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ptr = 0;
char str[100];
void S();
void A();
void Aprime();
void B();

void reject() {
    printf("ERROR. String Rejected.\n");
    exit(0);
}
void accept(){
    printf("SUCCESS. String Accepted.\n");
    exit(0);
}

void S(){
    if(str[ptr] == 'a'){
        ptr++;
        A();
        if(str[ptr] == 'c'){
            ptr++;
            B();
            if(str[ptr] == 'e'){
                ptr++;
                return;
            }else reject();
        }else reject();
    }else reject();
}

void A(){
    if(str[ptr] == 'b'){
        ptr++;
        Aprime();
    }else reject();
}

void Aprime(){
    if(str[ptr] == 'b'){
        ptr++;
        Aprime();
    }
    return;
}

void B(){
    if(str[ptr] == 'd'){
        ptr++;
        return;
    }
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
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ gcc l6q3.c -o l6q3
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q3
Enter string: abcde$
SUCCESS. String Accepted.
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q3
Enter string: abbcde$
SUCCESS. String Accepted.
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q3
Enter string: abbbcde$
SUCCESS. String Accepted.
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q3
Enter string: acde$
ERROR. String Rejected.
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q3
Enter string: abccde$
ERROR. String Rejected.
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q3
Enter string: abbcd$
ERROR. String Rejected.
*/

