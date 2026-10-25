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
 
void searchBook(void)
{
    FILE *fp;
    Book book;
    int searchId;
    int found = 0;

    fp = fopen("books.dat", "rb");

    if (fp == NULL)
    {
        printf("Unable to open library file.\n");
        return;
    }

    printf("Enter Book ID to search: ");
    scanf("%d", &searchId);

    while (fread(&book, sizeof(Book), 1, fp) == 1)
    {
        if (book.bookId == searchId)
        {
            printf("\nBook Found!\n");
            printf("Book ID: %d\n", book.bookId);
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
            printf("Total Copies: %d\n", book.totalCopies);
            printf("Available Copies: %d\n", book.availableCopies);

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("Book not found.\n");
    }

    fclose(fp);
}

void issueBook(void)
{
    FILE *fp;
    Book book;
    int searchId;
    int found = 0;

    fp = fopen("books.dat", "rb+");

    if (fp == NULL)
    {
        printf("Unable to open library file.\n");
        return;
    }

    printf("Enter Book ID to issue: ");
    scanf("%d", &searchId);

    while (fread(&book, sizeof(Book), 1, fp) == 1)
    {
        if (book.bookId == searchId)
        {
            found = 1;

            if (book.availableCopies > 0)
            {
                book.availableCopies--;

                fseek(fp, -(long)sizeof(Book), SEEK_CUR);
                fwrite(&book, sizeof(Book), 1, fp);

                printf("Book issued successfully!\n");
                printf("Available copies: %d\n",
                       book.availableCopies);
            }
            else
            {
                printf("No copies available to issue.\n");
            }

            break;
        }
    }

    if (found == 0)
    {
        printf("Book not found.\n");
    }

    fclose(fp);
}


