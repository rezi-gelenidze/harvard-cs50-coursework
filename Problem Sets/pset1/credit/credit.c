#include <stdio.h>
#include <cs50.h>

/*
    [Credit Card Number Validator]

C program which calculates checksum with Luhn’s Algorithm
and validates card number. Also it determines its type
        (Visa, Mastercard or American Express)

[Credit problem from CS50x Problem Set1]

[Created by: Rezi Gelenidze]

This is CS50 :)
*/




int get_number_length(long num);

int main(void)
{
    long numbers;

    // get postive credit card number input
    do
    {
        numbers = get_long("Card Number: ");
    }
    while (numbers < 0);

    // determine number length
    int num_length = get_number_length(numbers);

    // add number's each digit to an array
    int digits[num_length];
    int digit;


    for (int i = 0; i < num_length; i++)
    {
        digit = numbers % 10;
        numbers -= digit;
        numbers /= 10;
        digits[i] = digit;
    }

    // determine number's first two digits
    int first_digit = digits[num_length - 1];
    int second_digit = digits[num_length - 2];

    // declare digit set arrays
    int set1_len;
    int set2_len;

    // determine digit set array lengths
    if (num_length % 2 == 0)
    {
        set1_len = num_length / 2;
        set2_len = num_length / 2;

    }
    else
    {
        int len = num_length + 1;
        set1_len = len / 2;
        set2_len = len / 2 - 1;
    }

    // create number set arrays and add digits into them
    int set1[set1_len];
    int set2[set2_len];

    // putting numbers in set1
    for (int a = 0, b = 0; a < num_length; a += 2, b++)
    {
        set1[b] = digits[a];
    }

    // putting numbers in set2
    for (int x = 1, y = 0; x < num_length; x += 2, y++)
    {
        set2[y] = digits[x];
    }

    // calculate sum of set1 digits
    int set1_sum = 0;

    for (int t = 0; t < set1_len; t++)
    {
        set1_sum += set1[t];
    }


    // process set2 digits

    // multiply all numbers by 2
    // and determine number of digits

    int set2_digit_num = 0;

    for (int d = 0; d < set2_len; d++)
    {
        set2[d] *= 2;

        if (set2[d] < 10)
        {
            set2_digit_num++;
        }
        else
        {
            set2_digit_num += 2;
        }
    }

    // putting every single digit in an array set2_digits

    int set2_digits[set2_digit_num];

    for (int f = 0, p = 0; f < set2_len; f++, p++)
    {
        if (set2[f] < 10)
        {
            set2_digits[p] = set2[f];
        }
        else
        {
            set2_digits[p] = set2[f] % 10;
            set2_digits[p + 1] = 1;
            p++;
        }
    }

    // calculate set2 digit sum

    int set2_sum = 0;

    for (int q = 0; q < set2_digit_num; q++)
    {
        set2_sum += set2_digits[q];
    }


    // get final result
    int result = set2_sum + set1_sum;



    // if number is valid, determine card type. Else print "INVALID"
    if (result % 10 == 0)
    {
        if ((num_length == 13 || num_length == 16) && (first_digit == 4))
        {
            printf("VISA\n");
        }
        else if ((num_length == 16) && (first_digit == 5) && (second_digit == 1 || second_digit == 2 || second_digit == 3
                 || second_digit == 4 || second_digit == 5))
        {
            printf("MASTERCARD\n");
        }
        else if ((num_length == 15) && (first_digit == 3) && (second_digit == 4 || second_digit == 7))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}


// calculates length of given long number
int get_number_length(long num)
{
    int n = 0;
    while (num > 0)
    {
        num /= 10;
        n++;
    }

    return n;
}


