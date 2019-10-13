#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int k; //key
    string text; //plaintext
    char c; //ciphertext
    
    if (argc != 2)
    {
        printf("Usage: ./caeser key\n");
        return 1;
    }
    else
    {
        // string to number i.e. int
        k = atoi(argv[1]);
        text = get_string("plaintext: ");
        //printf("%s\n", text);
        
        printf("ciphertext: ");
        for (int i = 0, sl = strlen(text); i < sl; i++)
        {
            // ASCII     a = 97    z = 122
            //           A = 65    Z = 90
            if (islower(text[i]))
            {
                c = (((text[i] + k) - 97) % 26) + 97;
            }
            else if (isupper(text[i]))
            {
                c = (((text[i] + k) - 65) % 26) + 65;
            }
            else
            {
                // for non-letter, i.e. space and comma
                c = text[i];
            }
            printf("%c", c);    
        }
        printf("\n");
        
        return 0;
    }

    
}
