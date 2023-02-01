#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, string argv[])
{
    //start of key verification
    if (argc != 2 || argv[1] == 0)//hasn't inserted a key
    {
        printf("Usage: ./substitution key\n");
        return (1);
    }
    int z = strlen(argv[1]);
    if (z != 26)//key of wrong size
    {
        printf("The key must contain 26 characters.\n");
        return (1);
    }
    for (int i = 0; i < z; i++)
    {
        if (isalpha(argv[1][i]) == 0) //not alphabetical key
        {
            printf("The key must contain only alphabetical characters.\n");
            return (1);
        }
        for (int j = i + 1; j < z; j++)
        {
            if (toupper(argv[1][i]) == toupper(argv[1][j])) //verifying repetitions
            {
                printf("The key must not contain repeated characters.\n");
                return (1);
            }
        }
    }//end of key verification
    string t = get_string("Plaintext: ");
    z = strlen(t); //reusing z for the new strlen
    for (int i = 0; i < z; i++) //making the substitution based on positioning
    {
        if (islower(t[i]))
        {
            t[i] = tolower(argv[1][t[i] - 97]);
        }
        if (isupper(t[i]))
        {
            t[i] = toupper(argv[1][t[i] - 65]);
        }
    }
    printf("ciphertext: %s\n", t);
}