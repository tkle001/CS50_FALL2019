#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string key = argv[1]; //key
    string text; //plaintext
    char c; //ciphertext
    
    // check if key is entered
    if (argc != 2)
    {
        printf("Usage: ./caeser key\n");
        return 1;
    }
    else
    {   
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            // check to make sure key is letter only
            if (!isalpha(key[i]))
            {
                printf("Usage: ./caeser key\n");
                return 1;
            }   
        }
    }
    // get plaintext 
    text = get_string("plaintext: ");
    //printf("%s\n", text);
    
    // shift value and print ciphertext
    printf("ciphertext: ");
    for (int i = 0, j = 0, n = strlen(text), m = strlen(key); i < n; i++, j++)
    {
        // loop key 
        if (j > m - 1)
        {
            j = 0;
        }
        if (isalpha(text[i]))
        {
            if (isupper(text[i]) && isupper(key[j]))
            {
                c = (((text[i] - 'A' + key[j]) - 'A') % 26) + 'A';
            }
            else if (isupper(text[i]) && islower(key[j]))
            {
                c = (((text[i] - 'A' + key[j]) - 'a') % 26) + 'A';
            }
            else if (islower(text[i]) && isupper(key[j]))
            {
                c = (((text[i] - 'a' + key[j]) - 'A') % 26) + 'a';
            }
            else if (islower(text[i]) && islower(key[j]))
            {
                c = (((text[i] - 'a' + key[j]) - 'a') % 26) + 'a';
            }
        }
        else
        {
            c = text[i];
            j--;
        }
        //printf("i = %d, j = %d, c = %c\n", i, j, c);
        printf("%c", c);
    }
    printf("\n");

    return 0;
}


