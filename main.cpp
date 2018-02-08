#include <iostream>
#include <string>
#include <experimental/filesystem>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>


//namespace fs = std::experimental/__cpp_lib_experimental_filesystem;
using namespace std;
DIR *tempDirPointer = nullptr;

class ForkAndExec {
    int main() {
        std::cout << "Hello, World!" << std::endl;
        string testFileLocation = "";
        string testDestination = "";

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
        }
        else
        {
            std::cout << "temp directory exists";
            std::experimental::filesystem::copy(testFileLocation, testDestination);
        }

        return 0;
    }
};
