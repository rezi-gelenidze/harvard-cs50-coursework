#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // checking argument

    // checking argument existence
    if (argc == 2)
    {
        // checking argument length
        if (strlen(argv[1]) != 26)
        {
            printf("26 chars are needed\n");
            return 1;
        }

        // looping through each character for more checks and operations
        for (int n = 0; n < 26; n++)
        {
            // checking if character is a letter
            if (isalpha(argv[1][n]) == 0)
            {
                printf("alphabet letters only\n");
                return 1;
            }

            // converting letter to lowercase if letter is uppercase
            if (islower(argv[1][n]) == 0)
            {
                argv[1][n] = tolower(argv[1][n]);
            }

            // another loop to check if all letters are unique
            for (int i = 0; i < 26; i++)
            {
                if (i == n)
                {
                    i++;
                }
                else if (argv[1][n] == argv[1][i])
                {
                    printf("enter different letters only\n");
                    return 1;
                }
            }
        }
    }
    else
    {
        printf("usage: ./program key\n");
        return 1;
    }

    // if argument is valid, program will continue working
    // and will recieve plaintext, enctypt and return ciphertext
    // else, program will print an error message and stop working

    // getting plaintext
    string text = get_string("plaintext: ");

    string alph = "abcdefghijklmnopqrstuvwxyz";

    // encryption
    for (int a = 0; a < strlen(text); a++)
    {
        for (int b = 0; b < 26; b++)
        {
            if (tolower(text[a]) == alph[b])
            {
                if (islower(text[a]) == 0)
                {
                    text[a] = toupper(argv[1][b]);
                    break;
                }
                else
                {
                    text[a] = argv[1][b];
                    break;
                }
            }
        }
    }
    // print ciphertext
    printf("ciphertext: %s\n", text);
}