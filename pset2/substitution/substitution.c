#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int notValidateKey(string key);

int main(int argc, string argv[])
{
    if (argc != 2) //Garante que o usuario só vai dar dois argumentos
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    if (notValidateKey(argv[1])) //Verifica se tem apenas 26 caracteres
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }


    string plainText = get_string("plaintext:  "); //Pega a string do usuario

    printf("ciphertext: ");
    
    for (int i = 0, n = strlen(plainText), j = 0; i < n; i++)
    {
        if (isupper(plainText[i]))
        {
            j = plainText[i] - 'A'; //Criptografa os maísculos
        }
        else
        {
            j = plainText[i] - 'a'; //Criptografa os minusculos
        }

        if (!isspace(plainText[i]) && isalpha(plainText[i])) //Verifica se o caractere não é um espaço
        {
            if (isupper(plainText[i]))
            {
                plainText[i] = toupper(argv[1][j]);
            }
            else
            {
                plainText[i] = tolower(argv[1][j]);
            }
            printf("%c", plainText[i]);
        }
        else
        {
            printf("%c", plainText[i]);
        }
    }
    printf("\n");
}

int notValidateKey(string key) //Verifica se a chave funciona
{
    int count = 0;

    for (int i = 0, n = strlen(key); i < n; i++)
    {

        if (isalpha(key[i])) //Verifica se o caractere é uma letra
        {
            for (int x = i + 1; x < n; x++)
            {
                if (toupper(key[i]) == toupper(key[x])) //Verifica se um caractere não esta repetido
                {
                    return 1;
                }
            }
            count++;
        }

    }


    if (count != 26)
    {
        return 1;
    }

    return 0;
}