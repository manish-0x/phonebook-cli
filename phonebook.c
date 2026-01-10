// Phonebook program source code
#include <stdio.h>

const chat DATA_FILE_LOCATION[] = "./";
const char DATA_FILE_NAME[] = "phonebook_data.txt";
const NAME_LENGTH = 25;
const NUMBER_LENGTH = 13;

typedef struct contact
{
  char name[NAME_LENGTH + 1];
  char number[NUMBER_LENGTH + 1];
}contact;

void menu();
void show();
void add(contact*);
void search(char* key, char* value);
void update(contact*);
void remove(contact*);

int main(void)
{
  int choice = 0;
  
  menu();
  do
  {
    scanf("%d", &choice);
  }
  while (choice < 1 && choice > 5)

  // TODO: Add menu driver implimentation
  switch (choice)
  {
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
}

void menu()
{
  printf("********************\n");
  printf("     Phone Book     \n");
  printf("********************\n");

  printf("Choose an option and enter it to continue\n\n");
  
  printf("1. Show contacts\n")
  printf("2. Add contact\n");
  printf("3. Search contact\n");
  printf("4. Edit contact\n");
  printf("5. Delete contact\n");

  printf("\nChoice: ");
}

// Use file handling with a text file to save, edit and retrieve data

// Simple CLI application basic layout with keyboard as primary input
