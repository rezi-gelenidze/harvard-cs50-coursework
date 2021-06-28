#include <stdio.h>
#include <math.h>
#include <cs50.h>
#include <string.h>

void count(string txt);
void calculate_index_and_print_grade();

float letters = 0, words = 0, sentences = 0;

int main(void)
{
    // get text as input
    string text = get_string("Text: ");

    // calling functions to proccess text
    count(text);
    calculate_index_and_print_grade();
}

// receives text and determines numbers of sentences words and letters
void count(string txt)
{
    int i = 0;

    while (txt[i] != '\0')
    {
        // Counting letters
        if ((txt[i] >= 'a' && txt[i] <= 'z') ||
            (txt[i] >= 'A' && txt[i] <= 'Z'))
        {
            letters++;
        }
        // Counting sentences
        if (txt[i] == '.' || txt[i] == '!' || txt[i] == '?')
        {
            sentences++;
        }
        // Counting words
        if (((txt[i] == ' ') || (txt[i - 1] == '\0')) && (txt[i + 1] != ' '))
        {
            words++;
        }

        i++;
    }
}

// Calculates index and prints results
void calculate_index_and_print_grade()
{
    // Calculating Index
    float s = (sentences / words) * 100;
    float l = (letters / words) * 100;

    int index = round(0.0588 * l - 0.296 * s - 15.8);


    // Checking index value and determining what to print as the result
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}