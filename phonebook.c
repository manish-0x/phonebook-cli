// Phonebook program source code
/*
TODO: Improve the program by making it defensive
TODO: Improve UI for better viewing, input and output experience
*/
#include <stdio.h>
#include <string.h>

const char DATA_FILE[] = "./phonebook_data.txt";
const short int NAME_LENGTH = 25;
const short int NUMBER_LENGTH = 14;

typedef struct contact
{
    char name[NAME_LENGTH + 1];
    char number[NUMBER_LENGTH + 1];
}contact;

void menu();
void show_contacts();
void add_contact();
void search_contact();
void update_contact();
void remove_contact();

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
        switch (choice)
        {
            case '1':
                show_contacts();
                break;
            case '2':
                add_contact();
                break;
            case '3':
                search_contact();
                break;
            case '4':
                update_contact();
                break;
            case '5':
                remove_contact();
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
    printf("Choose an option and enter it to continue\n\n");

    printf("1. Show contacts\n");
    printf("2. Add contact\n");
    printf("3. Search contact\n");
    printf("4. Edit contact\n");
    printf("5. Delete contact\n");
    printf("6. Exit\n");
    printf("\n");
}

void show_contacts()
{
    printf("Showing contacts\n");
    FILE* file = fopen(DATA_FILE, "r");
    unsigned int counter = 0;
    if (!file)
    {
        printf("Error opening data file\n");
        return;
    }

    printf("\nSr.\tName\t\t\t\t\t\tNumber\n");
    contact person;
    while (fscanf(file, "%s , %s\n", &person.name, &person.number) != EOF)
    {
        printf("%d.\t%s\t\t\t\t\t\t%s\n", ++counter, person.name, person.number);
    }
    printf("\nListed %d contacts from the Data file.\n", counter);
    
    fclose(file);
}

void add_contact()
{
    printf("Adding contact\n");
    FILE* file = fopen(DATA_FILE, "a+");
    if (!file)
    {
        printf("Error opening data file\n");
        return;
    }

    contact person;
    printf("Enter contact details. Please don't use Spaces in name or number\n");
    printf("Name: ");
    scanf("%s", &person.name);
    printf("Number: ");
    scanf("%s", &person.number);
    fprintf(file, "%s , %s\n", person.name, person.number);

    fclose(file);
}

void search_contact()
{
    printf("Searching contact\n");
    char choice = '\n';
    contact person;
    FILE* file = fopen(DATA_FILE, "r");
    if (!file)
    {
        printf("Error opening file\n");
        return;
    }

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
        char target_name[NAME_LENGTH + 1] = "\n";
        printf("Enter Name to search: ");
        scanf("%s", &target_name);
        while (getchar() != '\n');
        unsigned int counter = 0;
        printf("Search results:\n");
        printf("\nSr.\tName\t\t\t\t\t\tNumber\n");
        while (fscanf(file, "%s , %s\n", &person.name, &person.number) != EOF)
        {
            if (strcmp(person.name, target_name) == 0)
                printf("%d.\t%s\t\t\t\t\t\t%s\n", ++counter, person.name, person.number);
        }
        printf("\nFound %d contacts having name \"%s\".\n", counter, target_name);
    }
    else
     {
        char target_number[NUMBER_LENGTH + 1] = "\n";
        printf("Enter Number to search: ");
        scanf("%s", &target_number);
        while (getchar() != '\n');
        unsigned int counter = 0;
        printf("Search results:\n");
        printf("\nSr.\tName\t\t\t\t\t\tNumber\n");
        while (fscanf(file, "%s , %s\n", &person.name, &person.number) != EOF)
        {
            if (strcmp(person.number, target_number) == 0)
                printf("%d.\t%s\t\t\t\t\t\t%s\n", ++counter, person.name, person.number);
        }
        printf("\nFound %d contacts having number \"%s\".\n", counter, target_number);
    }

    fclose(file);
}

void update_contact()
{
    printf("Updating contact\n");
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

    printf("Showing contact list:\n");
    show_contacts();
    printf("\nSelect serial number of contact to edit: ");
    scanf("%d", &target_contact);
    while (getchar() != '\n');

    FILE* file = fopen(DATA_FILE, "r");
    FILE* temp = fopen("temp.txt", "w");
    while (fscanf(file, "%s , %s\n", &person.name, &person.number) != EOF)
    {
        if (++counter == target_contact)
        {
            printf("Editing contact details of:\n");
            printf("Name: %s\nNumber: %s", person.name, person.number);
            printf("New name: ");
            scanf("%s", &person.name);
            while (getchar() != '\n');
            printf("New number: ");
            scanf("%s", &person.number);
            while (getchar() != '\n');
            fprintf(temp, "%s , %s\n", person.name, person.number);
        }
        else
            fprintf(temp, "%s , %s\n", person.name, person.number);
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
}

void remove_contact()
{
    contact person;
    unsigned int target_contact = 0, counter = 0;
    printf("Removing contact\n");
    printf("Showing all contacts:\n");
    show_contacts();
    printf("Select contact serial to remove: ");
    scanf("%d", &target_contact);
    while (getchar() != '\n');

    FILE* file = fopen(DATA_FILE, "r");
    FILE* temp = fopen("temp.txt", "w");

    while (fscanf(file, "%s , %s\n", &person.name, &person.number) != EOF)
    {
        if (++counter != target_contact)
            fprintf(temp, "%s , %s\n", person.name, person.number);
    }
    
    fclose(file);
    fclose(temp);
    remove(DATA_FILE);
    rename("temp.txt", DATA_FILE);
}

// Use file handling with a text file to save, edit and retrieve data
// Simple CLI application basic layout with keyboard as primary input
