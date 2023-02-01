#include <stdio.h>
#include <cs50.h>
int main(void)
{
    long i = 0;
    do
    {
        i = get_long("Números do cartão: ");
    }
    while (i < 0);
    if (i < 1000000000000) //less than 13 digits
    {
        printf("INVALID\n");
    }
    else
    {
        int a = 0;
        int b = 0;
        long j = i;
        do
        {
            //take digits one by one
            int g = i % 10;
            a = a + g;
            i = ((i - i % 10) / 10);
            g = i % 10;
            if (g >= 5)
            {
                b = b + ((g * 2) % 10) + ((2 * g - (g * 2) % 10) / 10);
            }
            else
            {
                b = b + 2 * g;
            }
            i = ((i - i % 10) / 10);
        }
        while (i > 0);
        int s = a + b;
        int k = ((s + 1) % 10);
        if (((s + 1) % 10) == 1)
        {
            do
            {
                j = (j - (j % 10)) / 10;
            }
            while (j > 99);
            //flag identifier
            if (51 <= j && j <= 55)
            {
                printf("MASTERCARD\n");
            }
            else if (j == 34 || j == 37)
            {
                printf("AMEX\n");
            }
            else if (j >= 40 && j <= 49)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}