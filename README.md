# Dictionary-Hashing

* PA 3
* CPTS 233

> In this task, you will implement a program that creates an English dictionary.  You will implement a hash table to store the dictionary. The hash table will be indexed via the words in the English language. The dictionary will store the definition of the words for doing lookups after the dictionary is built. 

# Testing
> Your program will be tested first by running without passing in the dictionary.json filename on the command line – usage/help should be printed out. Then, it will be run with the dictionary.json filename. That should load the dictionary, and go into the query mode. I will be using a test file of words to search for. It should print out the words and their definitions or “Word not found” if it’s an invalid search.

> It is very easy to run on the command line with a pipe (or a redirect):
> > cat testcases.txt | ./a.out dictionary.json
> The program should build the hash from the dictionary, then do the queries for the words listed in that testcases.txt file and quit.

# Grading Criteria
> Your assignment will be judged by the following criteria:

+ [80] Your code compiles on the EECS servers using g++ -std=c++0x *.cpp, passes inspection with a set of test cases (words), and also handles outputs a usage message if it isn’t given the dictionary.json filename on the command line (via argv)
+ [10] Data structure usage.  Your program only uses vectors, plus your Word and Dictionary classes. 
+ [10] Your code is well documented and generally easy to read.

=======
100/100
=======