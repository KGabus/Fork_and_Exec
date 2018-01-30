#include <iostream>
#include <string>
//#include <filesystem>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>

//namespace fs = std::filesystem;

DIR *tempDirPointer = nullptr;

int main() {
    std::cout << "Hello, World!" << std::endl;

    tempDirPointer = opendir("./var/temp");
    if (tempDirPointer == nullptr)
    {
        std::cout << "Directory /var/temp does not exist?"; //todo: verify this only gets hit when that directory doesn't exist

        tempDirPointer = opendir("./var");
        if (tempDirPointer == nullptr)
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
    }

    return 0;
}