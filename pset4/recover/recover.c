#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;



int main(int argc, char *argv[])
{
    //Verifica se passou o nome do arquivo
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        return 1;
    }


    BYTE *buffer = malloc(512);
    int qtd_photos = 0;
    int jpeg_found = 1;
    int count = 0;
    char *filename = malloc(sizeof(char) * 3);
    FILE *img = NULL;

    while (fread(buffer, 512, 1, file)) //Enquanto o arquivo ainda tiver bytes rode
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) //É um JPEG
        {
            jpeg_found = 0;

            if (count == 0) //Primeiro JPEG?
            {
                sprintf(filename, "%03i.jpg", qtd_photos); //Cria o nome do arquivo
                printf("%s\n", filename);
                img = fopen(filename, "w");

                if (img == NULL)
                {
                    fprintf(stderr, "ERRO\n");
                    return 1;
                }

                fwrite(buffer, 512, 1, img); //Escreve o arquivo

                qtd_photos++;
                count++;
            }
            else
            {
                fclose(img);
                count = 0;
            }

        }
        else //Não é um JPEG
        {
            if (jpeg_found == 0)
            {
                fwrite(buffer, 512, 1, img);
                count = 0;
            }
        }

    }


    free(filename);
    free(buffer);
    fclose(file);
    fclose(img);

}