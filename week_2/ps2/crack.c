/**
 * Crack passwords with bruth force by using crypt to match hashes
 */

#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>


// \0 counts + 26 lowercase + 26 uppercase = 53 characters
const int CHAR_TOTAL = 53;
const string CHAR_ALL = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, char *argv[])
{
    string hash = argv[1];
    char salt[3];
    char pp[6] = "\0\0\0\0\0\0"; // protential password
    
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    
    salt[0] = hash[0];
    salt[1] = hash[1];
    salt[2] = '\0';
    //printf("%s\n", salt); //50
    
    // 5 letters password
    for (int i = 0; i < CHAR_TOTAL; i++)         
    {
        // 4 letters password
        for (int j = 0; j < CHAR_TOTAL; j++)
        {
            // 3 letters password
            for (int k = 0; k < CHAR_TOTAL; k++)
            {
                // 2 letters password
                for (int l = 0; l < CHAR_TOTAL; l++)
                {
                    // 1 letters password
                    for (int m = 1; m < CHAR_TOTAL; m++)
                    {
                        //                           1 2 3 4 5 6
                        pp[0] = CHAR_ALL[m];   // 1) x\0\0\0\0\0
                        pp[1] = CHAR_ALL[l];   // 2) x x\0\0\0\0
                        pp[2] = CHAR_ALL[k];   // 3) x x x\0\0\0
                        pp[3] = CHAR_ALL[j];   // 4) x x x x\0\0
                        pp[4] = CHAR_ALL[i];   // 5) x x x x x\0
                        
                        //printf("hash: %s, password: %s, m = %d, l = %d, k = %d, j = %d, i = %d\n", crypt(pp, salt), pp, m, l, k, j, i);

                        // strcmp: string compare, 0 = strings are found to be identical
                        // compare user hash input with generated hash
                        if (strcmp(crypt(pp, salt), hash) == 0)
                        {
                            printf("%s\n", pp);
                            return 0;
                        }
                    }
                }
            }
        }
    }
   
    printf("Fail to crack hash!\n");
    return 2;
}
