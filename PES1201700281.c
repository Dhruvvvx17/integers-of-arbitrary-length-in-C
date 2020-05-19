/*
    Dhruv Vohra
    PES1201700281
    C Library for integers of arbitrary length (intal)

    Includes the following functions:
        - 1. Addition of two intals (intal_add)
        - 2. Comparison of two intals (intal_compare)
        - 3. Difference of two intals (intal_diff)
        - 4. Product of two intals (intal_multiply)
        - 5. Mod of two intals (intal_mod)
        - 6. First intal to the power second intal (intal_pow)
        - 7. GCD of two intals (intal_gcd)
        - 8. nth fibonacci number, n is an intal (intal_fibonacci)
        - 9. Factorial of an intal (intal_factorial)
        - 10. binomial coefficient of nCk, result returned is intal (intal_bincoeff)
        - 11. index of max intal in an unsorted array (intal_max)
        - 12. index of min intal in an unsorted array (intal_min)
        - 13. index of given intal in an unsorted array (intal_search)
        - 14. sorting an array of intals in O(nlogn) time (intal_sort)
        - 15. searching for the given intal value in a sorted arrar in O(logn) time (intal_binsearch)
        - 16. Dynamic problem solution to the coin row problem in an intal array (coin_row_problem)
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "intal.h"

//assuming max intal length to be 1000 + 1 for null character
#define MAX_SIZE 1001

// Helper Function declarations
static char* padding(const char* intalTemp, int zeros, int new_length);
static char* stripZeros(const char* intalTemp);
static char* compute_gcd(char* n1, char* n2);
static int getMin(unsigned int a, unsigned int b);
static void merge(char **arr, int n, int m);
static void mergeSort(char **arr, int n);
static int custom_binSearch(char **arr, int l, int r, char *key);
static char* find_max(char **arr, char **dp_table, int n);


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


//Removing any prefix zeros from the given string
static char* stripZeros(const char* intalTemp){

    //check if the string contains all zeros, in which case a single character 0 should be returned
    int check = 1;      //temporary variable to check if the string is all zeros
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
        //free up any extra memory allocated
        //new_intal1 and new_intal2 are copies of original intal's, have to be freed 
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


// 6. INTAL_POW: Function to find intal1 ^ n
char* intal_pow(const char* intal1, unsigned int n){
    if(n==0){
        char *res = (char*)malloc(sizeof(char)*2);
        res[0] = '1';
        res[1] = '\0';
        return res;
    }
    char *temp, *res;
    temp = intal_pow(intal1,n/2);   //recursive approach
    //if power is even, multiply subproblems directly
    if(n%2==0){
        res = intal_multiply(temp,temp);
        free(temp);
        return res;
    }
    //if power is odd, multiply subproblems with the original value
    else{
        temp = intal_multiply(temp,temp);
        res = intal_multiply(intal1,temp);
        free(temp);
        return res;
    }
}


// 7. INTAL_GCD: Function to find gcd of intal1 and intal2
char* intal_gcd(const char* intal1, const char* intal2){
    //check for border case of having intal1 and intal2 as 0, in which case, return 0
    if( intal_compare(intal1,"0")==0 && intal_compare(intal2,"0")==0 ){
        char *res = (char*)malloc(sizeof(char)*2);
        res[0] = '0';
        res[1] = '\0';
        return res;        
    }
    else{
        char *res, *n1, *n2;
        n1 = strdup(intal1);
        n2 = strdup(intal2);
        res = compute_gcd(n1,n2);
        free(n1);
        free(n2);
        return res;
    }
}

//helper fucntion, includes actual euclidean algorithm for gcd
static char* compute_gcd(char* n1, char* n2){
    if(intal_compare(n2,"0")==0){
        char *res = strdup(n1);
        return res;
    }
    char *t, *res;
    t = intal_mod(n1,n2);
    res = compute_gcd(n2,t);
    free(t);
    return res;
}


// 8. INTAL_FIBONACCI: Function to find the nth fibonacci number
char* intal_fibonacci(unsigned int n){
    char *prev_2, *prev_1, *res, *t;
    
    prev_2 = (char*)malloc(sizeof(char)*2);
    prev_2[0] = '0';
    prev_2[1] = '\0';

    if(n==0)
        return prev_2;


    prev_1 = (char*)malloc(sizeof(char)*2);
    prev_1[0] = '1';
    prev_1[1] = '\0';

    if(n==1)
        return prev_1;

    int i = 2;
    while(i<=n){
        res = intal_add(prev_2,prev_1);
        t = prev_2;
        prev_2 = prev_1;
        prev_1 = res;
        free(t);
        i+=1;
    }

    //free up any extra allocated memory
    free(prev_2);
    //cant free prev1 becuase it points to res

    return res;
}


// 9. INTAL_FACTORIAL: Factorial to find factorial of n (iterative solution)
char* intal_factorial(unsigned int n){
    //border case of n=0 or n=1, result=1
    if(n==0 || n==1){
        char *res = (char*)malloc(sizeof(char)*2);
        res[0] = '1';
        res[1] = '\0';
        return res;
    }

    int i = 2;
    char *t1, *t2, *res, *add_one, *next_num;

    //a constant '1' to add to the previous number, to obtain next intal number
    add_one = (char*)malloc(sizeof(char)*2);
    add_one[0] = '1';
    add_one[1] = '\0';

    //the next number to be multiplied in to the resulting factorial
    next_num = (char*)malloc(sizeof(char)*2);
    next_num[0] = '1';
    next_num[1] = '\0';

    //actual factorial result over the n iterations
    res = (char*)malloc(sizeof(char)*2);
    res[0] = '1';
    res[1] = '\0';

    while(i<=n){
        t1 = intal_add(next_num,add_one);
        t2 = next_num;
        next_num = t1;
        free(t2);       //free up the memory occupied by previous next_num
        
        t1 = intal_multiply(res,next_num);
        t2 = res;
        res = t1;
        free(t2);       //free up the memory occupied by previous res
        i+=1;
    }

    free(add_one);
    free(next_num);

    return res;
}


// 10. INTAL_BINCOEFF: Function to compute the binary coefficient of C(n,k)
char* intal_bincoeff(unsigned int n, unsigned int k){
    //string array to store coefficients, based on pascals identity

    //as C(n,k) is same as C(n,n-k). The reduces the computations for k values greater than n/2
    //the max computations will be for k==n/2
    if(k>n/2)
        k = n-k;

    char **array = (char**)malloc(sizeof(char*)*(k+1));
    //array of size k, initally all values 0
    for(int i=0; i<=k; i++){
        array[i] = (char*)malloc(sizeof(char*)*MAX_SIZE);
        strcpy(array[i], "0");
    }
    strcpy(array[0],"1");     //C(n,0) = 1

    char *t, *res;

    for(int i=1; i<=n; i++){
        for(int j=getMin(i,k); j>0; j--){
            t = intal_add(array[j], array[j-1]);
            strcpy(array[j],t);
            free(t);
        }
    }

    res = strdup(array[k]);
    for(int i=0; i<=k; i++){
        free(array[i]);
    }
    free(array);
    return res;
}

static int getMin(unsigned int a, unsigned int b){
    return (a>=b) ? b : a;
}


// 11. INTAL_MAX: Function to find the max value intal in the given array
int intal_max(char **arr, int n){

    int max_index = 0, cmp;
    char *max_intal, *t;

    max_intal = (char*)malloc(sizeof(char)*MAX_SIZE);
    strcpy(max_intal,arr[0]);

    for(int i=1; i<n; i++){
        t = arr[i];
        cmp = intal_compare(t,max_intal);
        //if t > max_intal then cmp==1 & t is the new max_intal
        if(cmp==1){
            strcpy(max_intal,t);
            max_index = i;
        }
    }
    //free up memory
    free(max_intal);
    return max_index;
}


// 12. INTAL_MIN: Function to find the min value intal in the given array
int intal_min(char **arr, int n){

    int min_index = 0, cmp;
    char *min_intal, *t;

    min_intal = (char*)malloc(sizeof(char)*MAX_SIZE);
    strcpy(min_intal,arr[0]);

    for(int i=1; i<n; i++){
        t = arr[i];
        cmp = intal_compare(t,min_intal);
        //if t < min_intal then cmp==-1 & t is the new min_intal
        if(cmp==-1){
            strcpy(min_intal,t);
            min_index = i;
        }
    }
    //free up memory
    free(min_intal);
    return min_index;
}


// 13. INTAL_SEARCH: A linear search implementation to search for the given key in the array
int intal_search(char **arr, int n, const char* key){

    int res = -1, cmp;
    char *t;

    for(int i=0; i<n; i++){
        t = arr[i];
        cmp = intal_compare(t,key);
        if(cmp==0){
            res = i;
            break;
        }
    }
    //no memory is allocated at all, hence nothing to free
    return res;
}


// 14. INTAL_SORT: A O(nlogn) implementation soring algorithm to sort the array of intal's
void intal_sort(char **arr, int n){
    mergeSort(arr, n);
}


//helper function for mergesort, to divide array into 2 halves
static void mergeSort(char **arr, int n){    
    if(n<=1)
        return;

    int m = n/2;
    //recursively call mergeSort until 1 element is left in list
    mergeSort(arr, m);
    mergeSort(arr+m, n-m);
    merge(arr, n, m);
}


//helper function for mergesort, to merge two arrays in a sorted order
static void merge(char **arr, int n, int m){
    int i=0, j=m, k=0;
    
    char **temp;
    temp = (char**)malloc(sizeof(char*)*n);
    for(int x=0; x<n; x++){
        temp[x] = (char*)malloc(sizeof(char)*MAX_SIZE);
        strcpy(temp[x],"0");
    }

    while(i<m && j<n){
        if(intal_compare(arr[i],arr[j])!=1){
            strcpy(temp[k],arr[i]);
            i+=1;
        }
        else{
            strcpy(temp[k],arr[j]);
            j+=1;
        }
        k+=1;
    }

    //if any one list is exhausted, copy the other one completely
    if(j==n){
        while(i<m){
            strcpy(temp[k],arr[i]);
            i+=1; k+=1;
        }        
    }
    else{
        while(j<n){
            strcpy(temp[k],arr[j]);
            j+=1; k+=1;
        }
    }

    //free up the temporary array
    for(int x=0; x<n; x++){
        strcpy(arr[x],temp[x]);
        free(temp[x]);
    }
    free(temp);
}


// 15. INTAL_BINSEARCH: A O(logn) implementation to search for the given key in the array 
int intal_binsearch(char **arr, int n, const char* key){
    char *k = (char*)malloc(sizeof(char)*MAX_SIZE);
    strcpy(k,key);
    int res;
    res = custom_binSearch(arr, 0, n, k);
    free(k);
    return res;
}


//binary search helper function, actual binary search logic
static int custom_binSearch(char **arr, int l, int r, char *key){
    if(r-l+1 < 1){
        return -1;
    }
    int m = (l+r)/2;

    if(intal_compare(key,arr[m])==0)
        return m;

    else if(intal_compare(key,arr[m])==-1)
        return custom_binSearch(arr, l, m-1, key);
    
    else
        return custom_binSearch(arr, m+1, r, key);
}


// 16. COIN_ROW_PROBLEM: Returns the max sum that can be obtained from the array, with no consecutive value taken in the sum
char* coin_row_problem(char **arr, int n){

    //init a dp_table with all zeros, allocating O(n) extra space
    char **dp_table = (char**)malloc(sizeof(char*)*n);
    for(int i=0; i<n; i++){
        dp_table[i] = (char*)malloc(sizeof(char)*MAX_SIZE);
        strcpy(dp_table[i],"0");
    }
    char *res = (char*)malloc(sizeof(char)*MAX_SIZE);
    strcpy(res,find_max(arr,dp_table,n-1));

    //free up the dp_table memory
    for(int i=0; i<n; i++){
        free(dp_table[i]);
    }
    free(dp_table);

    return res;
}


//helper function to evaluate the recurrance and find solution to coin-row-problem
static char* find_max(char **arr, char **dp_table, int n){
    if(n<0)
        return "0";

    else if (n==0){
        strcpy(dp_table[0],arr[0]);
        return dp_table[0];
    }

    char *t1, *add_curr_coin, *use_prev_max;
    
    //RECURRANCE: F(n) = max{ (Cn + F(n-2)), F(n-1) }

    //first part of recurrance
    t1 = find_max(arr, dp_table, n-2);
    add_curr_coin = intal_add(t1, arr[n]); 

    //second part of recurrance
    use_prev_max = find_max(arr, dp_table, n-1);

    //compare the two to find max value, copy the max in dp_table
    int r = intal_compare(add_curr_coin, use_prev_max);
    if(r>=0)
        strcpy(dp_table[n], add_curr_coin);
    else
        strcpy(dp_table[n], use_prev_max);


    //free add_curr_coin as that is the result of intal_add which returns a char*
    free(add_curr_coin);
    //do not free use_prev_max as that points to a value in dp_table, dp_table memory is freed up in the calling function

    return dp_table[n];
}