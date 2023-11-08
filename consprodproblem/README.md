# Consumer Producer Assignment

# Programs:
This project contains 2 programs called producer.cpp and consumer.cpp
The shared memory contains 5 bits. The producer when it is able to enter the critical section
turns all the bits into 1, while the consumer goes in and turns them to 0. There is no practical
purpose besides proving that the producer consumer problem is solved using semaphores.

# Possible Problems:
Adding multi threading resulted in the program working half the time when running. Removing the multi threading, the program works as expected.
The program works half the time when running and I was not able to solve it before the due date. Without multithreading the programs should work fine.

# Compiling and Running
gcc consumer.cpp -lstdc++ -o consumer
gcc producer.cpp -lstdc++ -o producer

./producer & ./consumer &
no arguments.
