// Phonebook program source code
#include <stdio.h>

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
        char choice = '-', first_try = 'Y';

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
    if (!file)
    {
        printf("Error opening data file\n");
        return;
    }

    printf("\nName\t\t\t\t\t\tNumber\n");
    contact person;
    while (fscanf(file, "%s , %s\n", &person.name, &person.number) != EOF)
    {
        printf("%s\t\t\t\t\t\t%s\n", person.name, person.number);
    }
    
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
}

void update_contact()
{
    printf("Updating contact\n");
}

void remove_contact()
{
    printf("Removing contact\n");
}

// Use file handling with a text file to save, edit and retrieve data
// Simple CLI application basic layout with keyboard as primary input
