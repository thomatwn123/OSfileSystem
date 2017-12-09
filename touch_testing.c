#include <stdio.h>
#include <stdlib.h>
#include "touch.h"

int main(int argc, char *argv[])
{
    FILE *fptr;
    char* path = argv[1];

    if(argc == 1)
    {
        printf("Please inster a file name\n");
        exit(1);
    }
    else
    {   
        touchFunc(path);
    }
    return 0;
}
