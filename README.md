# phonebook-cli
A CLI phonebook application built using C which uses file handling to use a text (.txt) file for storing data.

## Data Format
The contacts are stored in a .txt file, with each line representing one contact.
Format:
`name; number`

## Compatibility
The application source code can be compiled only on Windows because of the use of `system("cls");` line.
That line works for UI related things and can be omitted/replaced if compiling on Linux or any non-Windows OS.
Cross-platform portability was not a goal for this project, it was not implemented.

## Usage
    .\phonebook.exe
On startup, the application shows the menu with numbered options. As per the labels, the user can choose an option by entering the corresponding option number they want to use.

## Assumptions
- Input is provided in expected format.
- The user interacts with the program as intended.
- The program is executed in a windows environment.

## Design choice
- _Text file storage_: Used a plain text file instead of binary file storage to practice file handling in a more visible and readable way.
- _Simplicity over robustness_: Focused mostly on core functionality rather than balance in functionality and defensiveness to keep the project simple.
- _Limited portability_: Skipped portability in source code to keep the project simple.
- _Custom delimiter_: Used (;) for name and number separator instead of a comma to distinguish the format from CSV-style data.
