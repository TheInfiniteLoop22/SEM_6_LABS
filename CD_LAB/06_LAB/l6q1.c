/*
S→a | > | ( T )
T→T, S|S

After removing left recursion
S→a | > | ( T )
→ST'
T'-> ,ST'| epsilon

*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ptr=0;
char str[100];

void S();
void T();
void Tprime();

void reject(){
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
        return;
    }
    else if(str[ptr] == '>'){
        ptr++;
        return;
    }
    else if(str[ptr] == '('){
        ptr++;
        T();
        if(str[ptr] == ')'){
            ptr++;
            return;
        }
        else reject();
    }
    else reject();
}

void T(){
   S();
   Tprime();
}

void Tprime(){
    if(str[ptr] == ','){
        ptr++;
        S();
        Tprime();
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
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ gcc l6q1.c -o l6q1
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q1
Enter string: ((a,a),a)$
SUCCESS. String Accepted.
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q1
Enter string: (a,>,a)$
SUCCESS. String Accepted.
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q1
Enter string: (a,)$
ERROR. String Rejected.
CD_A1@CL3-02:~/Desktop/230905010_DevadathanNR_CS_A1/06_LAB$ ./l6q1
Enter string: (a,a$
ERROR. String Rejected.
*/
