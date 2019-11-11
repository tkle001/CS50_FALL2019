# Questions

## What's `stdint.h`?

C header file that declare sets of integer types having specified widths, along with the defined min and max values for each type, using macros.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

These are unsigned and signed integer types from stdint.h 
Using well-defined types make code easier to understand and interpret 

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE    = 1 bytes
DWORD   = 4 bytes (32 bits)
LONG    = 4 bytes (64 bits)
WORD    = 2 bytes (16 bits)

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The first 2 bytes of the BMP file format are the character "B" then the character "M" in ASCII encoding. All of the integer values are stored in little-endian format (i.e. least-significant byte first). The header field used to identify the BMP and DIB file is 0x42 0x4D in hexadecimal same as BM in ASCII.

## What's the difference between `bfSize` and `biSize`?

bfSize - The number of bytes of the bitmap file.
biSize - The number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

If biHeight is positive, the image is bottom-up. 
If biHeight is negative, the image is top-down.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in `copy.c`?

Beacuse the file that fopen() is trying to get doesn't exist

## Why is the third argument to `fread` always `1` in our code?

The third argument in fread() tells you how many "block" (i.e. number of members) to read. Since there is only one file header and one info header, the third argument is always 1. 

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

size of RGBTRIPLE = 3
=> (4 - ((3*3) % 4)) % 4
=> (4 - (9 % 4)) % 4
=> (4 - 1) % 4
=> 3 % 4 
=> 3
padding = 3

## What does `fseek` do?

It allows you to rewind or fast forward within a file

## What is `SEEK_CUR`?

It moves file pointer position to given location.
In this problem set, it skip over padding, if any 
    fseek(inptr, padding, SEEK_CUR);

