#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average_pixels;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average_pixels = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / (float)3);
            image[i][j].rgbtRed = average_pixels;
            image[i][j].rgbtBlue = average_pixels;
            image[i][j].rgbtGreen = average_pixels;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int copyRed;
    int copyBlue;
    int copyGreen;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            copyRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed; //2
            image[i][width - j - 1].rgbtRed = copyRed;

            copyBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue; //3
            image[i][width - j - 1].rgbtBlue = copyBlue;

            copyGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen; //4
            image[i][width - j - 1].rgbtGreen = copyGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*image_copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    int amount_red = 0;
    int amount_blue = 0;
    int amount_green = 0;
    int count_pixels = 0;

    for (int i = 0; i < height; i++) //3
    {
        for (int j = 0; j < width; j++) //3
        {
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int z = j - 1; z <= j + 1; z++)
                {
                    if (x >= 0 && z >= 0 && x < height & z < width) //Verifica se pode analisar o pixel
                    {
                        amount_red += image[x][z].rgbtRed;
                        amount_blue += image[x][z].rgbtBlue;
                        amount_green += image[x][z].rgbtGreen;
                        count_pixels++;
                    }

                    if (z >= j + 1 && x >= i + 1)
                    {
                        image_copy[i][j].rgbtRed = round((float)amount_red / count_pixels);
                        image_copy[i][j].rgbtBlue = round((float)amount_blue / count_pixels);
                        image_copy[i][j].rgbtGreen = round((float)amount_green / count_pixels);

                        //printf("%i %i %i\n", image_copy[i][j].rgbtRed, image_copy[i][j].rgbtBlue, image_copy[i][j].rgbtGreen);

                        amount_red = 0;
                        amount_blue = 0;
                        amount_green = 0;
                        count_pixels = 0;
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image_copy[i][j].rgbtRed;
            image[i][j].rgbtBlue = image_copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image_copy[i][j].rgbtGreen;
        }
    }


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3];
    int gy[3][3];

    gx[0][0] = -1;
    gx[0][1] = 0;
    gx[0][2] = 1;
    gx[1][0] = -2;
    gx[1][1] = 0;
    gx[1][2] = 2;
    gx[2][0] = -1;
    gx[2][1] = 0;
    gx[2][2] = 1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            gy[i][j] = gx[j][i];
            //printf("%i\n", gy[i][j]);
        }
    }

    RGBTRIPLE(*image_copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    int amount_redx = 0;
    int amount_bluex = 0;
    int amount_greenx = 0;

    int amount_redy = 0;
    int amount_bluey = 0;
    int amount_greeny = 0;


    for (int i = 0; i < height; i++) //Passa por todos os pixels da linha
    {
        for (int j = 0; j < width; j++) //Passa pr todos os pixels da coluna
        {
            for (int x = i - 1, count_gx = 0; x <= i + 1; x++) //Inicia uma linha acima da linha do pixel inicial
            {
                for (int z = j - 1, count_gy = 0; z <= j + 1; z++) //Inicia uma coluna acima da linha do pixel inicial
                {
                    if (x >= 0 && z >= 0 && x < height & z < width) //Verifica se o pixel pode ser analisador
                    {
                        amount_redx += image[x][z].rgbtRed * gx[count_gx][count_gy];
                        amount_bluex += image[x][z].rgbtBlue * gx[count_gx][count_gy];
                        amount_greenx += image[x][z].rgbtGreen * gx[count_gx][count_gy];

                        amount_redy += image[x][z].rgbtRed * gy[count_gx][count_gy];
                        amount_bluey += image[x][z].rgbtBlue * gy[count_gx][count_gy];
                        amount_greeny += image[x][z].rgbtGreen * gy[count_gx][count_gy];
                    }
                    else
                    {
                        amount_redx += 0; //Todos os pixels não utilizados são zerados
                        amount_bluex += 0;
                        amount_greenx += 0;

                        amount_redy += 0;
                        amount_bluey += 0;
                        amount_greeny += 0;
                    }

                    if (z == j + 1 && x == i + 1) //Verifica se passou pelos 9 pixels ou menos
                    {
                        int amount_red_square = round(sqrt(pow(amount_redx, 2) + pow(amount_redy, 2)));
                        int amount_blue_square = round(sqrt(pow(amount_bluex, 2) + pow(amount_bluey, 2)));
                        int amount_green_square = round(sqrt(pow(amount_greenx, 2) + pow(amount_greeny, 2)));
                        //printf("ERROOOOO ----%i\n\n", amount_green_square);

                        amount_red_square > 255 ? amount_red_square = 255 : amount_red_square;
                        amount_blue_square > 255 ? amount_blue_square = 255 : amount_blue_square;
                        amount_green_square > 255 ? amount_green_square = 255 : amount_green_square;

                        image_copy[i][j].rgbtRed = amount_red_square;
                        image_copy[i][j].rgbtBlue = amount_blue_square;
                        image_copy[i][j].rgbtGreen = amount_green_square;

                        //printf("%i %i %i\n", image_copy[i][j].rgbtRed, image_copy[i][j].rgbtBlue, image_copy[i][j].rgbtGreen);

                        amount_redx = 0;
                        amount_bluex = 0;
                        amount_greenx = 0;

                        amount_redy = 0;
                        amount_bluey = 0;
                        amount_greeny = 0;

                    }

                    count_gy++;
                }

                count_gx++;
            }
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image_copy[i][j].rgbtRed;
            image[i][j].rgbtBlue = image_copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image_copy[i][j].rgbtGreen;
        }
    }

    return;
}
