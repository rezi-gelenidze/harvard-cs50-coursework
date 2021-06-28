#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

// gets command line arguments as numbers, sort and outputs them with selection sort algorithm
int main(int argc, string argv[])
{
    int length = argc - 1;
    // creating array of numbers and storing command line arguments (numbers) in as integers
    int numbers[length];

    for (int i = 0; i < length; i++)
    {
        numbers[i] = atoi(argv[i + 1]);
    }

    //writing selection sort algorithm
    for (int n = 0; n < length; n++)
    {
        int lowest = n;

        for (int c = n + 1; c < length; c++)
        {
            if (numbers[c] < numbers[lowest])
            {
                lowest = c;
            }
        }

        if (lowest != n)
        {
            numbers[n] += numbers[lowest];
            numbers[lowest] = numbers[n] - numbers[lowest];
            numbers[n] -= numbers[lowest];
        }
    }

    // printing sorted array numbers
    for(int j = 0; j < length; j++)
    {
        printf("%i\n", numbers[j]);
    }
}