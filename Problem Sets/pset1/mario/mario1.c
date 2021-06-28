#include <stdio.h>
#include <cs50.h>

int height;

int main(void)
{
    //Using do-while loop to get a number from
    //user between 1 and 8.
    do
    {
        //getting int and assigning it to a variable height
        height = get_int("Height: ");

        //boolean expression checks user unput.If a number is greater
        //than 8 or less than 1, it will get an input again
    }
    while (height > 8 || height < 1);


    //using for loops to print right-aligned pyramid

    for (int row = 1; row <= height; row++)
    {

        for (int space = 0; space < (height - row); space++)
        {
            //printing specific number of spaces to right-align pyramid left pyramid
            printf(" ");
        }

        //printing left side pyramid
        for (int hash = 0; hash < row; hash++)
        {
            printf("#");
        }

        //making gap between pyramids
        printf("  ");

        //printing right side pyramid
        for (int hash = 0; hash < row; hash++)
        {
            printf("#");
        }


        printf("\n");
    }
}