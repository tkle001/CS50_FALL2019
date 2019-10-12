/**
  *
  * This program validate credit card numbers using Luhn's Algorithm
  *
  **/

#include <cs50.h>
#include <math.h>
#include <stdio.h>

int *num2array(long long ccn);
bool luhn_s_alg(int *arr, int length);
void cc_type(bool v, int *arr, int length);
    
int main(void)
{
    long long user_ccn = 0;
    int *cnn_array; // pointer to array
    int len_cc;
    bool valid;
    
    do 
    {
        user_ccn = get_long("Number: ");
    }
    // avoid negative number
    while (user_ccn  < 0);
    // printf("credit card number: %lld\n", ccn);
    
    len_cc = floor(log10(user_ccn)) + 1;
    // printf("length of credit card number: %d\n", len_cc);
    
    // printf("%i\n", ccn_len);
    if (len_cc < 13 || len_cc > 16)
    {
        printf("INVALID\n");
    }
    else
    {
        cnn_array = num2array(user_ccn);

        valid = luhn_s_alg(cnn_array, len_cc);   
        //printf("%d\n", valid);

        cc_type(valid, cnn_array, len_cc);
    }
}

// use code to convert credit card number into an array
int *num2array(long long ccn)
{
    static int a[16];
    
    //printf("\n1) convert cc num to array\n");
    for (int i = 0; i < 16; i++) 
    {
        a[i] = ccn % 10;
        ccn = ccn / 10; // floor is imply, long
        //printf("%d  : %d : %lld\n", i, a[i], ccn);
    }      
    
    return a;
}


// 0 = false
// 1 = true
bool luhn_s_alg(int *arr, int length)
{
    int set_1 = 0;
    int sum_1 = 0;
    int sum_2 = 0;
    int sum_final = 0;

    //printf("\nx2 every other digit starting from 
    //second-to-last and add those products' digits\n");
    for (int j = 1; j < length; j += 2)
    {
        set_1 = arr[j] * 2;
        if (0 < set_1 && set_1 < 9)
        {
            sum_1 += set_1;
        } 
        else if (set_1 > 9)
        {
            sum_1 += set_1 % 10;
            sum_1 += set_1 / 10; // floor is imply, long
        }
        //printf("%d  : %d : %d\n", j, set_1, sum_1);
    }
        
    //printf("\nget sum of the other digits\n");
    for (int k = 0; k < length; k += 2)
    {
        sum_2 += arr[k];
        //printf("%d  : %d : %d\n", k, arr[k], sum_2);
    }
  
    sum_final = sum_1 + sum_2; 
    //printf("%d  = %d + %d\n", sum_final, sum_1, sum_2);
    
    if (sum_final % 10 == 0)
    {
        return true;
    } 
    else
    {
        return false;
    }
}

// print the type of credit card
void cc_type(bool v, int *arr, int length)
{
    if (v == false)
    {
        printf("INVALID\n");
    } 
    else 
    {
        //printf("something\n");
        if (length == 15 && arr[length - 1] == 3 && (arr[length - 2] == 4 ||  arr[length - 2] == 7))
        {
            printf("AMEX\n");
        }
        else if (length == 16 && arr[length - 1] == 5 && (arr[length - 2] == 1 
                 || arr[length - 2] == 2 ||  arr[length - 2] == 3 ||  arr[length - 2] == 4
                 ||  arr[length - 2] == 5))
        {
            printf("MASTERCARD\n");
        }
        else if ((length == 13 || length == 16) && (arr[length - 1] == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
