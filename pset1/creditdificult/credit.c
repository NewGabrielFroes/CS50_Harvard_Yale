#include <stdio.h>
#include <cs50.h>
#include <math.h>

int lengthNumber(long cardNumber);
int isCardValid(int lengthNumber);
int checkSum(long cardNumber);
void banner(int result, long cardNumber);

int main(void)
{
    long cardNumber = get_long("Number: ");
    int validator = isCardValid(lengthNumber(cardNumber));
    if (validator == 0)
    {
        banner(checkSum(cardNumber), cardNumber);
        return 0;
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
    return 1;
}

int lengthNumber(long cardNumber) //Diz quantos digitos tem um cartao
{
    int count = 0;
    while (cardNumber > 0)
    {
        cardNumber = cardNumber / 10;
        count++;
    }

    return count;
}

int isCardValid(int lengthNumber) //Diz se o cartão é valido ou não
{
    if (lengthNumber == 13 || lengthNumber == 15 || lengthNumber == 16)
    {
        return 0;
    }

    return 1;
}

int checkSum(long cardNumber)
{
    int sum1 = 0;
    int sum2 = 0;
    int result = 0;
    int modulus1;
    int modulus2;
    int digitus1;
    int digitus2;

    while (cardNumber > 0)
    {
        modulus1 = cardNumber % 10; //Pega do último digito e adiciona
        cardNumber = cardNumber / 10; //Resto do cartao faltando
        sum1 += modulus1; //Soma de todos os digitos começando pelo último

        modulus2 = cardNumber % 10; //Pega do penútimo digito
        cardNumber = cardNumber / 10;// Resto do cartao faltando

        modulus2 = modulus2 * 2;  //Multiplica pois esta na formula
        digitus1 = modulus2 % 10; //Pega o último digito EX: 18 --> Retira o 8
        digitus2 = modulus2 / 10; //Pega o primeiro digito EX: 18 --> Retira o 1
        sum2 = sum2 + digitus1 + digitus2; //Soma todos os digitos começando pelo penúltimo

        /*printf("PrimeiroDigito: %i\n", digitus2);
        printf("SegundoDigito: %i\n", digitus1);
        printf("SomaDigitod: %i\n", sum2);*/
    }

    result = (sum1 + sum2) % 10;

    if (result % 10 == 0)
    {
        return 0;
    }

    return 1;
}

void banner(int result, long cardNumber)
{
    if (result == 0)
    {
        do
        {
            cardNumber = cardNumber / 10;
        }
        while (cardNumber > 100);


        if ((cardNumber / 10 == 5) && (0 < cardNumber % 10 && cardNumber % 10 < 6))
        {
            printf("MASTERCARD\n");
        }
        else if ((cardNumber / 10 == 3) && (cardNumber % 10 == 4 || cardNumber % 10 == 7))
        {
            printf("AMEX\n");
        }
        else if (cardNumber / 10 == 4)
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
