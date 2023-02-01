#include <stdio.h>
#include <cs50.h> //Biblioteca to CS50
#include <math.h>
int main(void)
{
    float i = 0;
    do
    {
        i = get_float("Troco devido: ");
    }
    while (i <= 0);
    int v = round(i * 100);
    int g = 0;
    if (v >= 25)
    {
        do
        {
            v = v - 25;
            g ++;
        }
        while (v >= 25);
    }
    else;
    if (v >= 10)
    {
        do
        {
            v = v - 10;
            g ++;
        }
        while (v >= 10);
    }
    else;
    if (v >= 5)
    {
        do
        {
            v = v - 5;
            g ++;
        }
        while (v >= 5);
    }
    else;
    if (v >= 1)
    {
        do
        {
            v = v - 1;
            g ++;
        }
        while (v >= 1);
    }
    else;
    printf("Total de moedas: %i\n", g);
}