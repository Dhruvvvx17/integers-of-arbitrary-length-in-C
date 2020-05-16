#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "intal.h"

// Helper Function declarations
static char* padding(const char* intalTemp, int zeros, int new_length);
static char* stripZeros(const char* intalTemp);


// Padding the given string with prefix zeros to make the new length equal to the given length
static char* padding(const char* intalTemp, int zeros, int new_length){
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
static char* stripZeros(const char* intalTemp){

    //check if the string contains all zeros, in which case a single character 0 should be returned
    int check = 1;      // temporary variable to check if the string is all zeros
    for(int i=0; i<strlen(intalTemp); i++){
        if(intalTemp[i] != '0'){
            check = 0;
            break;
        }
    }
    if(check){
        char *res = (char*)malloc(sizeof(char)*2);
        res[0] = '0';
        res[1] = '\0';
        return res;
    }

    //as it is confirmed that the string contains characters other than all zeros,
    //removing all preceeding zeros from the string 
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


// 1. INTAL_ADD: Function to add two intal numbers
char* intal_add(const char* intal1, const char* intal2){
    int l1, l2, diff_len, res_len;
    l1 = strlen(intal1);    
    l2 = strlen(intal2);    

    diff_len = (l1>l2) ? (l1-l2) : (l2-l1);

    char *new_intal1,*new_intal2;   //variables to create copies of intal1 and intal2

    if(l1>l2){
        new_intal1 = strdup(intal1);
        new_intal2 = padding(intal2,diff_len,l1);
        res_len = l1;
        l2 = l1;
    }
    else if(l2>l1){
        new_intal1 = padding(intal1,diff_len,l2);
        new_intal2 = strdup(intal2);
        res_len = l2;
        l1 = l2;
    }
    else{
        new_intal1 = strdup(intal1);
        new_intal2 = strdup(intal2);
        res_len = l1;
    }

    char *res;
    res = (char*)malloc(sizeof(char)*(res_len+2));

    int i, j, d1, d2, sum, carry=0, k=res_len;

    for(i=l1-1,j=l2-1; i>=0; i--,j--){
        d1 = new_intal1[i] - '0';
        d2 = new_intal2[j] - '0';
        sum = d1 + d2 + carry;
        carry = sum / 10;
        sum = sum % 10;
        res[k] = sum + '0';
        k--;
    }
    res[0] = carry + '0';
    res[res_len+1] = '\0';

    //removing extra zeros from the result string
    char *t1, *t2;
    t1 = stripZeros(res);
    t2 = res;
    res = t1;

    //free up any extra allocated memory
    //t2 points to the result which might have preceeding zeros, hence its memory has to be freed
    free(t2);
    //the original intal1 and intal2 are unaltered
    //either of intal1 or intal2 might be padded with 0s, the other is copied by strdup() 
    free(new_intal1);       
    free(new_intal2);       
    
    return res;    
}


// 2. INTAL_COMPARE: Function to compare two intal numbers
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


// 3. INTAL_DIFF: Function to subtract the larger intal number from the smaller intal number
char* intal_diff(const char* intal1, const char* intal2){
    int l1, l2, cmp, diff_len, res_len;
    l1 = strlen(intal1);
    l2 = strlen(intal2);

    diff_len = (l1>l2) ? (l1-l2) : (l2-l1);

    char* new_intal1, *new_intal2;      //variables to create copies of intal1 and intal2

    if(l1>l2){
        new_intal1 = strdup(intal1);
        new_intal2 = padding(intal2,diff_len,l1);
        res_len = l1;
        l2 = l1;
    }
    else if(l2>l1){
        new_intal1 = padding(intal1,diff_len,l2);
        new_intal2 = strdup(intal2);
        res_len = l2;
        l1 = l2;
    }
    else{
        new_intal1 = strdup(intal1);
        new_intal2 = strdup(intal2);
        res_len = l1;
    }

    //value comparison, lengths are same after padding 
    cmp = intal_compare(new_intal1,new_intal2);
    if(cmp == -1){
        //swapping to maintain the order of new_intal1 having the larger value number
        char *temp;
        temp = new_intal1;
        new_intal1 = new_intal2;
        new_intal2 = temp;
    }
    else if(cmp == 0){
        //if both are equal in length and value, then difference is 0. Hence, returning null terminated 0.
        char *res;
        res = (char*)malloc(sizeof(char)*(2));
        res[0] = '0';
        res[1] = '\0';
        // free up any extra memory allocated
        // new_intal1 and new_intal2 are copies of original intal's, have to be freed 
        free(new_intal1);
        free(new_intal2);
        return res;
    }

    char *res;
    res = (char*)malloc(sizeof(char)*(res_len+1));

    int i, j, d1, d2, diff, carry=0, k=res_len-1;

    for(i=l1-1,j=l2-1; i>=0; i--,j--){
        d1 = new_intal1[i] - '0';
        d2 = new_intal2[i] - '0';
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

    //removing extra zeros from the result string
    char *t1, *t2;
    t1 = stripZeros(res);
    t2 = res;
    res = t1;

    //t2 points to the result which might have preceeding zeros, hence its memory has to be freed
    free(t2);
    //the original intal1 and intal2 are unaltered
    //either of intal1 or intal2 might be padded with 0s, the other is copied by strdup() 
    free(new_intal1);       
    free(new_intal2);       

    return res;
}


// 4. INTAL_MUL: Function to multiple two intal numbers
char* intal_multiply(const char* intal1, const char* intal2){
    int l1, l2, res_len;
    l1 = strlen(intal1);
    l2 = strlen(intal2);
    res_len = l1+l2;

    //create a string of all zeros of length l1+l2
    char *res = (char*)malloc(sizeof(char)*(res_len+1));
    for(int k=0;k<res_len;k++){
        res[k] = '0';
    }
    res[res_len] = '\0';

    int i, j, d1, d2, sum, carry, v_shift=res_len-1, h_shift=0;

    for(i=l1-1; i>=0; i--){
        d1 = intal1[i] - '0';
        carry = 0;
        v_shift = res_len-1;

        for(j=l2-1; j>=0; j--){
            d2 = intal2[j] - '0';
            sum = (d1*d2) + (res[v_shift-h_shift] - '0') + carry;
            carry = sum / 10;
            sum = sum % 10;
            res[v_shift-h_shift] = sum + '0';
            v_shift--;
        }

        if(carry>0){
            int c = res[v_shift-h_shift] - '0';
            c = c + carry;
            res[v_shift-h_shift] = c + '0';
        }

        h_shift++;
    }
    res[res_len] = '\0';

    //removing extra zeros from the result string
    char *t1, *t2;
    t1 = stripZeros(res);
    t2 = res;
    res = t1;

    //free up any extra allocated memory
    //t2 points to he result which might have preceeding zeros, hence its memory has to be freed
    free(t2);
    //the original intal1 and intal2 are unaltered and not ducplicated

    return res;
}


// 5. INTAL_MOD: Function to find intal1 (divident) mod intal2 (divisor)
char* intal_mod(const char* intal1, const char* intal2){
    char *divident, *divisor, *t1, *t2;
    divident = strdup(intal1);

    int iter = 0;   //value varies between 0 and 1

    //run loop till divident is greater than divisor 
    while(intal_compare(divident,intal2)!=-1){

        divisor = strdup(intal2);
        //run loop till divisor is smaller than divident
        while(intal_compare(divident,divisor)==1){
            t1 = intal_multiply(divisor,"2");
            t2 = divisor;
            divisor = t1;
            free(t2);
        }        
        t1 = intal_diff(divisor,divident);
        t2 = divident;
        divident = t1;
        free(t2);

        //if intal1 is a factor of intal2
        if(intal_compare(divident,"0")==0){
            free(divident);
            free(divisor);
            char *res = (char*)malloc(sizeof(char)*2);
            res[0] = '0';
            res[1] = '\0';
            return res;
        }

        iter+=1;
        iter%=2;
    }

    if(iter==1){
        t1 = intal_diff(intal2,divident);
        t2 = divident;
        divident = t1;
        free(t2);
    }

    t1 = stripZeros(divident);
    t2 = divident;
    divident = t1;
    free(t2);

    free(divisor);

    return divident;  
}