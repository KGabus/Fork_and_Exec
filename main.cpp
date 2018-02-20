#include <iostream>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


using namespace std;

DIR *tempDirPointer = nullptr;

const int BUFFSIZE = 8192;
int n;
char buf[BUFFSIZE];
string fileNameArray[20];



    int copyFile(char* startFileName, char* endFileName)
    {   //copies a file to a temp folder created in the same directory is the program
        //returns 0 if copy successful, -1 if read error, -2 if write error
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

        close(startFile);
        close(endFile);

        return 0;
    }

    void compileFiles(int argCount, char* fileNames[])
    {
        pid_t pid;
        int status;

        char* gppCommandArray[25];
        gppCommandArray[0] = (char*)"g++";
        gppCommandArray[1] = (char*)"-pass-exit-codes";
        gppCommandArray[2] = (char*)"-std=c++14";
        gppCommandArray[3] = (char*)"-o";
        gppCommandArray[4] = (char*)"Gabus.out";

        for (int loopIndex = 1; loopIndex < argCount; loopIndex++)
        {   //copy files to be compiled into g++ command arg array
            gppCommandArray[loopIndex + 4] = fileNames[loopIndex];
        }

        gppCommandArray[argCount + 4] = (char*)NULL;

        cout << "Compile command: ";
        for (int loopIndex = 0; loopIndex <= argCount + 3; loopIndex++)
            cout << gppCommandArray[loopIndex] << " ";
        cout << endl;

        pid = fork();
        if (pid >= 0)
        {   //fork succeeded
            if (pid == 0)
            {   //this is the child process
                execvp(gppCommandArray[0], gppCommandArray);
            }
            else
            {   //parent process
                wait(&status);
                if (WEXITSTATUS(status) > 0)                            //g++ uses positive return codes for failures and 0 for success
                    cout << "Could not compile files." << endl;
                else cout << "File compilation successful." << endl;
            }
        }
    }

    int main(int argCount, char* argValues[])
    {
        bool noCopyErrors = true;
        int fileCounter;
        size_t lastSlash;
        char endFileName[100] = "./temp/";

        char* fileName;

        tempDirPointer = opendir("./temp");
        if (tempDirPointer == nullptr) {
            cout << "Directory /temp does not exist." << endl;

            int dirError = mkdir("temp", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            if (dirError == -1)
            {
                cout << "Could not create temp directory." << endl;
                exit(-1);
            }
            else cout << "temp directory created." << endl;
        }

        for (fileCounter = 1; fileCounter < argCount; fileCounter++)
        {
            fileName = argValues[fileCounter];

            //remove path from entered files
            string tempStr = fileName;                                  //todo: make this less terrible
            lastSlash = tempStr.find_last_of("/\\");
            tempStr = tempStr.substr(lastSlash + 1);
            char* tempName = new char[tempStr.length() + 1];
            strcpy(tempName, tempStr.c_str());
            strcat(endFileName, tempName);


            int result = copyFile(fileName, endFileName);

            fileNameArray[fileCounter - 1] = endFileName;                      //add the file to the array that gets used in the compile command

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
            compileFiles(argCount, argValues);
        }

        exit(0);
    };

