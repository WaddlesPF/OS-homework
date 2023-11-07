#include <iostream>
#include <queue>
#include <thread>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>

sem_t* emptySlots;
sem_t* fullSlots;
sem_t mutp;
int bsize = 5;



int pmain() {
    std::cout << "producer program start" << std::endl;
    
    // Shared Memory Setup
    int shmid = shmget(1236, bsize, IPC_CREAT | 0666);
    //std::cout << errno << std::endl;
    if(shmid == -1) std::cerr << "shared mem fail" << std::endl;
    bool* table = (bool*)shmat(shmid, NULL, 0);
    //std::cout << errno << std::endl;

    std::cout << "shared memory done" << std::endl;

    // Semaphore open/init
    sem_unlink("/emptysem");
    sem_unlink("/fullsem");
    
    int ret = sem_init(&mutp, 0, 1);
    if(ret == -1) return -1;
    std::cout << "sem_init successful" << std::endl;
    
    emptySlots = sem_open("/emptysem", O_CREAT | O_EXCL, 0644, bsize);
    if(emptySlots == SEM_FAILED) {/*std::cout << errno << std::endl;*/ return -1; }

    fullSlots = sem_open("/fullsem", O_CREAT | O_EXCL, 0644, 0);
    if(fullSlots == SEM_FAILED) return -1; // exit if full slots failed
    std::cout << "full slots open" << std::endl;

    std::cout << "semaphore setup done (producer)" << std::endl;
    
    // Producer Loop
    
    do {
        sem_wait(emptySlots);
        sem_wait(&mutp);
        std::cout << "sem_waits done" << std::endl;

        int i = 0; 

        while(table[i] && i < bsize) ++i;
        table[i] = true;
       // std::cout << i << std::endl;
        
        sem_post(&mutp);
        sem_post(fullSlots);
        std::cout << "sempost for producer" << std::endl;
        
        
    } while(true);


    shmdt(table);
    shmctl(shmid, IPC_RMID, NULL);
  
    return 0;
}                                                   

int main(int argc, char* args[]) {
    std::thread t1(pmain);
    std::thread t2(pmain);

    t2.join();
    t1.join();

    return 0;
}
