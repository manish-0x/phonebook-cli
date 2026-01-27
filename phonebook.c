// Phonebook program source code
/*
TODO: Remove defensiveness and fix all functionality.
Assume that the user always co-operates.
TODO: Improve UI for better viewing, input and output experience
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char DATA_FILE[] = "./phonebook_data.txt";
const short int NAME_LENGTH = 25;
const short int NUMBER_LENGTH = 14;

typedef struct
{
    char name[NAME_LENGTH + 1];
    char number[NUMBER_LENGTH + 1];
}contact;

void menu();
int show_contacts();
int add_contact();
int search_contact();
int update_contact();
int remove_contact();

int main(void)
{
    while (1)
    {
        char choice = '\n', first_try = 'Y';

        menu();
        do
        {
            if (first_try == 'N')
                printf("\nInvalid choice. Please try again.\n");
            printf("Only the first character of input will be considered as choice\n");
            printf("Choice: ");
            scanf("%c", &choice);
            while (getchar() != '\n');
            first_try = 'N';
        } while (
            choice != '1' && choice != '2' && choice != '3' 
            && choice != '4' && choice != '5' && choice != '6'
                );

        // Menu driver implimentation
        int status = 0;
        switch (choice)
        {
            case '1':
                if (show_contacts() == 1)
                {
                    printf("Error opening data file.\n");
                    printf("Try adding contacts first.\n");
                }
                break;
            case '2':
                if (add_contact() == 2)
                {
                    printf("Error\n");
                }
                break;
            case '3':
                if (search_contact() == 1)
                {
                    printf("Error opening data file.\n");
                    printf("Try adding contacts first.\n");
                }
                break;
            case '4':
                status = update_contact();
                if (status == 1)
                {
                    printf("Error opening data file.\n");
                    printf("Try adding contacts first.\n");
                }
                else if (status == 2)
                {
                    printf("Error\n");
                }
                else if (status == 3)
                {
                    printf("An unexpected error occurred\n");
                }
                status = 0;
                break;
            case '5':
                status = remove_contact();
                if (status == 1)
                {
                    printf("Error opening data file.\n");
                    printf("Try adding contacts first.\n");
                }
                else if (status == 2)
                {
                    printf("Error\n");
                }
                else if (status == 3)
                {
                    printf("An unexpected error occurred\n");
                }
                status = 0;
                break;
            case '6':
                return 0;
        }
        printf("--------------------------------------------------\n");
    }
}

void menu()
{
    printf("********************\n");
    printf("     Phone Book     \n");
    printf("********************\n");
    printf("1. Show contacts\n");
    printf("2. Add contact\n");
    printf("3. Search contact\n");
    printf("4. Edit contact\n");
    printf("5. Delete contact\n");
    printf("6. Exit\n");

    printf("\nChoose an option and enter it to continue\n");
    printf("********************\n");
    printf("\n");
}

int show_contacts()
{
    printf("Showing all contacts...\n");
    FILE* file = fopen(DATA_FILE, "r");
    if (!file)
        return 1;
    unsigned int counter = 0;

    printf("\nSr.\tName\t\t\t\t\t\tNumber\n");
    contact person;
    while (fscanf(file, "%[^;]; %[^\n]\n", &person.name, &person.number) != EOF)
    {
        printf("%d.\t%s\t\t\t\t\t\t%s\n", ++counter, person.name, person.number);
    }
    printf("\nListed %d contacts from the Data file.\n", counter);
    
    fclose(file);

    return 0;
}

int add_contact()
{
    printf("Add a contact...\n");
    char choice = '\n';
    FILE* file = fopen(DATA_FILE, "a");
    if (!file)
        return 2;

    contact person;
    printf("Enter contact details.\n");
    printf("Name (Max %d characters): ", NAME_LENGTH);
    scanf("%[^\n]", &person.name);
    while (getchar() != '\n');
    printf("Number (Max %d characters): ", NUMBER_LENGTH);
    scanf("%[^\n]", &person.number);
    while (getchar() != '\n');
    printf("Add new contact:\n");
    printf("Name: %s\n", person.name);
    printf("Number: %s\n", person.number);
    do
    {
        printf("Choice (y/n): ");
        scanf("%c", &choice);
        while (getchar() != '\n');
        if (choice == 'n' || choice == 'N')
        {
            printf("Cancelled\n");
            fclose(file);
            return 0;
        }
    }
    while (choice != 'y' && choice != 'Y');
    fprintf(file, "%s; %s\n", person.name, person.number);

    fclose(file);

    return 0;
}

int search_contact()
{
    printf("Search a contact...\n");
    char choice = '\n';
    contact person;
    FILE* file = fopen(DATA_FILE, "r");
    if (!file)
        return 1;

    do
    {
        printf("Search contact by:\n");
        printf("1. Name\n");
        printf("2. Number\n");
        printf("Only the first character is considered the choice input\n");
        printf("Choice: ");
        scanf("%c", &choice);
        while (getchar() != '\n');
    } while (choice != '1' && choice != '2');

    if (choice == '1')
    {
        unsigned int counter = 0;
        char target_name[NAME_LENGTH + 1] = "\n";
        printf("Enter Name to search: ");
        scanf("%[^\n]", &target_name);
        while (getchar() != '\n');
        printf("Search results:\n");
        printf("\nSr.\tName\t\t\t\t\t\tNumber\n");
        while (fscanf(file, "%[^;]; %[^\n]\n", &person.name, &person.number) != EOF)
        {
            if (strcmp(person.name, target_name) == 0)
                printf("%d.\t%s\t\t\t\t\t\t%s\n", ++counter, person.name, person.number);
        }
        printf("\nFound %d contacts of name \"%s\".\n", counter, target_name);
    }
    else
    {
        unsigned int counter = 0;
        char target_number[NUMBER_LENGTH + 1] = "\n";
        printf("Enter Number to search: ");
        scanf("%[^\n]", &target_number);
        while (getchar() != '\n');
        printf("Search results:\n");
        printf("\nSr.\tName\t\t\t\t\t\tNumber\n");
        while (fscanf(file, "%[^;]; %[^\n]\n", &person.name, &person.number) != EOF)
        {
            if (strcmp(person.number, target_number) == 0)
                printf("%d.\t%s\t\t\t\t\t\t%s\n", ++counter, person.name, person.number);
        }
        printf("\nFound %d contacts of number \"%s\".\n", counter, target_number);
    }

    fclose(file);

    return 0;
}

int update_contact()
{
    printf("Update a contact...\n");
    contact person;
    unsigned int counter = 0;
    unsigned int target_contact = 0;

    /*
    Potential feature upgrade. Cancelled in initial build process for simplicity

    char choice = '\n';
    do
    {
        printf("Select contact by:\n");
        printf("1. Showing all contacts\n");
        printf("2. Search a specific contact\n");
        printf("\nChoice: ");
        scanf("%c", &choice);
    } while (choice != '1' && choice != '2');
    */

    // Showing contact list
    if (show_contacts() == 1)
        return 1;
    printf("\nEnter serial number of contact to edit: ");
    scanf("%d", &target_contact);
    while (getchar() != '\n');

    FILE* file = fopen(DATA_FILE, "r");
    if (!file)
        return 3;
    FILE* temp = fopen("temp.txt", "w");
    if (!temp)
        return 2;
    
    while (fscanf(file, "%[^;]; %[^\n]\n", &person.name, &person.number) != EOF)
    {
        if (++counter == target_contact)
        {
            printf("Editing contact details of:\n");
            printf("Name: %s\nNumber: %s", person.name, person.number);
            printf("New name: ");
            scanf("%[^\n]", &person.name);
            while (getchar() != '\n');
            printf("New number: ");
            scanf("%[^\n]", &person.number);
            while (getchar() != '\n');
            fprintf(temp, "%s; %s\n", person.name, person.number);
        }
        else
            fprintf(temp, "%s; %s\n", person.name, person.number);
    }

    /*
    printf("=====Removing\n");
    if (!remove(DATA_FILE))
        printf("Unable");
    */

    fclose(file);
    fclose(temp);
    remove(DATA_FILE);
    rename("temp.txt", DATA_FILE);

    return 0;
}

int remove_contact()
{
    contact person;
    unsigned int target_contact = 0, counter = 0;
    printf("Remove a contact...\n");
    // Showing contact list
    if (show_contacts() == 1)
        return 1;
    printf("Enter serial number of contact to remove: ");
    scanf("%d", &target_contact);
    while (getchar() != '\n');

    FILE* file = fopen(DATA_FILE, "r");
    if (!file)
        return 3;
    FILE* temp = fopen("temp.txt", "w");
    if (!temp)
        return 2;

    while (fscanf(file, "%[^;]; %[^\n]\n", &person.name, &person.number) != EOF)
    {
        if (++counter != target_contact)
            fprintf(temp, "%s; %s\n", person.name, person.number);
    }
    
    fclose(file);
    fclose(temp);
    remove(DATA_FILE);
    rename("temp.txt", DATA_FILE);

    return 0;
}
