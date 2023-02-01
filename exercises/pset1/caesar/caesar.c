#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
void passed(char);
int main(int argc, string argv[])
{
    if (argc != 2 || argv[1] == 0)
    {
        printf("Usage: ./caesar key\n");
        return (1);
    }
    for (int a = 0, b = strlen(argv[1]); a < b; a++)
    {
        if (isdigit(argv[1][a]) == 0)
        {
            return (1);
        }
    }
    int k = atoi(argv[1]);
    string w = get_string("Plaintext: ");
    for (int i = 0, f = strlen(w); i < f; i++)
    {
        if (isupper(w[i]))
        {
            int t = w[i] + k - 65;
            t %= 26;
            w[i] = t + 65;
        }
        if (islower(w[i]))
        {
            int t = w[i] + k - 97;
            t %= 26;
            w[i] = t + 97;
        }
    }
    printf("ciphertext: %s\n", w);
}