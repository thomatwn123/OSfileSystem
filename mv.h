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
		int link;
		FILE *f1;
		FILE *f2;
		f1=fopen(file1, "wrb+");
		if(file1==NULL)
		{
			printf("The specified source file is not there in the directory\n");
		}
		f2=fopen(file2, "awb+");
		if(file2==NULL)
                {
			int filecount;
			char buffer[512];
			f2=fopen(file2, "awb+");

                        while((filecount=fread(file1, 1, sizeof(file1), f1))>0)
                        {
                                fwrite(file2, filecount, sizeof(file2), f2);
                        }
                }
		fclose(f1);
		fclose(f2);
		
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

