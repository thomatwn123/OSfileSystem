#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include"mv.h"
void main(int argc, char *argv[])
{
	char *file1, *file2;
	if (argc!=3)
	{
		printf ("Aruguments not specified\n");
		exit(1);
	}
	else
	{
		file1= argv[1];
		file2= argv[2];
		mvFunc(file1, file2);
	}
}
			
