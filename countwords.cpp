/*CS480, Spring 2022
Assignment #2, POSIX Tree
FILE: countwords.cpp
Dean Quach, cssc1445
Copyright (c) 2022 Dean Quach. All rights reserved.
*/

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
#include <pthread.h>
using namespace std;

//increments count when the word/end of the word is true and goes through all of the characters then increments to the next one.
void* posix_countWordsStartingFromANode(void *ptr){
    EXEC_STATUS* temp = (EXEC_STATUS*) ptr; //the pointer created and passed in by the data structure
    char* fname = (char *)ptr;
    FILE *testFile = fopen(temp->filePath[1], "r");
    std::ifstream testStream;
    testStream.open(temp->filePath[1]); //opens test file
    ofstream output;
    output.open("countwords_output.txt"); //opens solution output textfile
    std::string test;
    char stream[1000];
    const char *delimiters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~"; //this is needed for parsing the testfile
    if(!testStream.is_open()){
        cout << "Unable to open <<" << temp->filePath[1] << ">>" << endl;
        exit(1);
    }
    temp->numOfCharsProcessedFromFile[TESTFILEINDEX] = 0; //set values of num processed & word count to 0
    temp->wordCountInFile[TESTFILEINDEX] = 0;
    while(std::getline(testStream, test)){
        int count = 0;
        if(fgets(stream, 1000, testFile) == NULL){
            break;
        }
        temp->numOfCharsProcessedFromFile[TESTFILEINDEX] += test.length() + 1; //counts the number of characters processed in test file
        char *word = strtok(stream,delimiters);
        while(word !=NULL){
            int count = temp->dictRootNode->isWord ? 1 : 0; //determines where the count variable should be 1 or 0
            dictNode *tmp = findEndingNodeOfAStr(temp->dictRootNode, word, test.c_str());
            countWordsStartingFromANode(tmp, count);
            output << word << " " << count << endl;
            temp->wordCountInFile[TESTFILEINDEX]++; //increases the words count in the testfile
            word = strtok(nullptr, delimiters);
        }
    }
    printf("There are %d words in %s.",temp->wordCountInFile[TESTFILEINDEX], temp->filePath[TESTFILEINDEX]);
    cout << "\n";
    temp->taskCompleted[TESTFILEINDEX] = true;
    cout.flush();
    output.close();
}

