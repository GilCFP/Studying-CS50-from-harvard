#include <stdio.h>
#include <cs50.h> //Biblioteca to CS50

int main(void)
{
    string name = get_string("Qual é o seu nome?\n"); //Solicitando entrada de dado na variável "name"
    printf("hello, %s \n", name);   //Sintaxe da string
}