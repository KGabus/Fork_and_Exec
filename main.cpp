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
string commandArgs[20];                                                    //todo: this could be used with execv to compile the files



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

    void compileFiles(int argCount)
    {
        //todo: compile files method
        int pid = 0;
  //      const char* commandPointer = command.c_str();

        const char* gppCommandArray[20];
        gppCommandArray[0] = "g++";
        gppCommandArray[1] = "-pass-exit-codes";
        gppCommandArray[2] = "-std=c++14";

        for (int loopIndex = 0; loopIndex < argCount - 1; loopIndex++)
        {   //copy files to be compiled into g++ command arg array
            gppCommandArray[loopIndex + 3] = commandArgs[loopIndex].c_str();    //todo: this should build the command args array for execlp. In theory. Maybe
        }


        pid = fork();
        if (pid == 0)
        {
            //todo: this is where the compiling should happen at some point
            execlp(gppCommandArray[0], gppCommandArray[20]);                    //todo: test this a lot
  //      system(commandPointer);                                                 //todo: use execlp instead
    /*        if (execv("/usr/bin/cc", commandArgs) > 0)                        //todo: this doesn't currently work because of permissions or something
                cout << "Could not compile files." << endl;
            else cout << "File compilation successful." << endl;
    */    }
     //   cout << command << endl;

    }

    int main(int argCount, char* argValues[])
    {
        bool noCopyErrors = true;
        int fileCounter;

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

        for (fileCounter = 1; fileCounter < argCount; fileCounter++)
        {//todo: verify this gets all the files


            fileName = argValues[fileCounter];   //todo: this is a bad way to convert this to a string and concat. Find a better way
            int result = copyFile(fileName);        //todo: this is also probably bad

            commandArgs[fileCounter - 1] = fileName;


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

        commandArgs[fileCounter] = "\0";        //the array passed to execv must be null terminated

        if (noCopyErrors)
        {

            compileFiles(argCount);
        }
            exit(0);
    };

