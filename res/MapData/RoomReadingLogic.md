# Room Reading Logic

The rooms are essential to how a floor generates. Due to its really essential nature, trying to read it
in a more flexible way is required. This method (probably and/or theoretically)

## Examples
**APPEND ALL FILE NAMES WITH ".txt"**

Name | Room no. | Row no.
--- | --- | ---
010 | 01 | 0
f12 | f1 | 2
abc | ab | c

`010` is the name of the room we're trying to load.
- `01` is the room number.
- The last `0` is the row number.

`f12` is the name of the room we're trying to load.
 - `f1` is the room number.
 - `2` is the row number.

 `abc` is the name of the room we're trying to load.
  - `ab` is the room number
  - `c` is the row number

## Explanation

This method of storage means that we can **easily access the row number of any room**. This is essential since we're trying to read from the file and add to a string from the file. As a **trade-off**, however, it means that we will **have to handle a lot of files.** The files can also use 1 through z, since we're not using hexadecimal numbers to label the file names, which can be helpful since it means that there are lots of maps that we can store.

## Procedure

To begin this arduous method of storing, first come up with a room design. After that, make a text file for each of the rows. This method can be painful, but can be eased with a macro or program of sorts. Then, dump the `.txt` files into the MapData folder.
