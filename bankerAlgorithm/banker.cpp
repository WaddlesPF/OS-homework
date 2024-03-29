#include <iostream>
#include <fstream>


int main(int argc, const char * argv[]) {
    // make sure there are enough args
    if(argc < 4) {
        std::cout << "missing args. text.txt procNumCount numOfResourceType" << std::endl;
        return -1;
    }
    
    std::ifstream textDoc;
    textDoc.open(argv[1]);
    
    // error check for if cant open file
    char input[50];
    if(!textDoc.is_open()) {
        std::cout << "error opening text document" << std::endl;
        return -1;
    }
   
    textDoc.getline(input,50);
    int n = (int)(*argv[2]) - '0';
    int m = (int)(*argv[3]) - '0';

    int allocation[n][m];
    int available[m];
    int max[n][m];

    int j = -1;

    // Reading the text document
    // reading allocation
    while(textDoc.getline(input, 50)){
        ++j;
        if(input[0] == '/') break;
        //std::cout << input << std::endl;

        int i = 0;
        for(int c = 0; c < 50; ++c) { 
            //std::cout << input[c] << std::endl;
            if(input[c] == '\n') break;
            if(input[c] == ' ') continue;
            if(i >= m) break;
            allocation[j][i] = input[c]-'0';
            //std::cout << "allocation["<<j<<"]"<<"["<<i<<"]" << allocation[j][i] << std::endl;
            ++i;
        }
    }
    
    // reading max
    j = -1;
    while(textDoc.getline(input, 50)){
        ++j;
        if(input[0] == '/') break;
        //std::cout << input << std::endl;

        int i = 0;
        for(int c = 0; c < 50; ++c) { 
            //std::cout << input[c] << std::endl;
            if(input[c] == '\n') break;
            if(input[c] == ' ') continue;
            if(i >= m) break;
            max[j][i] = input[c]-'0';
            //std::cout << "max["<<j<<"]"<<"["<<i<<"]" << max[j][i] << std::endl;
            ++i;
        }
    }
    // reading available
     while(textDoc.getline(input, 50)) {
        if(input[0] == '/') break;
        //std::cout << input << std::endl;
        int i = 0;
        for(int c = 0; c < 50; ++c) { 
            //std::cout << input[c] << std::endl;
            if(input[c] == '\n') break;
            if(input[c] == ' ') continue;
            if(i >= m) break;
            available[i] = input[c]-'0';
            //std::cout << "max["<<j<<"]"<<"["<<i<<"]" << max[j][i] << std::endl;
            ++i;
        }
     }
     
    int need[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
            //std::cout << "need [i][j]: " << need[i][j] << std::endl;
        }
    }
    
    // check if safe

    int work[m];

    for (int i = 0; i < m; ++i) {
        work[i] = available[i];
        //std::cout << work[i] << std::endl;
    }
   
    // list of which processes finished
    int finish[n];
    for(int i = 0; i < n; ++i) finish[i] = false;
    int flag = 0;
    
    // for process order
    int procList[n];
    int procInd = 0;
    
    // Make sure the loop goes around the correct number of times
    int finalCheck = 0;

    while(finalCheck < n) {
        for(int i = 0; i < n; ++i){
           
            // if finish[i] == false and need[i] <= work
            flag = 0;
            //std::cout << std::endl;
            if(finish[i] == 0) {
                for(int j = 0; j < m; ++j){
                    //std::cout << need[i][j] << " " << work[j] << std::endl;
                    
                    // flag indicates finish[i]==false and need[i] <= work
                    if(need[i][j] > work[j]) {
                        flag = 1; 
                        break;
                    }
                }
            }

            // work += allocation
            // finish[i] = true
            if(finish[i] == 1) { flag = 1; ++finalCheck; }
            //std::cout << "i is " << i << " flag is " << flag << std::endl;
            if(flag == 0) {
                procList[procInd] = i;
                ++procInd;
                for(int k = 0; k < m; ++k)
                    work[k] += allocation[i][k];
                finish[i] = 1;
                //std::cout << finish[0] << finish[1] << finish[2] << finish[3] << finish[4] << std::endl;
            }

        }
    
    }

    bool safe = true;

    for(int i = 0; i < n; ++i) 
        if(finish[i] == false) { safe = false; break; } 
    
    if(safe) {
        std::cout << "Safe, order is" << std::endl;
        for(int i = 0; i < n; ++i) {
            std::cout << "P" << procList[i] << std::endl;
        }
    }else {
        std::cout << "not safe" << std::endl;
    }


    return 0;
}
