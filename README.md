# Discord:
https://discord.gg/4DGyEUZ

# To Run Files:
This took me a while to figure out because I'm still pretty new to compiling code on the terminal. But to compile code. Be on the folder directory and type in the following:
``` bash
g++ main.cpp scanner.cpp token.cpp
```
It should compile and link all the files together. From there you should have an a.out file. Then to run it simply run.

``` bash
./a.out
```

Also, simply running run.sh will automate these two commands simply run:
``` bash
./run.sh
```

While in the main directory:
  run 'make' command from the terminal - this will execute g++ main.cpp
  scanner.cpp token.cpp and generate an object file named 'run'.  To execute
  this file type ./run in the terminal.  To remove this file simply type 
  'make clean' in the terminal and the command 'rm run' will execute.

# Resources For Class:
1. [Building a Simple Interpreter in Python](https://ruslanspivak.com/lsbasi-part1/)
  * This article talks about tokens and lexical analyzers and all that. Can be definitely used as a stepping stone for our project.
2. [Scanning and Creating Tokens (Implmented with Java)](http://www.craftinginterpreters.com/scanning.html)
  * The Concept is the same, but this is a really good example, in fact, this whole book is really good, for the entire project.
3. [RE C++ CheatSheet](http://cpprocks.com/files/c++11-regex-cheatsheet.pdf)
