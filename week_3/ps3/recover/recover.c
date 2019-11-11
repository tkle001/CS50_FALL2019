/**
 * recover.c
 *
 * This program recovers JPEGs
 * https://docs.cs50.net/2019/x/psets/3/recover/recover.html
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
const int SIZE = 512;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    BYTE block[SIZE];
    int nImagesRecovered = 0;
    FILE *outptr = NULL;
    char filename[0];
    //bool foundImg = false;

    while (fread(&block, sizeof(block), 1, inptr) != 0)
    {
        // looking for JPEG signatures
        // each photo is stored immediately after the previously taken photo
        if (block[0] == 0xFF && block[1] == 0xD8 && block[2] == 0xFF && block[3] >> 4 == 0xE)
        {

            // close previous file (if any)
            if (nImagesRecovered > 0)
            {
                fclose(outptr);
            }

            // new file
            sprintf(filename, "%03d.jpg", nImagesRecovered);

            // open file
            outptr = fopen(filename, "w");

            // count the number of images found/recoverd
            nImagesRecovered++;
        }

        // write blocks to file
        if (nImagesRecovered > 0)
        {
            fwrite(&block, 512, 1, outptr);
        }
    }
    printf("%i\n", nImagesRecovered);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;

}
