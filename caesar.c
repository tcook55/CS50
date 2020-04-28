#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    /*Check for more than 1 arguments*/
    if (argc == 1 || argc >= 3)
    {
        printf("./caesar key\n");
        return 1;
    }
    
    /*Check the argument for only integers*/
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]))
        {
            printf("./caesar key\n");
            return 1;
        }
    }
    /*Get message from user in plaintext*/
    string plain = get_string("plaintext: ");
    
    /*Convert argument key string to integer*/
    int key;
    key = atoi(argv[1]);

    /*Loop through plaintext and move the characters based on the key as well as maintaining case sensitivity*/
    /*Key chages are made by moving the ascii code to 0 based on upper and lower (to ensure z goes to a using modulus) then brings it back to regular ascii codes*/
    for (int i = 0; i < strlen(plain); i++)
    {
        if(isupper(plain[i]))
        {
            plain[i] = (plain[i] - 65 + key) % 26 + 65;
        }
        else if(islower(plain[i]))
        {
            plain[i] = (plain[i] - 97 + key) % 26 + 97;
        }
    }

    printf("ciphertext: %s\n", plain);
}