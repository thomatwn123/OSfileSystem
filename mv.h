#ifndef mv_h
#define mv_h

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

//insert the two file names (file1 and file 2; file1 is file which has to moved to new folder as file2) 
void mvFunc(char* file1, char* file2)
{	
	int f1, f2, link;
		f1=open(file1, O_RDONLY);
		if(file1==NULL)
		{
			printf("The specified source file is not there in the directory\n");
		}
		f2=open(file2, O_WRONLY);
		if(file2==NULL)
                {
			int filecount;
			char buffer[512];
                        f2=creat(file2, 0777);
                        while((filecount=read(f1, buffer, 512))>0)
                        {
                                write(f2, buffer, filecount);
                        }
                }
		close(f1);
		close(f2);
		
	link=unlink(file1);
        if(link==0)
	{
		printf("Moved or Renamed Successfully\n");
        }
        else
        {
            	printf("Move or Rename Error\n");
        }
}
#endif

