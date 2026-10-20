#include <stdio.h>
#include "library.h"

void addBook(void)
{
   Book b;
   FILE *fp;

   printf("Enter Book ID:  ");
   scanf("%d", &b.bookId);

   printf("Enter Book Title:  ");
   scanf(" %99[^\n]",&b.title);

   printf("Enter the Authors name: ");
   scanf(" %49[^\n]",&b.author);

   printf("Total no.s of copies:   ");
   scanf(" %d",&b.totalCopies);

   if(b.totalCopies <= 0)
   {
     printf("Ivalid number of copies!!\n");
     return;
 

   }

   
   b.availableCopies = b.totalCopies;
   
   fp = fopen("books.dat", "ab");

   if(fp == NULL)
   {
    printf("Error opening file!\n");
    return;
   }
   
   if(fwrite(&b, sizeof(Book), 1, fp) !=1)
   {
      printf("Error saving the Book: \n");
      fclose(fp);
      return;

   }
   
   if(fclose(fp) != 0)
   {
      printf("Error closing the file !! \n");
      return;

   }
     
    printf("The Book added sucessfully! \n");
}  

void viewBooks(void)
{ 
   FILE *fp;
   Book book;
   int count = 0;
   
   fp = fopen("books.dat", "rb");
   
   if(fp == NULL)
   {
    printf("Error opening file!\n");
    return;
   }
   while(fread(&book, sizeof(Book), 1, fp) == 1)
   {
         count++; 
   }
      if(count == 0)
      {
      printf("No books fount in the library. \n");
      return;      
      }
    
       rewind(fp);

      printf("%-6s %-25s %-20s %-8s %-10s\n",
    "ID", "Title", "Author", "Total", "Available");
   printf("----------------------------------------------------------------------------------------------------------------\n");
   
    while(fread(&book, sizeof(Book), 1, fp) == 1)
   {
         printf("%-6d %-25s %-20s %-8d %-10d\n",
         book.bookId,
         book.title, 
         book.author,
         book.totalCopies,
         book.availableCopies);
   }
     fclose(fp);
}


