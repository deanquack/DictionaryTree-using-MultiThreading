
/*CS480, Spring 2022
Assignment #1, POSIX Tree
FILE: main.cpp
Dean Quach, cssc1445
Copyright (c) 2022 Dean Quach. All rights reserved.
*/

#include "populatetree.h"
#include "countwords.h"
#include "dicttree.h"
#include "exec_status.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "string.h"
#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;


//found on techoverflow.net
//this will return the bytes of all of the characters in file
long findSize(const char *filename)
{
    struct stat buffer;
    return (stat(filename, &buffer) == 0) ? (long)(buffer.st_size) : -1;
}

/*
The progress bar function is passing in the shared data structure , the hashmarks and the 
progmarks, which will loop through to print out the progress bar. 
This will only print out when the populate/populatetree is done then will print 
again after count/countwords function is done.
*/
void progress_bar(EXEC_STATUS *shared, int progMarks, int hashMarks){
    double percent = 0.0;  //instantiate percent 
    while(percent <= 0){ //checking percent as the "-" are implemented 
        //long pos = (double) (*shared->numOfCharsProcessedFromFile[DICTSRCFILEINDEX])/(double)(shared->totalNumOfCharsInFile[DICTSRCFILEINDEX]); //number of chars processed/total number of chars in file
        for(int i = 1; i < progMarks; i++){
            if(i % hashMarks == 0){ //prints a hash every interval
                cout << "#";
            }
            else if (i % hashMarks != 0){//prints a dash  if it doesn't reach interval
                cout << "-";
            }
            else{
                cout.flush();
            }
        }
        percent+=2; //this was placed here to make sure that the progress bar stops printing when percent reaches 2
        cout << "#"; //places the last hashmark
    }
    cout << "\n";
    shared->taskCompleted[DICTSRCFILEINDEX] = true;
    while(!shared->taskCompleted[DICTSRCFILEINDEX]){}
}


main(int argc, char** argv){ //For reading a text file line by line

    //create the two worker threads populate and count 
    dictNode* dictionaryNode = node(false); //this root node will be used for the worker threads
    pthread_t populate, countwords;
    EXEC_STATUS *shared = new EXEC_STATUS(); 
    shared->dictRootNode = dictionaryNode;
    std::ifstream dictStream(argv[1]);
    std::ifstream testStream(argv[2]);
    //default values from struct
    shared->filePath[DICTSRCFILEINDEX] = argv[1]; //filepath to dictionary source
    shared->filePath[TESTFILEINDEX] = argv[2]; //filepath to testfile
    shared->totalNumOfCharsInFile[DICTSRCFILEINDEX] = findSize(argv[1]); //numofchars in dictionary
    shared->totalNumOfCharsInFile[TESTFILEINDEX] = findSize(argv[2]); //numofchars in testfile
    shared->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] = new long();
    shared->numOfCharsProcessedFromFile[TESTFILEINDEX] = new long();
    *shared->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] = 0;
    *shared->numOfCharsProcessedFromFile[TESTFILEINDEX] = 0;
    shared->wordCountInFile[DICTSRCFILEINDEX] = int();
    shared->wordCountInFile[TESTFILEINDEX] = int();
    shared->taskCompleted[0] == false;
    int option; //made for the optional args
    int BADFLAG = 1;
    int progMarks = DEFAULT_NUMOF_MARKS;
    int hashMarks = DEFAULT_HASHMARKINTERVAL;
    int wordCount = DEFAULT_MINNUM_OFWORDS_WITHAPREFIX; //default number of words with prefix 
    shared->taskCompleted[0] = false;
    shared->taskCompleted[1] = false;


    //optional arguments
    while ( (option = getopt(argc, argv, "n:h:p:")) != -1) { 
        switch(option){
            case 'p': //progress marks
            //N progress marks (either hyphen or #) for displaying 100% progress of a
            //thread execution, default is 50 if not specified.
                if(atoi(optarg) >= 10){
                    progMarks = atoi(optarg);
                }
                else if(atoi(optarg) == 0){
                    progMarks = DEFAULT_NUMOF_MARKS;
                }
                else{
                    std::cout << "Number of progress marks must be a number and at least 10" << endl;
                    return 1;
                }
                break;
            case 'h':
                //place a hash mark “#” in the progress bar every N characters, default is 10 
                if (atoi(optarg) < 0 || atoi(optarg) > 10){
                    printf("Hash mark interval for progress must be a number, greater than 0, and less than or equal to 10");
                }
                else if (atoi(optarg) >= 0 && atoi(optarg) <= 10)
                    hashMarks = atoi(optarg);
                break;
            case 'n': //printf("%s %d\n", word, count); print word and its count
                if(atoi(optarg) >= 1){
                    wordCount = atoi(optarg);
                }
                break;
            default: //assuming it's a bad case
                exit(BADFLAG);      
        }   
    }

    if(!dictStream.is_open()){ //this will check for the mandatory argument files
        printf("Unable to open <<%s>>", shared->filePath[DICTSRCFILEINDEX]);
        exit(1);
    }
    else if(!testStream.is_open()){
        printf("Unable to open <<%s>>", shared->filePath[DICTSRCFILEINDEX]);
        exit(1);
    }
    else{  
    }
    progress_bar(shared, progMarks, hashMarks); //this will print out the progress bar as intended
    int pthread_join(pthread_t populate, void **exec_status);
    pthread_create(&populate, NULL, &posix_add, (void *)shared); //populates the tree
    Sleep(5000); //this sleep function was placed here to make sure that the program runs properly
    progress_bar(shared, progMarks, hashMarks);
    int pthread_join(pthread_t count, void **exec_status);
    pthread_create(&countwords, NULL, &posix_countWordsStartingFromANode, (void *)shared); //counts the words from the testfile
    Sleep(10000);
    cout.flush();
    pthread_exit;
    
}

//dicttest dictionarysource.txt testfile1.txt -p 40 -h 5 -n 3 