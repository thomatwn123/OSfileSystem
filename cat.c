#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define LINELEN 256

void copy_file(FILE *fin, FILE* fout, int writeLineNumbers);

int main(int argc, char *argv[]){
    char cpr[]= "-n";
    FILE *fp;
    
    if(argc >1){
		if(strcmp(cpr,argv[1])!=0){
			if((fp= fopen(argv[1], "r"))!=NULL){
				copy_file(fp, stdout, 0);
				fclose(fp);
				exit(1);
			}
			else{
				perror("could not open the file.");
				exit(1);
			}
		}
	}
    if(argc==1){
        copy_file(stdin, stdout, 0);
        exit(1);
    }
    else{
        if(argc==2){
			copy_file(stdin, stdout, 1);
            exit(1);
        }
        else{
            if((fp= fopen(argv[2], "r"))!=NULL){
                copy_file(fp, stdout, 1);
                fclose(fp);
                exit(1);
            }
            else{
				perror("could not open the file.");
                exit(1);
            }
        }
    }
   return 0;
}

void copy_file(FILE *fin, FILE* fout, int writeLineNumbers){
    char line[LINELEN];
    int lineno = 1;
    while (fgets(line, LINELEN, fin)){
        if(writeLineNumbers) printf("%d ", lineno);

        if(fputs(line, fout) == EOF){
			perror("Write to stdout failed.");
            return;
        }
        ++lineno;
    }
}