#include <iostream>
#include <sstream>
#include <string.h>
#include <math.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <thread>
#include <vector>


void help(){
    std::cout <<
    "Possible commands from this file:" << std::endl <<
    "   -BasicSystemPrint       -Prints with for loop" << std::endl <<
    "   -ForkSystemPrint        -Prints with fork" << std::endl <<
    "   -ThreadSystemPrint      -Prints with threads" << std::endl;
}

void printSystemSpecs(){
    int nprocs = get_nprocs();
    char tmpHostname [50];
    gethostname(tmpHostname, 500);

    //Hardware platform
    utsname hardware_platform;
    uname(&hardware_platform);    

    std::cout << "Number of processors: " << nprocs << std::endl;
    std::cout  << "Hostname: "<< tmpHostname << std::endl;
    std::cout << "Hardware platform: " << hardware_platform.machine << std::endl;
    system("cat /proc/meminfo | grep MemTotal");
}

void printSumWithForks(int x){
    for (int w = 0; w < x; w++)
    {
        int pid = fork();
        if(pid == 0){
            // cool cool
        }
        else{
            double sum = 0;
            for (int i = 1; i < 5000; i++)
            {
                for (int j = 1; j < i; j++)
                {
                    sum += sqrt(i*j);
                }
            }
            std::cout << "PID: " << pid << " Sum of calc: " << sum << "\n\n";

        }
    }
}

void threadWork(){
    double sum = 0;
    for (int i = 1; i < 5000; i++)
    {
        for (int j = 1; j < i; j++)
        {
            sum += sqrt(i*j);
        }
    }
    std::cout << "PID: " << getpid() << " Sum of calc: " << sum << "\n\n";
}


void printSumWithThreads(int x){
    std::vector<std::thread> threads;
    for (int w = 0; w < x; w++)
    {
        threads.push_back(std::thread(threadWork));
    }
    for (int i = 0; i < x; i++)
    {
        threads.back().join();
        threads.pop_back();
    }    
}    


int main(int argc, char* argv[]){
    
    if(argc == 0){
        help();
    }
    for(int i = 0; i < argc; i++){
        if(!strcmp(argv[i], "-i")){
            printSystemSpecs();
        }

        if(!strcmp(argv[i], "-f")){
            if(atoi(argv[i+1]) <= 0){
                std::cout << "missing arguments" << std::endl;
            }
            else{
                printSumWithForks(std::atoi(argv[i+1]));
            }
        }

        if(!strcmp(argv[i], "-t")){
            if(atoi(argv[i+1]) <= 0 ){
                std::cout << "missing arguments" << std::endl;
            }
            else{
                printSumWithThreads(std::atoi(argv[i+1]));
            }
        }
    }
}