#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void textUpper(string text);
int countLetters(string text);
int countWords(string text);
int countSentences(string text);

int main(void)
{
    string text = get_string("Text: "); //Pega o texto
    float l, s;

    l = (countLetters(text) / (float)countWords(text)) * 100; //Arredonda
    s = (countSentences(text) / (float)countWords(text)) * 100; //Arredonda

    l = round(l * 100) / 100;
    s = round(s * 100) / 100;
    int index = round(0.0588 * l - 0.296 * s - 15.8); //Calcula Index

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}

void textUpper(string text) //Coloca tudo maisculo
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (islower(text[i]))
        {
            text[i] = toupper(text[i]);
        }
    }
}

int countLetters(string text) //Conta letra
{
    int count = 0;

    textUpper(text);

    for (int i = 0, n = strlen(text); i < n; i++) //Laço
    {

        if (text[i] >= 'A' && text[i] <= 'Z') //Pega todas as maisculas
        {
            count++; //Conta todas as letras
        }

    }
    

    return count;
}

int countWords(string text)
{
    int count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            count++;
        }
    }

    return ++count;
}

int countSentences(string text)
{
    int count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count++;
        }
    }

    return count;
}