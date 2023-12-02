# Banker's Algorithm for deadlock avoidance

## Program
This project contains a single .cpp file.
The program will use the Banker's Algorithm to ensure that there is no deadlock.
An example is given. A text document is read which sets up the correct matrices.
It will then check if the sequence is safe or will cause deadlock.
If the system is in an unsafe state it returns saying "not safe".
If it is safe it will also provide the safe sequence.

## Problems
The only problems that could arise is giving the incorrect arguments.

## Compiling and Running
'''
g++ banker.cpp -o banker
'''
the process takes 3 arguments.
the first is the .txt file with the matrices for allocation, max, and available
the second is the number of processes 
and the third is the number of resource types

## Example

![ex.png](ex.png)

This is an example state 
it is a system with five processes P0 through P4 and three resources of type A, B, C. Resource type A has 10 instances, B has 5 instances and type C has 7 instances.

to run this example
'''
./banker ex.txt 5 3
'''
