#include <stdio.h>
#include <cs50.h>
void hashtag(int);
int main(void)
{
    int n; //variavel de 1 a 8
    do
    {
        n = get_int("Altura: ");
    }
    while (n < 1 || n > 8);
    for (int i = 0; i < n; i++)//se repete n vezes
    {
        for (int g = n - 1; g > i; g--)//coloca um ponto a menos em cada linha
        {
            printf(" ");
        }
        hashtag(i);
        printf("  ");
        hashtag(i);
        printf("\n");
    }
}
void hashtag(int i)//coloca uma hashtag a mais em cada linha
{
    for (int h = 0; h <= i; h++)
    {
        printf("#");
    }
}