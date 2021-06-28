#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // declaring input variable to then
    // get an amount of change in float
    float input;
    // declaring and assigning given number of coins to 0
    int coins = 0;

    do
    {
        // getting positive float number from user
        input = get_float("Change owed: $");
    }
    while (input < 0);

    // converting input to an amount of cents
    int change = round(input * 100);

    // calculating optimal number of coins to give

    // While change amount is bigger than the specific coin value
    // (starting from 25 to 1) it keeps decrementing change value
    // with coin value and then adds 1 to the number of coins variable each time.

    while (change >= 25)
    {
        change -= 25;
        coins++;
    }
    while (change >= 10)
    {
        change -= 10;
        coins++;
    }
    while (change >= 5)
    {
        change -= 5;
        coins++;
    }
    while (change >= 1)
    {
        change -= 1;
        coins++;
    }

    // printing total number of cents
    printf("%i\n", coins);

}

