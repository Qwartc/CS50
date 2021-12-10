#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // обеспечиваем правильное использование
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    //Получаем n из пользовательского ввода
    int n = atoi(argv[1]);

    //Убеждаемся, что n от 0 до 100
    if (n < 0 || n > 100)
    {
        printf("Usage: ./resize n infile outfile\n");

        return 5;
    }

    // Запомнаем имена файлов.
    char *infile = argv[2];
    char *outfile = argv[3];

    // Открываем входной файл.
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "%s.\n", infile);
        return 2;
    }

    // Открываем выходной файл.
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "%s.\n", outfile);
        return 3;
    }

    // Читаем BITMAPFILEHEADER infile и устанавливаем равный ему BITMAPHEADERFILE.
    BITMAPFILEHEADER bf, bfR;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bfR = bf;

    // Читаем BITMAPINFOHEADER infile и устанавливаем равный ему BITMAPINFOHEADER.
    BITMAPINFOHEADER bi, biR;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    biR = bi;

    //Задаем файлы заголовка выходного файла для настройки по значению изменения размера.
    biR.biWidth = bi.biWidth * n;
    biR.biHeight = bi.biHeight * n;

    // Проверяем, что infile (вероятно) является 24-битным несжатым BMP 4.0.
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
  
     // Определяем отступы для строк развертки для infile и outfile.
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outPadding = (4 - (biR.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //Новый размер изображения.
    bfR.bfSize = 54 + biR.biWidth * abs(biR.biHeight) * 3 + abs(biR.biHeight) *  outPadding;
	biR.biSizeImage = ((((biR.biWidth * biR.biBitCount) + 31) & ~31) / 8) * abs(biR.biHeight);

    // Записываем файл BITMAPFILEHEADER.
    fwrite(&bfR, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Записываем файл BITMAPINFOHEADER.
    fwrite(&biR, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Перебираем сканы строк в infile.
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Перебираем пиксели в линии сканирования.
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < bi.biWidth; k++)
            {
                // Создаем временное хранилище.
                RGBTRIPLE triple;

                // Читаем тройной RGB из infile.
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // Пишем тройной RGB в выходной файл n раз.
                for (int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // Добавляем отступы.
            for (int m = 0; m < outPadding; m++)
            {
                fputc(0x00, outptr);
            }

            if (j < n - 1)
            {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }

        // Пропускаем заполнение, если они есть
        fseek(inptr, padding, SEEK_CUR);
      }
      fclose(inptr);

     fclose(outptr);

    return 0;
}