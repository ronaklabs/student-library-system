#ifndef COMMON_H
#define COMMON_H

typedef struct {
  char rollNo[20];
  char name[50];
  char branch[20];
  int semester;
} Student;

typedef struct {
  int bookId;
  char title[100];
  char author[50];
  int totalCopies;
  int availableCopies;
} Book;

typedef struct {
  char rollNo[20];
  int bookId;
  char issueDate[20];
} IssueRecord;

#endif
