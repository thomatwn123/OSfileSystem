#ifndef touch_h
#define touch_h

#include <stdio.h>
#include <stdlib.h>

//inster the file name (path) 
void touchFunc(char* path)
{
    if(!path)
    {
        printf("Please inster a file name\n");
        exit(1);
    }
    else
    {    
        FILE *fptr;
        fptr = fopen(path, "rb+");
        if(fptr == NULL)
        {
            fptr = fopen(path, "wb");
            printf("Creating the File...\n");   
        }
        else
        {
            printf("The file is already existed.\n");
        }

        fclose(fptr);
    }
}

#endif
