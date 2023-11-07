// consumer.cpp

#include <iostream>
#include <queue>
#include <thread>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <fcntl.h>

sem_t* emptySlots;
sem_t* fullSlots;
sem_t mutc;
int bsize = 5;

int cmain() {
    std::cout << "consumer program start" << std::endl;
    
    // Shared Memory Setup
    int shmid = shmget(1236, bsize, IPC_CREAT | 0666);
    std::cout << errno << std::endl;
    if(shmid == -1) std::cerr << "shared mem fail" << std::endl;
    bool* table = (bool*)shmat(shmid, NULL, 0);
    std::cout << errno << "(consumer)" << std::endl;

    std::cout << "shared memory done" << std::endl;   

    // Semaphore open/init


    // Loop
    
     for(int t = 0; t < 5; ++t) {
        std::cout << "loop start consumer" << std::endl;
        sem_wait(fullSlots);
        sem_wait(&mutc);
        
        int i = 0;
        
        while(!table[i] && i < bsize) ++i;
        if(i >= bsize) continue;
        table[i] = false;
        //std::cout << i << std::endl;
       
        sem_post(&mutc);
        sem_post(emptySlots);
        std::cout << "sempost for consumer" << std::endl;

        
    }


    shmdt(table);
    shmctl(shmid, IPC_RMID, NULL);
    
    std::cout << "consumer finished" << std::endl;
    return 0;
}                  

int main(int argc, char* args[]) {
    int ret = sem_init(&mutc, 0, 1);
    if(ret == -1) return -1;
    std::cout << "sem_init successful" << std::endl;
    
    emptySlots = sem_open("/emptysem", 0);
    if(emptySlots == SEM_FAILED) {std::cout << errno << "consumer" << std::endl; return -1; }

    fullSlots = sem_open("/fullsem", 0);
    if(fullSlots == SEM_FAILED) return -1; // exit if full slots failed
    std::cout << "full slots open" << std::endl;

    std::cout << "semaphore setup done (consumer)" << std::endl;

    std::thread t1(cmain);
    std::thread t2(cmain);
    //std::thread t3(cmain);

    //t3.join();
    t2.join();
    t1.join();

    return 0;
}
