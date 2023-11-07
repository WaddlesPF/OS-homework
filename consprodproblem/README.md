# Consumer Producer Assignment

# Programs:
This project contains 2 programs called producer.cpp and consumer.cpp

# Possible Problems:
Adding multi threading resulted in the program working half the time when running. Removing the multi threading, the program works as expected.

# Compiling and Running
gcc consumer.cpp -lstdc++ -o consumer
gcc producer.cpp -lstdc++ -o producer

./producer & ./consumer &
