#include <stdio.h>
#include <cs50.h>

/*

C program which gets input as an user name
and uses this name to greet the user

[Hello problem from CS50x Problem Set1]

[Created by: Rezi Gelenidze]

This is CS50 :)

*/

int main(void)
{
    string name = get_string("What is your name?\n:");
    printf("Hello, %s\n", name);
}