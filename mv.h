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
int i,fd1,fd2;
char buf[2];	

fd1=open(file1,O_RDONLY,0777);
if(fd1==-1)
{
printf("-----------------------------------------------------------------------\nThe specified source file is not there in the directory\n----------------------------------------------------------------------\n");
}
else
{
fd2=creat(file2,0777);
while(i=read(fd1,buf,1)>0)
write(fd2,buf,1);
printf("-----------------------------------------------------------------------\n%s got renamed or moved successfully to %s\n-----------------------------------------------------------------------\n",file1,file2);
remove(file1);

close(fd1);
close(fd2);
}
}		
#endif

