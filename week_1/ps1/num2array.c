/**
  *
  * This program will take in a postive number and store each digit into an array 
  * and return that array into the main function
  *
  **/

#include <cs50.h>
#include <math.h>
#include <stdio.h>

int *num2array(long long ccn, int len, int array[]);
    
int main(void)
{
    long long user_ccn = 0;
    int len_cc = 16; // max cc number length
    int cc_array[len_cc];
    int *cnn_array; // pointer to cc_array
    do 
    {
        user_ccn = get_long("Number: ");
    }
    // avoid negative number
    while (user_ccn  < 0);
    
    len_cc = floor(log10(user_ccn)) + 1;
    // printf("length of credit card number: %d\n", len_cc);
    
    cnn_array = num2array(user_ccn, len_cc, cc_array);
    for (int i = 0; i < len_cc; i++)
    {
        printf("array[%d] = %d \n", i, cnn_array[i]);
    }
}

// use code to convert credit card number into an array
int *num2array(long long ccn, int len, int array[])
{    
    //printf("\n1) convert cc num to array\n");
    for (int i = 0; i < len; i++) 
    {
        array[i] = ccn % 10;
        ccn = ccn / 10; // floor is imply, long
        //printf("array[%d] = %d : new num = %lld\n", i, array[i], ccn);
    }      
    
    return array;
}



