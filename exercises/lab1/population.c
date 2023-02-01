#include<stdio.h>
#include<cs50.h>
#include<math.h>
int main(void)
{
    int i = 0; // initial population
    int f = 0; // final population
    int t = 0; //years
    do
    {
        i =  get_int("Initial population= ");   //receiving inputs
    }
    while (i < 9);
    do
    {
        f =  get_int("Final population= "); //receiving inputs
    }
    while (f < i);
    if(f == i)
    {
        printf("Years: 0\n");
    }
    else
    {
        do
        {
            int g = (i + floor((float)i / 3));  //mathmatical operations
            g = (g - floor((float)i / 4));
            i = g;
            t++;    //counting time
        }
        while (i < f);
        printf("Years: %i\n", t);
    }
}