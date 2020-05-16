#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "intal.h"

// Function declarations
char* padding(const char* intalTemp, int zeros, int new_length);
char* stripZeros(const char* intalTemp);


// Padding the given string with prefix zeros to make the new length equal to the given length
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

// Removing any prefix zeros from the given string
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
    int l1, l2, diff_len, res_len;
    l1 = strlen(intal1);    
    l2 = strlen(intal2);    

    diff_len = (l1>l2) ? (l1-l2) : (l2-l1);

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

    int i, j, d1, d2, sum, carry=0, k=res_len;

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

    //removing extra zeros from the result string, freeing any extra allocated memory
    char *t1, *t2;
    t1 = stripZeros(res);
    t2 = res;
    res = t1;
    free(t2);
    return res;    
}


int intal_compare(const char* intal1, const char* intal2){
    int l1, l2;
    l1 = strlen(intal1);
    l2 = strlen(intal2);

    if(l1>l2)
        return 1;

    if(l2>l1)
        return -1;

    for(int i=0; i<l1; i++){
        if(intal1[i]>intal2[i])
            return 1;
        if(intal2[i]>intal1[i])
            return -1;
    }
    return 0;
}


char* intal_diff(const char* intal1, const char* intal2){
    int l1, l2, cmp, diff_len, res_len;
    l1 = strlen(intal1);
    l2 = strlen(intal2);

    diff_len = (l1>l2) ? (l1-l2) : (l2-l1);

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

    cmp = intal_compare(intal1,intal2);
    if(cmp == -1){
        const char *temp;
        temp = intal1;
        intal1 = intal2;
        intal2 = temp;
    }
    else if(cmp == 0){
        char *res;
        res = (char*)malloc(sizeof(char)*(2));
        res[0] = '0';
        res[1] = '\0';
        return res;
    }

    char *res;
    res = (char*)malloc(sizeof(char)*(res_len+1));

    int i, j, d1, d2, diff, carry=0, k=res_len-1;

    for(i=l1-1,j=l2-1; i>=0; i--,j--){
        d1 = intal1[i] - '0';
        d2 = intal2[i] - '0';
        diff = d1 - d2 - carry;
        if(diff<0){
            diff = diff + 10;
            carry = 1;
        }
        else{
            carry = 0;
        }

        res[k] = diff + '0';
        k--;
    }
    res[res_len] = '\0';

    //removing extra zeros from the result string, freeing any extra allocated memory
    char *t1, *t2;
    t1 = stripZeros(res);
    t2 = res;
    res = t1;
    free(t2);
    return res;
}