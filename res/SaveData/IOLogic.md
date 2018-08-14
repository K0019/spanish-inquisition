# IO Logic

Due to the nature of the save data's usage, saving data will be handled in this way:

## In a save file...

The save file will contain:
 - Player's score
 - Player's Upgrades[]

Reading
===
Procedure
---
1. Read the file
2. Get the variable from the file
3. Set the variable as obtained from the file

> Let's not get verbose, keep it succinct

### 1. Read the file
Reading the file is using a basic read code. In a sense, only `ifstream` will be used for this case.

### 2. Get the variable
When reading, get the lines and put them into a string array.

### 3. Set the variable
Get from a specific index of the array and put the value into the variable.

# Writing

## Procedure
1. Get all the writable variables
2. Open the file
3. Write to save file

### 1. Get all variables
The variables will be stored in an array for sake of easier coding. This will mostly be done through a function.

### 2. Open the file
Use `ofstream` to open the file to be able to write to it.

### 3. Write!
Utilize for loops to iterate through the variable array.


> ~EOF~
