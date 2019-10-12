#include <cs50.h>
#include <stdio.h>

void pyramid(int i);

int main(void)
{
    int s = 0;
    s = get_int("Height: ");    
    // stay in this loop until Height entered is between 1 and 8
    while (s < 1 || s > 8)
    {
        s = get_int("Height: ");
    }
    pyramid(s);   
}

// this function creat the pyramid 
void pyramid(int n)
{
    int height_max = n;
    int row_max = n * 2 + 2;
    
    // height
    for (int i = 0; i < height_max; i++)
    {
        // row
        for (int j = 0; j < row_max; j++)
        {  
            // space left and gap
            if (i + j < n - 1 || j == n || j == n + 1)
            {
                printf(" ");    
            }
            // skip space right
            else if (row_max - j + i < n)
            {
                printf("");
            } 
            else 
            {
                printf("#");
            }
        }
        //print new line for next row
        printf("\n");  
    }
}
