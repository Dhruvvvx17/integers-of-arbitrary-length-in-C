#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "intal.h"

// Function declarations
char* padding(const char* intalTemp, int zeros, int new_length);
char* stripZeros(const char* intalTemp);


char* padding(const char* intalTemp, int zeros, int new_length){
    char *res;
    res = (char*)malloc(sizeof(char)*new_length+1);
    int k=0;
    for(int i=0;i<zeros;i++){
        res[k] = '0';
        k++;
    }
    for(int i=0;i<strlen(intalTemp);i++){
        res[k] = intalTemp[i];
        k++;
    }
    res[k] = '\0';
    return res;
}


char* stripZeros(const char* intalTemp){

    int initial_zeros = 0;
    for(int i=0; i<strlen(intalTemp); i++){
        if(intalTemp[i]=='0')
            initial_zeros++;
        else
            break;
    } 

    int new_len = strlen(intalTemp) - initial_zeros, k = 0;
    char* res;
    res = (char*)malloc(sizeof(char)*(new_len+1));
    
    for(int i=initial_zeros; i<strlen(intalTemp); i++){
        res[k] = intalTemp[i];
        k++;
    }
    res[new_len] = '\0';
    return res;
}

char* intal_add(const char* intal1, const char* intal2){

    // printf("Intal1: %s\n",intal1);    
    // printf("\tLength: %d\n",strlen(intal1));

    // printf("Intal2: %s\n",intal2);
    // printf("\tLength: %d\n",strlen(intal2));

    int l1, l2, diff_len, res_len;
    l1 = strlen(intal1);    
    l2 = strlen(intal2);    

    diff_len = (l1>l2) ? (l1-l2) : (l2-l1);

    // printf("DIFF %d\n",diff_len);

    if(l1>l2){
        intal2 = padding(intal2,diff_len,l1);
        res_len = l1;
        l2 = l1;
    }

    else if(l2>l1){
        intal1 = padding(intal1,diff_len,l2);
        res_len = l2;
        l1 = l2;
    }

    char *res;
    res = (char*)malloc(sizeof(char)*(res_len+2));

    int i, j, d1, d2, sum, carry = 0, k=res_len;

    for(i=l1-1,j=l2-1; i>=0; i--,j--){
        d1 = intal1[i] - '0';
        d2 = intal2[j] - '0';
        sum = d1 + d2 + carry;
        carry = sum / 10;
        sum = sum % 10;
        res[k] = sum + '0';
        k--;
    }
    res[0] = carry + '0';
    res[res_len+1] = '\0';

    // printf("Temp Sum: %s\n",res);
    // printf("Temp len: %d\n",strlen(res));

    res = stripZeros(res);

    // printf("Temp Sum after zeros are stripped: %s\n",res);
    // printf("Temp len: %d\n",strlen(res));

    return res;    
}