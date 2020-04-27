#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int text_processing(string sent);
int index_calc(float letters, float words, float sentences);

/* Both spaces and periods initiated to be updated when the number of letters is counted in text_processing. More efficient to only loop once*/
int spaces = 0;
int periods = 0;

int main(void)
{
    /*Asks user for text input*/
    string text = get_string("Text: ");
    /* Create letters variable that uses the text_processing function to count letters as well as update
    the global variable spaces and periods*/
    int letters = text_processing(text);
    /*Calculate the Coleman-Liau index using the letters, spaces for words, and periods for sentences*/
    int index = index_calc(letters, spaces + 1, periods);
    
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}


/*Function to loop through the inputted text. This function returns letter counts but will also update the spaces and periods variables to help calculate words and sentences.
Only 1 loop is used for efficiency*/
int text_processing(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        /*Check each character if it's a letter, space, or period*/
        if (isalpha(text[i]))
        {
            count++;
        }
        else if (text[i] == ' ')
        {
            spaces++;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            periods++;
        }
    }
    return count;
}

/*Function to calculate Coleman-Liau index*/
int index_calc(float letters, float words, float sentences)
{
    float L = (letters / words) * 100;
    float S = (sentences / words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return round(index);
}