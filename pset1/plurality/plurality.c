#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#define MAX 9
typedef struct
{
    string name;
    int votes;
}
candidates;
candidates candidate[MAX];
int print_winner(string);
bool vote(string name);
int main(int argc, string argv[])
{
    if(argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }
    if(argc - 1 > MAX)
    {
    printf("The max amount of candidates is 9\n");
    return 1;
    }
    int n = get_int("Number of Voters:");
    for(int i = 0; i < argc; i++) //fills the array with appropriate data
    {
        strcpy(candidate[i].name , argv[i + 1]);
        candidate[i].votes = 0;
    }
    for(int i = 0; i < n; i++)  //gets votes n times
    {
        string name = get_string("Vote: ");
        bool vote(string name);
    }
    int print_winner(string candidate);
}
bool vote(string name)//count votes
{
    for(int j = 0; j < MAX; j++)
    {
        if (candidate[j].name != NULL)
        {
            if (strcmp(name, candidate[j].name) == 0)
            {
                candidate[j].votes++;
                return true;
            }
        }
    }
    printf("Invalid vote\n");
    return false;
}
int print_winner(string candidates)
{
    int z = 0;
    for(int i = 0; i < 9; i++)
    {
        if(candidate[i].votes > z)
        {
            z = candidate[i].votes;
        }
    }
    for(int i = 0; i < 9; i++)
    {
        if(candidate[i].votes == z)
        {
            printf("%s\n",candidate[i].name);
        }
    }
    return 0;
}