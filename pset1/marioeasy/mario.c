#include <stdio.h>
#include <cs50.h>

int get_positive_int(void);
void pyramid(void);

int main(void)
{
    pyramid();
}

int get_positive_int(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}

void pyramid(void)
{
    int height = get_positive_int();

    for (int i = 1; i <= height; i++)
    {

        for (int f = height; f > i; f--)
        {
            printf(" ");//create the spacing
        }

        for (int j = 0; j < i; j++)
        {
            printf("#");//create the pyramids
        }

        printf("\n");
    }
}