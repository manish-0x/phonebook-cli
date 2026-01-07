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

int main(void)
{
  return 0;
}

// Use file handling with a text file to save, edit and retrieve data

// Simple CLI application basic layout with keyboard as primary input
