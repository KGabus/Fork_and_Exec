#include <iostream>
#include <string>
//#include <filesystem>
#include <fstream>
#include <dirent.h>

//namespace fs = std::filesystem;

DIR *tempDirPointer = NULL;

int main() {
    std::cout << "Hello, World!" << std::endl;

    tempDirPointer = opendir("./var/temp");
    if (tempDirPointer == NULL)
        std::cout << "Directory /var/temp does not exist?";

    return 0;
}