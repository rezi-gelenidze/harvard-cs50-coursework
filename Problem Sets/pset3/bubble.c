#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

// gets command line arguments as numbers, sort and outputs them with bubble sort algorithm
int main(int argc, string argv[])
{
    // creating array of numbers and storing command line arguments (numbers) in as integers
    int numbers[argc - 1];

    for (int i = 0; i < argc -1; i++)
    {
        numbers[i] = atoi(argv[i + 1]);
    }

    //writing bubble sort algorithm
    for (int n = 0; n < argc - 1; n++)
    {
        for (int a = (argc - 2) - n, b = 0; b < a; b++)
        {
            if (numbers[b] > numbers[b + 1])
            {
                //swapping numbers
                numbers[b] += numbers[b + 1];
                numbers[b + 1] = numbers[b] - numbers[b + 1];
                numbers[b] -= numbers[b + 1];
            }
        }
    }

    // printing sorted array numbers
    for (int j = 0 ; j < argc - 1; j ++)
    {
        printf("%i\n", numbers[j]);
    }
}