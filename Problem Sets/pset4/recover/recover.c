#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check if there is exactly one command line argument
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    // assign given command line argument as a name of file to string filename
    char *filename = argv[1];

    // opening file in read mode
    FILE *file = fopen(filename, "r");

    // if file did not open, program quits with erroe message
    if (!file)
    {
        printf("Could not open file.");
        return 1;
    }

    // buffer to store each 512 byte block, when we read it
    BYTE buffer[512];

    // Return value of fread() (used later)
    int i = 0;

    // counter of found JPEGs
    int found = 0;

    // output file name
    char ofilename[8];

    // output file pointer declaration
    FILE *ofile = NULL;

    // search for JPEGs while we are not at the end of the file
    while (1)
    {
        // reading file and assigning return value to i
        // if all bytes are read it returns 1, else 0
        i = fread(buffer, sizeof(BYTE), 512, file);

        // checking if all bytes are read, else quit
        if (!i)
        {
            break;
        }

        // check if block contains start of JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 &&
            buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if we found JPEG we close previous if it is not the first
            if (ofile != NULL)
            {
                fclose(ofile);
            }

            // get output file name
            sprintf(ofilename, "%03i.jpg", found);

            // create new JPEG
            ofile = fopen(ofilename, "w");

            // add 1 toy found counter
            found++;
        }

        // if file is created
        if (ofile != NULL)
        {
            // write block of data in it
            fwrite(buffer, sizeof(BYTE), 512, ofile);
        }
    }

    // close files

    if (ofile != NULL)
    {
        fclose(ofile);
    }

    fclose(file);

    return 0;
}
