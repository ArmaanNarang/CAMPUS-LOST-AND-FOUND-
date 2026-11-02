# Campus Lost & Found System

A beginner-friendly console application written in C to report and manage lost and found items on a campus.

## Features
- Report a lost item
- Report a found item
- Search for an item by exact name
- View all reported items
- Remove an item by its displayed number
- Save records in `items.txt` so they can be loaded the next time the program runs

## Requirements
- A C compiler (GCC recommended)
- C99 or later

## Run the project

### Linux / macOS
```bash
gcc main.c -o campus_finder
./campus_finder
```

### Windows (MinGW GCC)
```bash
gcc main.c -o campus_finder.exe
campus_finder.exe
```

The program creates `items.txt` in the current working directory when it saves records.

## Data format
Each record is stored as:
```text
type|item name|location
```
`1` means Lost and `2` means Found.

## Notes
- Search currently requires the exact item name (including capitalization).
- This is a learning project, not a production campus service.
- Avoid using the `|` character in item names or locations because it separates fields in the data file.

## Author
Add your name here.
