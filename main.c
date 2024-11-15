#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Student {
    char ID[100000];
    char name[10000];
    int marks;
    int attendance;
};

void addToRecords() {
    FILE *file;

    file = fopen("records.txt", "a");

    if(file == NULL) {
        printf("File doesn't exist or created\n");
    }
    else {

        struct Student student;

        int num;
        printf("Enter amount of student to add: ");
        scanf("%d", &num);

        for(int i = 0; i < num; i++) {
            printf("Enter ID: ");
            scanf(" %[^\n]", student.ID);
            getchar();

            printf("Enter Name: ");
            scanf(" %[^\n]", student.name);
            getchar();

            printf("Enter Marks: ");
            scanf("%d", &student.marks);
            getchar();

            printf("Enter attendance: ");
            scanf("%d", &student.attendance);
            getchar();

            fprintf(file, "%s\t %s\t %d\t %d\n", student.ID, student.name, student.marks, student.attendance);

            printf("Added to records successfully\n");
        }

        fclose(file);

    }
}

void displayRecords() {
    FILE *file;
    file = fopen("records.txt", "r");

    if(file == NULL) {
        printf("File doesn't exist yet. Try adding records\n");
    }
    else {
        struct Student student;

        while(fscanf(file, " %[^\t\n] %[^\t\n] %d %d", student.ID, student.name, &student.marks, &student.attendance) != EOF) {
            printf("%s\t %s\t %d\t %d\n", student.ID, student.name, student.marks, student.attendance);
        }

        fclose(file);
    }
}


void searchRecords() {
    FILE *file;
    file = fopen("records.txt", "r");


    if (file == NULL) {
        printf("File doesn't exist yet. Try adding records.\n");
        return;
    }

    struct Student student;
    char searchQuery[100];

    bool found = false;

    printf("Enter ID or Name to search: ");
    scanf(" %[^\n]", searchQuery);

    while (fscanf(file, "%s\t %[^\t]\t %d\t %d\n", student.ID, student.name, &student.marks, &student.attendance) != EOF) {
        if (strcmp(student.ID, searchQuery) == 0 || strcasecmp(student.name, searchQuery) == 0) {
            printf("\nRecord Found:\n");
            printf("ID: %s\n", student.ID);
            printf("Name: %s\n", student.name);
            printf("Marks: %d\n", student.marks);
            printf("Attendance: %d\n", student.attendance);
            found = true;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("\nNo records found for '%s'.\n", searchQuery);
    }
}


void updateRecords() {
    FILE *file;
    
    file = fopen("records.txt", "r");


    if (file == NULL) {
        printf("File doesn't exist yet. Try adding records first.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Unable to create a temporary file.\n");
        fclose(file);
        return;
    }

    struct Student student;
    char searchID[100];

    bool found = false;

    printf("Enter the ID of the student to update: ");
    scanf(" %[^\n]", searchID);

    while (fscanf(file, "%s\t %[^\t]\t %d\t %d\n", student.ID, student.name, &student.marks, &student.attendance) != EOF) {
        if (strcmp(student.ID, searchID) == 0) {
            printf("\nRecord Found:\n");
            printf("ID: %s\n", student.ID);
            printf("Name: %s\n", student.name);
            printf("Marks: %d\n", student.marks);
            printf("Attendance: %d\n", student.attendance);

            printf("\nEnter new details:\n");
            printf("Enter Name: ");
            scanf(" %[^\n]", student.name);
            printf("Enter Marks: ");
            scanf("%d", &student.marks);
            printf("Enter Attendance: ");
            scanf("%d", &student.attendance);

            found = true;
        }
        fprintf(tempFile, "%s\t %s\t %d\t %d\n", student.ID, student.name, student.marks, student.attendance);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("records.txt");
        rename("temp.txt", "records.txt");
        printf("\nRecord updated successfully.\n");
    } else {
        remove("temp.txt");
        printf("\nNo record found with ID '%s'.\n", searchID);
    }
}







int main() {

    int choice;

    do
    {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student Record\n");
        printf("2. Display Records\n");
        printf("3. Search Records\n");
        printf("4. Update Student Record\n");
        printf("5. Exit\n\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addToRecords();
                break;
            case 2:
                displayRecords();
                break;
            case 3:
                searchRecords();
                break;
            case 4:
                updateRecords();
                break;
            case 5:
                printf("Quitting\n");
                break;
            default:
                printf("Invalid Input. Please Try Again\n");
        }

    } while (choice != 5);
    

    return 0;
}