#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <unistd.h>


void help(){
    std::cout <<
    "Possible commands from this file:" << std::endl <<
    "   -BasicSystemPrint       -Prints with for loop" << std::endl <<
    "   -ForkSystemPrint        -Prints with fork" << std::endl <<
    "   -ThreadSystemPrint      -Prints with threads" << std::endl;
}

int main(int argc, char* argv[]){
    int nprocs = get_nprocs();
    char tmpHostname [50];
    gethostname(tmpHostname, 500);

    ofstream memFile;
    

    for (size_t i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i], "-i")){
            std::cout << "Number of processors: " << nprocs << std::endl;
            std::cout  << "Hostname: "<< tmpHostname << std::endl;
            std::cout << "Hardware platform: " <<  /proc/meminfo | grep MemTotal << std::endl;
            std::cout << std::endl;
            system("cat /proc/meminfo | grep MemTotal");
        }

          if(!strcmp(argv[i], "-f")){
             system("inxi -f");
        }

        if(!strcmp(argv[i], "-t")){
             system("inxi -t");
        }
    }
}