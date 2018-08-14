# Room Reading Logic

The rooms are essential to how a floor generates. Due to its really essential nature, trying to read it
in a more flexible way is required. This method (probably and/or theoretically)

## Explanation

The game will get the current room and will read the associated room file. This will let the program know what it can choose from. After that, the program will then read from the rooms that it has chosen from and adds it to the internal level storage.

This way of naming can allow for a virtually infinite amount of possibilities, which can be beneficial, since there can be a lot of type of rooms.

## Examples
**APPEND ALL FILE NAMES WITH ".txt"**

#### Floor 1:
```
0
1
2
3
4
5
6
7
8
9
a
b
```

Floor 1 will only contain rooms 0 through b.

#### Floor 2:
```
c
d
e
f
g
h
i
j
k
l
m
n
```

Floor 2 will only contain rooms c through n.

`0` contains:
```
<MAP DATA HERE>
```

`1a` contains:
```
<MAP DATA HERE>
```

`op` contains:
```
<MAP DATA HERE>
```

`p2p` contains:
```
<MAP DATA HERE>
```
