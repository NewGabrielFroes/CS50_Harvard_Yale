#include <stdio.h>
#include <cs50.h>
#include <math.h>

float get_positive_float(void);
void cash(void);

int main(void)
{
    cash();
}

void cash(void)
{
    int totalCoins = 0;
    float changeOwed = get_positive_float();
    int cents = round(changeOwed * 100);

    while (cents > 0) //Programa vai continuar rodando até sobrar nenhum troco
    {

        if (cents - 25 >= 0) //Retira 25 centavos do troco
        {
            cents -= 25;
            totalCoins++;
            //2
        }

        else if (cents - 10 >= 0) //Retira 10 centavos do troco
        {
            cents -= 10;
            totalCoins++;
            //3
        }

        else if (cents - 5 >= 0) //Retira 5 centavos do troco
        {
            cents -= 5;
            totalCoins++;
        }
        else //Retira 1 centavo do troco
        {
            cents -= 1;
            totalCoins++;
        }




    }
    printf("TOTAL: %i\n", totalCoins);

}

float get_positive_float(void)
{
    float n;
    do
    {
        n = get_float("Change owed: ");
    }
    while (n <= 0);
    return n;
}