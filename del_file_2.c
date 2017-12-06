
#include<stdio.h>

main()
{
   int status;
   char Operation[25];
   char file_name[25];

   printf("Type the keyword to perform the following operations\n\n");
   printf("OpFILE --> File to OPEN\n");
   printf("ClsFILE --> File to CLOSE\n");
   printf("CopFILE --> File to COPY\n");
   printf("RenFILE --> File to RENAME\n");
   printf("DelFILE --> File to DELETE\n\n");

   gets(Operation);


   while(1)
   {

   if(strcmp(Operation,"DelFILE")== 0)
   {
       printf("Enter the name of file you wish to delete\n\n");
   gets(file_name);

   status = remove(file_name);

   if( status == 0 )
      printf("%s file deleted successfully.\n",file_name);
   else
   {
      printf("Unable to delete the file\n");
      perror("Error");
      printf("Please choose the operation again\n\n");
      gets(Operation);
   }

   }

   else if(strcmp(Operation,"OpFILE")== 0)
   {
     printf("Under Construction\n");
     printf("Please choose the operation again\n\n");
       gets(Operation);

   }


   else if(strcmp(Operation,"ClsFILE")== 0)
   {
      printf("Under Construction\n");
      printf("Please choose the operation again\n\n");
       gets(Operation);
   }

    else if(strcmp(Operation,"CopFILE")== 0)
   {
      printf("Under Construction\n");
      printf("Please choose the operation again\n\n");
      gets(Operation);
   }
     else if(strcmp(Operation,"RenFILE")== 0)
   {
       printf("Under Construction\n");
       printf("Please choose the operation again\n\n");
       gets(Operation);

   }

   else
   {
       printf("Please choose the operation again\n\n");
       gets(Operation);
   }
   }

   return 0;
}
