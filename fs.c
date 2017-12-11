/*
	Program	: Simple File System (fs.c)
	Compiled: 11 December 2017
*/

#include "header.h"
#include <string.h>

#define BUFFSIZE 30
#define CMD_PARAM_LIMIT 10

void printWelcome();
void printHelp();
void callFunc(char*);

int main(int argc, char *argv[]){	
	char inputCmd[BUFFSIZE];

	printWelcome();

	while(1){
		// Get user input
		printf("%% ");
		fgets(inputCmd, BUFFSIZE, stdin);
		callFunc(inputCmd);
	}

	return 0;
}

void printWelcome(){
	printf("Welcome to the Simple File System!\n");
	printf("** Type in 'h' for help, and 'exit' to leave\n");
	fflush(stdout);
	return;
}

void printHelp(){
	printf("Supported commands are as follows:\n");
	printf("- ls\n");
	printf("- rm\n");
	printf("- mv\n");
	printf("- touch <filename>\n");
	printf("- cat\n");
	printf("- cp\n");
	printf("- exit\n");
}

void callFunc(char *inputCmd){
	// Trim '\n'
	inputCmd[strlen(inputCmd) - 1] = '\0';

	// Check for exit
	if(strcmp(inputCmd, "exit") == 0)
		exit(0);

	char *token, temp[BUFFSIZE];
	char *inputCmdArr[BUFFSIZE];
	int i = 0;

	// Parse the input commands, and store them in str array
	token = strtok(inputCmd, " ");
	while(token != NULL){
		inputCmdArr[i++] = token;
		token = strtok(NULL, " ");
	}

	if(strcmp(inputCmdArr[0], "ls") == 0){
		
	}
	else if(strcmp(inputCmdArr[0], "rm") == 0){

	}
	else if(strcmp(inputCmdArr[0], "mv") == 0){

	}
	else if(strcmp(inputCmdArr[0], "touch") == 0){
		touchFunc(inputCmdArr[1]);
	}
	else if(strcmp(inputCmdArr[0], "cat") == 0){

	}
	else if(strcmp(inputCmdArr[0], "cp") == 0){
		cpFunc(inputCmdArr[1], inputCmdArr[2]);
	}
	else{
		printHelp();
	}
		
	return;
}

















