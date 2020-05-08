#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //Initialize image counter
    int jpg_count = 0;

    //Check for more than 1 argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //Open file and check if it is readable
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("file is not readable");
        return 1;
    }
    
    //Initialize image file to store each new found image
    FILE *img = NULL;

    //Create buffer
    unsigned char buff[512];
    
    //Initialize file name array
    char fname[8];
    
    //Read the file
    while(fread(buff, 512, 1, file) == 1)
    {
        if (buff[0] == 0xff && buff[1] == 0xd8 && buff[2] == 0xff && (buff[3] & 0xe0))
        {
            //Check if this is the first image found
            if (jpg_count == 0)
            {
                sprintf(fname, "%03i.jpg", jpg_count);
                img = fopen(fname, "wb");
                fwrite(&buff, sizeof(buff), 1, img);
            }
            //If it's not the first image found, close the old one and start writing to a new one.
            else
            {
                fclose(img);
                sprintf(fname, "%03i.jpg", jpg_count);
                img = fopen(fname, "wb");
                fwrite(&buff, sizeof(buff), 1, img);
            }
            jpg_count += 1;
        }
        //If we have already found 1 image then we shoudl still be writing to our current image
        else if (jpg_count > 0)
        {
            fwrite(buff, sizeof(buff), 1, img);
        }
    }
    
    fclose(img);
    //free(buff);
    fclose(file);

}
