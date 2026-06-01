#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int id;
    char name[100];
    float cgpa;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int inputInt(char message[]);
float inputCGPA(char message[]);
void clearInput();

void clearInput()
{
    while(getchar() != '\n');
}

int inputInt(char message[])
{
    int value;

    while(1)
    {
        printf("%s", message);

        if(scanf("%d", &value) == 1)
        {
            clearInput();
            return value;
        }

        printf("Sorry! Numbers only.\n");
        clearInput();
    }
}

float inputCGPA(char message[])
{
    float value;

    while(1)
    {
        printf("%s", message);

        if(scanf("%f", &value) == 1)
        {
            clearInput();

            if(value >= 0.00 && value <= 4.00)
            {
                return value;
            }

            printf("Sorry! CGPA must be between 0.00 and 4.00\n");
        }
        else
        {
            printf("Sorry! Numbers only.\n");
            clearInput();
        }
    }
}

int main()
{
    int choice;

    while(1)
    {
        printf("\n========== STUDENT MANAGEMENT SYSTEM ==========\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        choice = inputInt("\nEnter your choice: ");

        switch(choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            printf("Exiting Program...\n");
            exit(0);

        default:
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}

void addStudent()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.txt", "a");

    if(fp == NULL)
    {
        printf("File could not be opened!\n");
        return;
    }

    s.id = inputInt("\nEnter Student ID: ");

    printf("Enter Student Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    s.cgpa = inputCGPA("Enter Student CGPA: ");

    fprintf(fp, "%d|%s|%.2f\n",
            s.id, s.name, s.cgpa);

    fclose(fp);

    printf("Student Added Successfully!\n");
}

void displayStudents()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.txt", "r");

    if(fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("\n========== STUDENT RECORDS ==========\n");

    while(fscanf(fp, "%d|%99[^|]|%f\n",
                 &s.id, s.name, &s.cgpa) == 3)
    {
        printf("ID   : %d\n", s.id);
        printf("Name : %s\n", s.name);
        printf("CGPA : %.2f\n", s.cgpa);
        printf("----------------------------------\n");
    }

    fclose(fp);
}

void searchStudent()
{
    FILE *fp;
    struct Student s;
    int id;
    int found = 0;

    fp = fopen("students.txt", "r");

    if(fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    id = inputInt("\nEnter Student ID to Search: ");

    while(fscanf(fp, "%d|%99[^|]|%f\n",
                 &s.id, s.name, &s.cgpa) == 3)
    {
        if(s.id == id)
        {
            printf("\nStudent Found!\n");
            printf("ID   : %d\n", s.id);
            printf("Name : %s\n", s.name);
            printf("CGPA : %.2f\n", s.cgpa);

            found = 1;
            break;
        }
    }

    if(!found)
    {
        printf("Student Not Found!\n");
    }

    fclose(fp);
}


void updateStudent()
{
    FILE *fp, *temp;
    struct Student s;
    int id;
    int found = 0;

    fp = fopen("students.txt", "r");
    temp = fopen("temp.txt", "w");

    if(fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    id = inputInt("\nEnter Student ID to Update: ");

    while(fscanf(fp, "%d|%99[^|]|%f\n",
                 &s.id, s.name, &s.cgpa) == 3)
    {
        if(s.id == id)
        {
            printf("Enter New Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';

            s.cgpa = inputCGPA("Enter New CGPA: ");

            found = 1;
        }

        fprintf(temp, "%d|%s|%.2f\n",
                s.id, s.name, s.cgpa);
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(found)
        printf("Student Updated Successfully!\n");
    else
        printf("Student Not Found!\n");
}

void deleteStudent()
{
    FILE *fp, *temp;
    struct Student s;
    int id;
    int found = 0;

    fp = fopen("students.txt", "r");
    temp = fopen("temp.txt", "w");

    if(fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    id = inputInt("\nEnter Student ID to Delete: ");

    while(fscanf(fp, "%d|%99[^|]|%f\n",
                 &s.id, s.name, &s.cgpa) == 3)
    {
        if(s.id == id)
        {
            found = 1;
            continue;
        }

        fprintf(temp, "%d|%s|%.2f\n",
                s.id, s.name, s.cgpa);
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(found)
        printf("Student Deleted Successfully!\n");
    else
        printf("Student Not Found!\n");
}
