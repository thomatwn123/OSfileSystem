#ifndef rm_h
#define rm_h

#include <stdio.h>

void rmFunc()
{
   int status;
   char file_name[25];
    
	// enter the file name with location
   
   printf("Enter the name of file you want to delete\n");
   gets(file_name);

   status = remove(file_name);

   if( status == 0 )
      printf("%s file deleted successfully.\n",file_name);
   else
   {
      printf("Unable to delete the file\n");
      perror("Error");
   }

   return 0;
}

#endif
