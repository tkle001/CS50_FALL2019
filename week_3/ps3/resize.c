// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char *n = argv[1];
    char *infile = argv[2];
    char *outfile = argv[3];

    // string to int
    int num = atoi(n);

    if (num < 0 || num > 100)
    {
        fprintf(stderr, "n must be a positive integer less than or equal to 100\n");
        return 2;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // new dimesions
    int w_i = abs(bi.biWidth);       // in
    int h_i = abs(bi.biHeight);      // in
    int w_o = w_i*n;            // out
    int h_o = h_i*n;            // out

    // padding for scanline
    int padding_i = (4 - (w_i * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_o = (4 - (w_o * sizeof(RGBTRIPLE)) % 4) % 4;

    // modify header
    bi.biWidth  = w_o;
    bi.biHeight = h_o;
    bi.biSizeImage = (size(RGBTRIPLE)*w_o + padding_o) * h_o;
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // allocate memory to store one scanline
    RGBTRIPLE scanline[w_o * sizeof(RGBTRIPLE)];

    // determine padding for scanlines
    // int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0; i < h_i; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < w_i; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // store triple in scanline array
            for (int k = 0; k < num; k++)
            {
                scanline[(j*num) + k] = triple;
                // write RGB triple to outfile
                fwrite(scanline, sizeof(RGBTRIPLE), w_o, outptr);

                for (int l = 0; l < padding_o; k++)
                {
                    fputc(0x00, outptr);
                }
            }
        }

        // skip over padding, if any
        fseek(inptr, padding_i, SEEK_CUR);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
