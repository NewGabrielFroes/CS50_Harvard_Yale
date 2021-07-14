#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void validateKey(string key);

int main(int argc, string argv[])
{
    if (argc != 2) //Garante que o usuario só vai dar dois argumentos
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    validateKey(argv[1]);

    int key = atoi(argv[1]); //Converte a string para um int


    string plainText = get_string("plaintext:  ");

    printf("ciphertext: ");
    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        if (!isspace(plainText[i]) && isalpha(plainText[i])) //Verifica se o caractere não é um espaço
        {
            if ((plainText[i] + key >= 'a' && plainText[i] + key <= 'z') //Verifica se os caracteres fazem partes
                || (plainText[i] + key >= 'A' && plainText[i] + key <= 'Z')) //dos maisculos ou minuscilos
            {
                printf("%c", plainText[i] + key); //Começa a criptografar
            }
            else
            {
                if (plainText[i] + key > 'z')
                {
                    int resto = (plainText[i] + key) - ((int)'z');
                    int somador = ('a' + resto) - 1;
                    while (somador > 'z')
                    {
                        somador -= 26; //Subtrai para que as letras sempre fique no alfabeto
                    }
                    printf("%c", somador);
                }
                else
                {
                    int resto = (plainText[i] + key) - ((int)'Z');
                    int somador = ('A' + resto) - 1;
                    while (somador > 'Z')
                    {
                        somador -= 26; //Subtrai para que as letras sempre fique no alfabeto
                    }
                    printf("%c", somador);
                }

            }
        }
        else
        {
            printf("%c", plainText[i]);
        }
    }
    printf("\n");
}

void validateKey(string key) //Verifica se a chave funciona
{
    int count = 0;

    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (isdigit(key[i]))
        {
            count++;
        }
    }

    if (count != strlen(key))
    {
        printf("Usage: ./caesar key\n");
    }
}