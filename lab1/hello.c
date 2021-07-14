#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string nameUser = get_string("What is your name?\n"); //Pergunta o nome
    printf("hello, %s\n", nameUser); //Diz o nome
}