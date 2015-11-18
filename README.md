# cube

The problem stated below originated from otsys.com/problem. Think of
the problem statement as a set of "requirements".

The sample text files (cubes.txt and words.txt) come from the
same location.

The cube.pro file in this directory are auto-generated
by the Qt Creator IDE.

All other source files (.cpp and .h) are the work of Cody Brookshear.

Imagine that you have a 4x4x4 cube of letters, with each of the 64
"cubies" containing a single letter.  You also have a dictionary of
words.  You can say that a word "appears" in the cube if there is a
path through the cube starting with a cubie containing the first
letter of the word (ignoring case), moving next to an adjacent cubie
containing the second letter of the word, and so on until the word is
complete.  A cubie can only be used once in constructing a single
word, so the longest word that can possibly be constructed is 64
letters long.  (A single cubie *can* be used twice in two different
words, etc.)  By an "adjacent" cubie we mean one that touches a given
cubie in any direction, so a central cubie will have 26 neighbors (and
a corner cubie will have 7).

The program is invoked as follows:

```
program cube-file word-file
```

Specifically, if built using the Makefile and using default files,
invoke as:

```
./cube cubes.txt words.txt
```

cube-file is a file containing a sequence of 64-letter strings, each
on a separate line and each representing a cube in the obvious way.
word-file is a dictionary containing words, each once again on its own
line.

The program should output to stdout a sequence of integers, one for
each cube.  Each integer should be the number of unique words in the
dictionary that appear in that cube.

The source code can be compiled under Linux by running the command:

```
g++ -O3 -o cube cubie.cpp cube.cpp main.cpp
```

