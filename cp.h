#ifndef cp_h
#define cp_h

#include <stdio.h>
#include <stdlib.h>


int cpFunc(char *argv1, char *argv2){
	FILE *fr = fopen(argv1, "rb");
	FILE *fw = fopen(argv2, "wb");

	if (!fr) {
		printf("Fail to READ file.\n");
		return 1;
	}

	if (!fw) {
		printf("Fail to WRITE file.\n");
		return 1;
	}

	char ch;

	while (!feof(fr)) {
		fread(&ch, sizeof(char), 1, fr);

		if (!feof(fr)) {
			fwrite(&ch, sizeof(char), 1, fw);
		}
	}

	fclose(fr);
	fclose(fw);

	printf("Copy \"%s\" to \"%s\".\n", argv1, argv2);
	
	return 0;
}

#endif

