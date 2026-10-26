
#include "common.h"
#include <stdio.h>
// #include <stdlib.h>
#include <string.h>

#include "student.h"

int studentExists(const char *rollNo) {
  Student student;
  FILE *studentfile = fopen("students.dat", "rb");

  if (studentfile == NULL) {
    return 0;
  }

  while (fread(&student, sizeof student, 1, studentfile) == 1) {
    if (strcmp(rollNo, student.rollNo) == 0) {
      fclose(studentfile);

      return 1;
    }
  }

  fclose(studentfile);

  return 0;
}

void addStudent(void) {
  Student newStudent;

  printf("Enter the name of the student: ");
  fgets(newStudent.name, sizeof newStudent.name, stdin);
  newStudent.name[strcspn(newStudent.name, "\n")] = '\0';

  printf("Enter the student's roll no: ");
  fgets(newStudent.rollNo, sizeof newStudent.rollNo, stdin);
  newStudent.rollNo[strcspn(newStudent.rollNo, "\n")] = '\0';

  printf("Enter the branch of the student: ");
  fgets(newStudent.branch, sizeof newStudent.branch, stdin);
  newStudent.branch[strcspn(newStudent.branch, "\n")] = '\0';

  printf("Enter the Semester: ");
  if (scanf("%d", &newStudent.semester) != 1) {
    printf("Error! the value input is incorrect. Please choose and integer!");
  }

  if (newStudent.semester <= 0) {
    printf("Invalid semester! Please choose an interger greater than zero!");
    return;
  }

  if (studentExists(newStudent.rollNo)) {
    printf("The Student Already Exists!");
    return;
  }

  FILE *studentDetails = fopen("students.dat", "ab");

  if (studentDetails == NULL) {
    printf("File could not be opened!");
    return;
  }

  if (fwrite(&newStudent, sizeof newStudent, 1, studentDetails) != 1) {
    printf("Could not write to the file!");
    return;
  }

  if (fclose(studentDetails) != 0) {
    printf("Could not close this file!");
    return;
  }
}

void viewStudents(void) {
  Student student;
  int count = 0;

  FILE *fp = fopen("students.dat", "rb");
  if (fp == NULL) {
    printf("\nNo student records found yet.\n");
    return;
  }

  printf("\n");
  printf("+--------------------------------------------------------------------"
         "--------+\n");
  printf("|                            STUDENT DIRECTORY                       "
         "        |\n");
  printf("|                       Registered student records                   "
         "        |\n");
  printf("+--------------+--------------------------+----------------------+---"
         "--------+\n");
  printf("| ROLL NUMBER  | NAME                     | BRANCH               | "
         "SEMESTER  |\n");
  printf("+--------------+--------------------------+----------------------+---"
         "--------+\n");

  while (fread(&student, sizeof student, 1, fp) == 1) {
    printf("| %-12.12s | %-24.24s | %-20.20s | %8d  |\n", student.rollNo,
           student.name, student.branch, student.semester);

    count++;
  }

  printf("+--------------+--------------------------+----------------------+---"
         "--------+\n");

  if (count == 0) {
    printf("|                         NO STUDENT RECORDS FOUND                 "
           "          |\n");
  } else {
    printf("| TOTAL REGISTERED STUDENTS:%-48d |\n", count);
  }

  printf("+--------------------------------------------------------------------"
         "--------+\n");

  fclose(fp);
}
