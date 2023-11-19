#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct Student
{
    int rollnumber;
    char name[100];
    char phone[100];
    float percentage;
    struct Student *next;
};


struct Student *insert(struct Student *head, int rollnumber, const char name[100], const char phone[100], float percentage)
{
    struct Student *student = (struct Student *)malloc(sizeof(struct Student));
    student->rollnumber = rollnumber;
    strcpy(student->name, name);
    strcpy(student->phone, phone);
    student->percentage = percentage;
    student->next = NULL;

    if (head == NULL)
    {
        head = student;
    }
    else
    {
        student->next = head;
        head = student;
    }

    return head;
}

void search(struct Student *head, int rollnumber)
{
    struct Student *temp = head;
    while (temp != NULL)
    {
        if (temp->rollnumber == rollnumber)
        {
            printf("Roll Number: %d\n", temp->rollnumber);
            printf("Name: %s\n", temp->name);
            printf("Phone: %s\n", temp->phone);
            printf("Percentage: %0.4f\n", temp->percentage);
            return;
        }
        temp = temp->next;
    }
    printf("Student with roll number %d is not found !!!\n", rollnumber);
}

void update(struct Student *head, int rollnumber)
{
    struct Student *temp = head;
    while (temp != NULL)
    {
        if (temp->rollnumber == rollnumber)
        {
            printf("Record with roll number %d Found !!!\n", rollnumber);
            printf("Enter new name: ");
            scanf("%s", temp->name);
            printf("Enter new phone number: ");
            scanf("%s", temp->phone);
            printf("Enter new percentage: ");
            scanf("%f", &temp->percentage);
            printf("Updation Successful!!!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Student with roll number %d is not found !!!\n", rollnumber);
}

struct Student *Delete(struct Student *head, int rollnumber)
{
    struct Student *temp1 = head;
    struct Student *temp2 = head;
    while (temp1 != NULL)
    {
        if (temp1->rollnumber == rollnumber)
        {
            if (temp1 == temp2)
            {
                head = head->next;
                free(temp1);
            }
            else
            {
                temp2->next = temp1->next;
                free(temp1);
            }
            return head;
        }
        temp2 = temp1;
        temp1 = temp1->next;
    }
    return head;
}

void display(struct Student *head)
{
    struct Student *temp = head;
    while (temp != NULL)
    {
        printf("\nRoll Number: %d\n", temp->rollnumber);
        printf("Name: %s \n", temp->name);
        printf("Phone: %s \n", temp->phone);
        printf("Percentage: %0.4f\n", temp->percentage);
        temp = temp->next;
    }
}

struct Student *sort(struct Student *head)
{
    struct Student *temp = NULL;
    struct Student *ptr;
    struct Student *lptr;
    while (head != NULL)
    {
        ptr = head;
        lptr = head;
        while (ptr != NULL)
        {
            if (ptr->rollnumber > lptr->rollnumber)
            {
                lptr = ptr;
            }
            ptr = ptr->next;
        }
        temp = insert(temp, lptr->rollnumber, lptr->name, lptr->phone, lptr->percentage);
        head = Delete(head, lptr->rollnumber);
    }
    return temp;
}

void saveToFile(struct Student *head, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    struct Student *temp = head;
    while (temp != NULL)
    {
        fprintf(file, "%d %s %s %0.4f\n", temp->rollnumber, temp->name, temp->phone, temp->percentage);
        temp = temp->next;
    }

    fclose(file);
}

struct Student *loadFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return NULL;
    }

    struct Student *head = NULL;
    int rollnumber;
    char name[100];
    char phone[100];
    float percentage;

    while (fscanf(file, "%d %s %s %f", &rollnumber, name, phone, &percentage) == 4)
    {
        head = insert(head, rollnumber, name, phone, percentage);
    }

    fclose(file);
    return head;
}


