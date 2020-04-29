#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int check_arg(int arg_count, string arg);
string encipher(string plain, string key);


int main(int argc, string argv[])
{
    string key = argv[1];
    if (check_arg(argc, key) == 1)
    {
        return 1;
    }
    string plain = get_string("plaintext: ");
    string cipher = encipher(plain, key);
    printf("ciphertext: %s\n", cipher);

}




/*Function that runs a series of checks on provided argument*/
int check_arg(int arg_count, string arg)
{
    /*Check for 1 argument*/
    if (arg_count == 1 || arg_count >= 3)
    {
        printf("Program only takes one argument\n");
        return 1;
    }
    /*Check argmument for 26 characters*/
    if (strlen(arg) != 26)
    {
        printf("Key must be 26 characters\n");
        return 1;
    }
    /*Check argument for alphabet characters only*/
    for (int i = 0; i < strlen(arg); i++)
    {
        if (isalpha(arg[i]) == false)
        {
            printf("Argument can only use alphabetic characters\n");
            return 1;
        }
        /*Change all characters to lowercase for homogeneity when checking duplicates*/
        arg[i] = tolower(arg[i]);
        /*Check for duplicate characters*/
        int count = 0;
        for (int m = 0; m < strlen(arg); m++)
        {
            if (arg[m] == arg[i])
            {
                count++;
            }
            if (count == 2)
            {
                printf("No duplicate characters\n");
                return 1;
            }
        }
    }
    return 0;
}


/*Function that takes the submitted text and key and enciphers the user submitted text*/
string encipher(string plain, string key)
{
    /*Loop to iterate through the user submitted text*/
    for (int i = 0; i < strlen(plain); i++)
    {
        /*Check to see if it is a letter. If not, it will be outputted just as it was inputted.*/
        if (isalpha(plain[i]))
        {
            /*Check for lower case letters. It will matter because of how much we subtract by*/
            if (islower(plain[i]))
            {
                /*We have moved the ascii letters to 0 so that we can compare the positions of the old letters to their relative positions in the provided key then applying that change*/
                plain[i] = plain[i] - 97;
                for (int m = 0; m < strlen(key); m++)
                {
                    if (plain[i] == m)
                    {
                        plain[i] = key[m];
                    }
                }
            }
            /*Same as above only this statement changes letters back to uppercase when the cipher transition is finished*/
            else
            {
                plain[i] = plain[i] - 65;
                for (int m = 0; m < strlen(key); m++)
                {
                    if (plain[i] == m)
                    {
                        plain[i] = key[m];
                        plain[i] = toupper(plain[i]);
                    }
                }
            }
        }    
    }
    return plain;
}