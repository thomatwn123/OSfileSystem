#ifndef cat_h
#define cat_h

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define LINELEN 256



void copy_file(FILE *fin, FILE* fout);
void create_file(FILE *fin);

void catFunc(char* path,int x){ //x==0 open file ; x==1 create new file
    char cpr[]= "-n";
    FILE *fp;
    
	if(path){
		if(strcmp(cpr,path)!=0){
			if(x==0)
				if((fp= fopen(path, "r"))!=NULL){
					copy_file(fp, stdout);
					fclose(fp);
					exit(1);
				}
			if(x==1)
				if ((fp= fopen(path, "a"))!=NULL){
					create_file(fp);
					fclose(fp);
					exit(1);
				}
			else{
				perror("could not open the file.");
				exit(1);
			}
		}
	}
    if(!path){
        copy_file(stdin, stdout);
        exit(1);
    }
	
    
}



void copy_file(FILE *fin, FILE* fout){
    char line[LINELEN];
    int lineno = 1;
    while (fgets(line, LINELEN, fin)){
      
        if(fputs(line, fout) == EOF){
			perror("Write to stdout failed.");
            return;
        }
        ++lineno;
    }
}

void create_file(FILE *fin){
	char line[LINELEN];
    int lineno = 1;
	
    while (fgets(line, LINELEN, stdin)){
		fputs (line,fin);
	}
	
}
#endif