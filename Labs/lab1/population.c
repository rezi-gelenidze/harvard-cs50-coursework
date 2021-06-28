#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //Declare variables and get end-start size integer inputs from user
    // start_size >= 9, end_size >= start_size.
    int start_size;
    int end_size;

    do
    {
        start_size = get_int("Start Size:");
    }
    while (start_size < 9);

    do
    {
        end_size = get_int("End Size:");
    }
    while (end_size < start_size);


    //calculate gain and lost amount of 1 year
    int gained = 0;
    int lost = 0;
    int net_change = 0;
    int years = 0;

    int number_of_lammas = start_size;

    while (number_of_lammas < end_size)
    {
        gained = round(number_of_lammas / 3);
        lost = round(number_of_lammas / 4);
        net_change = gained - lost;

        number_of_lammas += net_change;
        years++;
    }

    //print answer
    printf("Years: %i\n", years);

}