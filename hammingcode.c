#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LEN 1000
void GetHammingcode();
void hamming(char data[], int *len, int paritytype);
void insert(char data[], int index, char c, int *len);
void updatecode(char data[], int index, int c);
void CorrectHammingcode();
void correct(char data[], int paritytype, int len);
int GetP_i(char data[], int i, int len);
int isPowerof2(int num);

int main(){
    while(1){
        printf("\n\nPlease choose function: \n");
        printf("(1. generate hamming code from given binary data  2. generate original data from given hamming code)\n");
        int func;
        scanf("%d", &func);
        getchar();
        switch (func){
            case 1:
                GetHammingcode();
                break;
            
            case 2:
                CorrectHammingcode();
                break;
        }
        printf("\n\nContinue? (Y: yes, continue  N: no, quit)\n");
        char c;
        getchar();
        scanf("%c", &c);
        getchar();
        if(c=='N') break;
    }
}

void GetHammingcode(){
    printf("Please input original data(e.g. 1010): \n");
    char data[MAX_LEN]="";
    scanf("%s", &data);
    int *len=malloc(sizeof(int));
    *len=strlen(data);
    printf("Please input type of parity bit(s): \n(1. even perity bit(s)   2. odd parity bit(s)):\n");
    int paritytype;
    scanf("%d", &paritytype);
    hamming(data, len, paritytype);
    printf("\n\nResult: \n%s\n", data);
}

void hamming(char data[], int *len, int paritytype){
    int n=strlen(data);
    int k;

    // calculate k, which is the total number of parity bit(s)
    for(k=0; pow(2, k)<n+k+1; k++) ;
    int i;

    // insert blank positions of parity bit(s)
    for(i=0; pow(2, i)<=n+k; i++){
        insert(data, (int)pow(2, i)-1, 0, len);
    }

    // calculate actual value of parity bit(s)
    for(i=0; i<n+k; i++){
        if(data[i]!=0 && data[i]!=1){
            updatecode(data, i, data[i]-'0');
        }
    }

    // get final output
    for(i=0; i<n+k; i++){
        if(data[i]==0 || data[i]==1){
            if(paritytype == 2) data[i]=data[i] ^ 1;
            data[i]+='0';
        }
    }
}

void insert(char data[], int index, char c, int *len){
    // index: counts from 0
    int i=*len;
    while(i+1!=index){
        char ch=data[i];
        data[i+1]=ch;
        i--;
    }
    i++;
    data[i]=c;
    (*len)++;
    return;
}

void updatecode(char data[], int index, int c){
    index++;
    int rem, counter=0;
    while(index!=0){
        rem = index%2;
        if(rem) {
            int chindex=(int)(pow(2, counter)-1);
            char ch=data[chindex] ^ c;
            data[chindex]=ch;
        }
        index /= 2;
        counter++;
    }
}

void infuncprint(char data[], int len){
    int i=0;
    while(i!=len) {
        printf("%c", (data[i] == 0 || data[i] == 1) ? data[i]+'0' : data[i]);
        i++;
    }
    printf("\n");
}

void CorrectHammingcode(){
    printf("Please input the hamming code(e.g. 11101001101): \n");
    char data[MAX_LEN]="";
    scanf("%s", &data);
    printf("Please input type of parity bit(s): \n(1. even perity bit(s)   2. odd parity bit(s)):\n");
    int paritytype;
    scanf("%d", &paritytype);
    int len=strlen(data);
    correct(data, paritytype, len);
    // printf("Original data is: \n");
}

void correct(char data[], int paritytype, int len){
    int count=0;
    int i;
    int to_be_corrected=0;
    for(i=0; pow(2, i)<=len; i++){
        int pi=GetP_i(data, i, len);
        if(paritytype == 2) pi=pi^1;
        to_be_corrected += pi << i;
    }
    if(to_be_corrected){
        if(data[to_be_corrected-1]=='0') data[to_be_corrected-1]='1';
        else data[to_be_corrected-1]='0';
    }
    printf("\n\nOriginal data: \n");
    for(i=0;i<len;i++){
        if(!isPowerof2(i+1)) printf("%c", data[i]);
    }
    printf("\n");
}

int GetP_i(char data[], int i, int len){
    int j;
    int pi=0;
    int power=(int)pow(2, i);
    for(j=0; j<len; j++){
        int condition=((j+1) == power) || (((j+1)>>i)%2 == 1);
        if(!condition) continue;
        pi ^= data[j]-'0';
    }
    return pi;
}

int isPowerof2(int num){
    int i;
    for(i=0; pow(2, i)<=num; i++){
        if(pow(2, i)==num) return 1;
    }
    return 0;
}