int main()
{
    struct Student *head = NULL;
    int choice;
    char name[100];
    char phone[100];
    char input[100];
    long rollnumber; // Use long to accommodate a wider range of integer values
    float percentage;
    char *endptr;

    // Load student records from file (if any)
    head = loadFromFile("student_records.txt");

    do
    {
        printf("\n*****************************************\n");
        printf("*       Student Database Management      *\n");
        printf("*****************************************\n");
        printf("1. Insert student details\n");
        printf("2. Search for student details\n");
        printf("3. Delete student details\n");
        printf("4. Update student details\n");
        printf("5. Display all student details\n");
        printf("6. Sort records based on roll number\n");
        printf("7. Save records to file\n");
        printf("0. Exit\n");
        printf("Enter Choice: ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Input error. Exiting.\n");
            return 1; // Handle input error
        }

        choice = strtol(input, &endptr, 10);

        // Check if the entire input is a valid integer
        if (*endptr == '\n' || *endptr == '\0')
        {
            switch (choice)
            {
            case 1:
                while (1)
                {
                    printf("\nEnter roll number: ");
                    if (fgets(input, sizeof(input), stdin) == NULL)
                    {
                        printf("Input error. Exiting.\n");
                        return 1; // Handle input error
                    }

                    rollnumber = strtol(input, &endptr, 10);

                    // Check if the entire input is a valid integer
                    if (*endptr == '\n' || *endptr == '\0')
                    {
                        if (rollnumber > 0)
                        {
                            break; // Break out of the loop if a valid input is provided
                        }
                        else
                        {
                            printf("Invalid input for roll number. Please enter a valid positive integer.\n");
                        }
                    }
                    else
                    {
                        printf("Invalid input for roll number. Please enter a valid positive integer.\n");
                    }
                }

                printf("Enter name: ");
                if (fgets(name, sizeof(name), stdin) == NULL)
                {
                    printf("Input error. Exiting.\n");
                    return 1; // Handle input error
                }

                printf("Enter phone number: ");
                if (fgets(phone, sizeof(phone), stdin) == NULL)
                {
                    printf("Input error. Exiting.\n");
                    return 1; // Handle input error
                }

                while (1)
                {
                    printf("Enter percentage: ");
                    if (fgets(input, sizeof(input), stdin) == NULL)
                    {
                        printf("Input error. Exiting.\n");
                        return 1; // Handle input error
                    }

                    percentage = strtof(input, &endptr);

                    // Check if the entire input is a valid float
                    if (*endptr == '\n' || *endptr == '\0')
                    {
                        if (percentage >= 0 && percentage <= 100)
                        {
                            break; // Break out of the loop if a valid input is provided
                        }
                        else
                        {
                            printf("Invalid input for percentage. Please enter a valid float between 0 and 100.\n");
                        }
                    }
                    else
                    {
                        printf("Invalid input for percentage. Please enter a valid float between 0 and 100.\n");
                    }
                }

                head = insert(head, rollnumber, name, phone, percentage);
                printf("Student details inserted successfully!\n");
                break;

            case 2:
                while (1)
                {
                    printf("\nEnter roll number to search: ");
                    if (fgets(input, sizeof(input), stdin) == NULL)
                    {
                        printf("Input error. Exiting.\n");
                        return 1; // Handle input error
                    }

                    rollnumber = strtol(input, &endptr, 10);

                    // Check if the entire input is a valid integer
                    if (*endptr == '\n' || *endptr == '\0')
                    {
                        if (rollnumber > 0)
                        {
                            break; // Break out of the loop if a valid input is provided
                        }
                        else
                        {
                            printf("Invalid input for roll number. Please enter a valid positive integer.\n");
                        }
                    }
                    else
                    {
                        printf("Invalid input for roll number. Please enter a valid positive integer.\n");
                    }
                }
                search(head, rollnumber);
                break;

            case 3:
                while (1)
                {
                    printf("\nEnter roll number to delete: ");
                    if (fgets(input, sizeof(input), stdin) == NULL)
                    {
                        printf("Input error. Exiting.\n");
                        return 1; // Handle input error
                    }

                    rollnumber = strtol(input, &endptr, 10);

                    // Check if the entire input is a valid integer
                    if (*endptr == '\n' || *endptr == '\0')
                    {
                        if (rollnumber > 0)
                        {
                            break; // Break out of the loop if a valid input is provided
                        }
                        else
                        {
                            printf("Invalid input for roll number. Please enter a valid positive integer.\n");
                        }
                    }
                    else
                    {
                        printf("Invalid input for roll number. Please enter a valid positive integer.\n");
                    }
                }
                head = Delete(head, rollnumber);
                printf("Student details deleted successfully!\n");
                break;

            case 4:
                while (1)
                {
                    printf("\nEnter roll number to update: ");
                    if (fgets(input, sizeof(input), stdin) == NULL)
                    {
                        printf("Input error. Exiting.\n");
                        return 1; // Handle input error
                    }

                    rollnumber = strtol(input, &endptr, 10);

                    // Check if the entire input is a valid integer
                    if (*endptr == '\n' || *endptr == '\0')
                    {
                        if (rollnumber > 0)
                        {
                            break; // Break out of the loop if a valid input is provided
                        }
                        else
                        {
                            printf("Invalid input for roll number. Please enter a valid positive integer.\n");
                        }
                    }
                    else
                    {
                        printf("Invalid input for roll number. Please enter a valid positive integer.\n");
                    }
                }

                update(head, rollnumber);
                printf("Student details updated successfully!\n");
                break;

            case 5:
                display(head);
                break;

            case 6:
                head = sort(head);
                printf("Records sorted successfully!\n");
                break;

            case 7:
                saveToFile(head, "student_records.txt");
                printf("Records saved to file.\n");
                break;
            }
        }
        else
        {
            printf("Invalid input for choice. Please enter a valid integer.\n");
        }

    } while (choice != 0);

    return 0;
}
