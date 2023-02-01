#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
int main (void)
{
int pairs[9] = {1,2,3,4,5,6,7,8,9};
for(int j = 0; j < 9; j++)
    {
        for(int i = 0; i < 9 - 1; i++)
        {
            if(pairs[i + 1] > pairs[i])
            {
                int temporary = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temporary;
            }
        }
    }
    for(int i = 0; i < 9; i++)
        {
        printf("%i",pairs[i]);
        }
        printf("\n");
}