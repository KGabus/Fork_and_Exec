#include <iostream>
#include <string>
#include <experimental/filesystem>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>


//namespace fs = std::experimental/__cpp_lib_experimental_filesystem;
using namespace std;
DIR *tempDirPointer = nullptr;

const int BUFFSIZE = 8192;
//extern int errno;

//class ForkAndExec {
    int main(int argCount, char* argValues[]) {
        std::cout << "Hello, World!" << std::endl;
        int testFileLocation = open("startdoc", O_RDONLY, 0);
        int testDestination = open("enddoc", O_WRONLY | O_CREAT, 0644);
        int n;
        char buf[BUFFSIZE];

        while ((n = read(testFileLocation/*STDIN_FILENO*/, buf, BUFFSIZE)) > 0){
            if (write(testDestination/*STDOUT_FILENO*/, buf, n) != n){
                perror("Write Error");
            }
        }
        if (n < 0){
            perror("Read Error");
        }
/*
        tempDirPointer = opendir("./temp");
        if (tempDirPointer == nullptr)
        {
            std::cout << "Directory /temp does not exist?"; //todo: verify this only gets hit when that directory doesn't exist

            int dirError = mkdir("temp", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            if (dirError == -1)
                std::cout << "Could not create temp directory.";
            else std::cout << "temp directory created.";
            tempDirPointer = opendir("./temp");
    /*        if (tempDirPointer == nullptr)
        {
            std::cout << "Creating /var directory";
            int dirError = mkdir("var", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            if (dirError == -1)
            {
                std::cout << "Could not create directory";
                //todo: set this up to do some type of return when it gets broken out into a method
            }
            else
            {
                tempDirPointer = opendir("./var");
                dirError = mkdir("temp", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);    //todo: doesn't currently create a sub folder
                if (dirError == -1)
                    std::cout << "Well that didn't work";
            }

        }
    */
/*        }
        else
        {
            std::cout << "temp directory exists";
            std::experimental::filesystem::copy(testFileLocation, testDestination);
        }
*/
        exit(0);
    }


//};
