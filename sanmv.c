#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
void main(int argc, char *argv[])
{
	int link, file1, file2, filecount;
	char buffer[512];
	if (argc!=3)
	{
		printf ("Aruguments not specified\n");
		exit(1);
	}
	else
	{	
		file1=open(argv[1], O_RDONLY);
		if(file1==-1)
		{
			printf("The specified source file is not there in the directory\n");
		}
		file2=open(argv[2], O_WRONLY);
		if(file2==-1)
		{
			file2=creat(argv[2], 0777);
			while((filecount=read(file1, buffer, 512))>0)
			{
				write(file2, buffer, filecount);
			}
		}
		close(file1);
		close(file2);
		}
		link=unlink(argv[1]);
		if(link==0)
		{
			printf("Moved or Renamed Successfully\n");
		}
		else
		{
			printf("Move or Rename Error\n");
		}
}
