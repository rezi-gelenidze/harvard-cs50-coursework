#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // checks if argument is given and it is digit
    // if argument is valid, text is encrypted
    // else program will print an error message
    if (argc == 2)
    {
        int arg_len = strlen(argv[1]);
        int check;
        // checks if characters are digits
        for (int i = 0; i < arg_len; i++)
        {
            check = isdigit(argv[1][i]);
        }
        // if argument characters are all digits, it is coverted to int
        // and used to encrypt user input later
        if (check != 0)
        {
            int key = atoi(argv[1]) % 26;

            // getting plaintext
            string text = get_string("plaintext: ");

            // encrypting (rotating) text
            for (int n = 0; n < strlen(text); n++)
            {
                if (text[n] >= 'a' && text[n] <= 'z')
                {
                    text[n] = 97 + ((text[n] - 97) + key) % 26;
                }
                else if (text[n] >= 'A' && text[n] <= 'Z')
                {
                    text[n] = 65 + ((text[n] - 65) + key) % 26;
                }
            }
            // printing ciphertext
            printf("ciphertext: %s\n", text);
        }
        // else error message is printed
        else
        {
            printf("Usage: ./cipher key\n");
            return 1;
        }
    }

    // else, error message will be printed and program will stop
    else
    {
        printf("Usage: ./cipher key\n");
        return 1;
    }

}