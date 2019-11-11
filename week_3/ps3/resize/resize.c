/**
 * resize.c
 *
 * This program resizes (i.e., enlarges or shrinks)
 * 24-bit uncompressed BMPs by a factor of f.
 *
 */


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
    float f = atof(argv[1]);  // string to float
    char *infile = argv[2];
    char *outfile = argv[3];

    if (f < 0 || f > 100)
    {
        fprintf(stderr, "f must be a positive value less than or equal to 100.0\n");
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

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // new dimesions
    int w_i = abs(bi.biWidth);       // in
    int h_i = bi.biHeight;           // in, biHeight is negative, the image is top-down
    int w_o = w_i * f;               // out
    int h_o = h_i * f;               // out

    // padding for scanline
    int padding_i = (4 - (w_i * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_o = (4 - (w_o * sizeof(RGBTRIPLE)) % 4) % 4;

    // modify header
    bi.biWidth  = w_o;
    bi.biHeight = h_o;
    bi.biSizeImage = (sizeof(RGBTRIPLE) * w_o + padding_o) * abs(h_o);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // allocate memory to store one scanline
    RGBTRIPLE output[w_i][abs(h_i)];

    // iterate over infile's scanlines
    for (int i = 0, height = abs(h_i); i < height; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < w_i; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // store RGB triple to output array
            output[j][i] = triple;
        }

        // skip over padding, if any
        fseek(inptr, padding_i, SEEK_CUR);
    }

    // writing the new image to file
    for (int i = 0, new_height = abs(h_o); i < new_height; i++)
    {
        for (int j = 0; j < w_o; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // scale the number of pixel
            triple = output[(int)(j / f)][(int)(i / f)];

            // write the pixel to the file
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // write the buffer
        for (int k = 0; k < padding_o; k++)
        {
            fputc(0x00, outptr);
        }
    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
