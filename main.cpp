#include <iostream>
#include <string.h>
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



using namespace std; 

//todo: doesn't take files from other folders. Or I don't know how to enter them properly into the terminal

DIR *tempDirPointer = nullptr;

const int BUFFSIZE = 8192;
int n;
char buf[BUFFSIZE];
string compileCommand = "g++ -pass-exit-codes -std=c++14 ";
char* commandArgs[];                                                    //todo: this could be used with execv to compile the files


//class ForkAndExec {

int copyFile(char* startFileName)
{   //copies a file to a temp folder created in the same directory is the program
    //returns 0 if copy successful, -1 if read error, -2 if write error

    char endFileName[100] = "./temp/";
    strcat(endFileName, startFileName);                             //create the copied file's name/path

    compileCommand += endFileName;
    compileCommand += " ";

  //  string endFileName = "./temp" + startFileName;              //todo: strip off location path here if you're going to do it

    int startFile = open(startFileName, O_RDONLY, 0);
    int endFile = open(endFileName, O_WRONLY | O_CREAT, 0644);

    while ((n = read(startFile, buf, BUFFSIZE)) > 0) {
        if (write(endFile, buf, n) != n) {
            perror("Write Error");
            return -2;
        }
    }
    if (n < 0) {
        perror("Read Error");
        return -1;
    }


    return 0;
}

void compileFiles(string command)
{
    //todo: compile files method
    int pid = 0;
    const char* commandPointer = command.c_str();

    pid = fork();
    if (pid == 0)
    {
        //todo: this is where the compiling should happen at some point
        system(commandPointer);
    }
    cout << command << endl;

}

int main(int argCount, char* argValues[])
{
    bool noCopyErrors = true;

    char* fileName;


    tempDirPointer = opendir("./temp");
    if (tempDirPointer == nullptr) {
        std::cout
                << "Directory /temp does not exist?" << endl; //todo: verify this only gets hit when that directory doesn't exist

        int dirError = mkdir("temp", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (dirError == -1)
        {
            cout << "Could not create temp directory." << endl;
            exit(-1);
        }
        else cout << "temp directory created." << endl;
    }

    for (int fileCounter = 1; fileCounter < argCount; fileCounter++)
    {//todo: verify this gets all the files


        fileName = argValues[fileCounter];   //todo: this is a bad way to convert this to a string and concat. Find a better way
        int result = copyFile(fileName);        //todo: this is also probably bad




        switch (result)
        {
            case 0:
            {
                cout << fileName << " Copied Successfully" << endl;
                break;
            }
            case -1:
            {
                cout << fileName << " Encountered A Read Error" << endl;
                noCopyErrors = false;
                break;
            }
            case -2:
            {
                cout << fileName << " Encountered A Write Error" << endl;
                noCopyErrors = false;
                break;
            }

        }
    }


    if (noCopyErrors)
    {

        compileFiles(compileCommand);
    }

/*
    }
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
};




//};
