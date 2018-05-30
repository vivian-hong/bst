#ReadMe for COMP15 HW 4
## Binary Search Tree


Purpose:

The purpose of this program is to give the user the ability to make a binary
search tree. The user should be able to insert and remove values from the tree
where ever value to the left of a node is less than the node and every value 
to the right of a node should be greater than the node. The user should also
be able to find the maximum node and the minimum node, print the tree, find
the total number of nodes on the tree, find the tree height, and find the sum
of all the nodes on the tree.

Files:
BinarySearchTree.cpp -- holds all the functions for manipulating the binary
		        search tree (i.e. insert, remove, max, min, etc.)
BinarySearchTree.h -- holds all the header functions for BinarySearchTree.cpp
main.cpp -- main that calls functions and has commented out tests

How to compile: 

Use included Makefile.

Outline of data structure:

There is a BinarySearchTree class that holds functions to create a binary
search tree of nodes (struct Node) that contain the value of the node, the
count of the node and pointers to the left and right children of the node. 
This class also contains all the functions having to do with the bst, including
insert, remove, max, min, contains, height, total nodes and count total
functions that all have private helper functions. There is also a copy 
constructor to make deep copies and an assignment overload.

Outline of algorithm:

Since most of the functions in the program are recursive, they follow a 
recursive algorithm, beginning by checking for base case(s), meaning the 
goal of the function has been achieved. Following this, general/recursive
case(s) are called that work towards the base case by breaking the problem 
down. Recursive call(s) to the function are performed. 

Recieved help for a glibc detected from Joel Reske