#include <stdio.h>
#include <cs50.h>

int get_number_start_permitted(void);
void years(void);


int main(void)
{
    years();
}

void years(void)
{
    int start = get_number_start_permitted();
    int years = 0;
    int end;

    do
    {
        end = get_int("End size: "); //TERMINA UM SIZE
    }
    while (end < start);



    while (start < end)
    {
        years++;
        start += ((start / 3) - (start / 4)); //COMEÇA A CONTAGME
    }

    printf("Years: %i\n", years); //IMPRIME OS ANOS


}

int get_number_start_permitted(void)
{
    int y;
    do
    {
        y = get_int("Start size: "); //PEGA O INICOS
    }
    while (y < 9);
    return y;
}

