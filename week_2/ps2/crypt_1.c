/**
 * Input password and key to generate hash
 * Opposite of crack.c
 */

#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    string pass = argv[1];
    string key  = argv[2];
    string hash;
    
    if (argc != 3)
    {
        printf("Usage: ./crypt_1 password key\n");
        return 1;
    }

    hash = crypt(pass, key);
    printf("Hash: %s\n", hash);
    return 0;
}
