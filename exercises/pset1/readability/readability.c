#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
int main(void)
{
    int letters = 0;
    int words = 1;
    int sentences = 0;

    string s = get_string("Type a text: ");
    for (int i = 0, f = strlen(s); i < f; i++)
    {
        //counting letters
        if (isupper(s[i]) + islower(s[i]) != 0)
        {
            letters += 1;
        }
        else;
        //counting words
        if (isspace(s[i]) != 0)
        {
            words += 1;
        }
        else;
        //counting sentences
        if (s[i] == 33 || s[i] == 46 || s[i] == 63)
        {
            sentences += 1;
        }
    }
    //changing proportionally to 100 words
    float L = letters * (float)100 / words;
    float S = sentences * (float)100 / words;
    //applying formula
    int Grade = round((0.0588 * L) - (0.296 * S) - 15.8);
    if (Grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else    if (Grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", Grade);
    }
}