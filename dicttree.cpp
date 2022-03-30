/*CS480, Spring 2022
Assignment #1, Dictionary Tree
FILE: dicttree.cpp
Dean Quach, cssc1445
Copyright (c) 2022 Dean Quach. All rights reserved.
*/

#define NUMOfCHARS 27 /* a-z plus ' */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include "dicttree.h"
#include <iostream>
using namespace std;

//constructor for creating the node. 
dictNode* node(bool isWord){
    dictNode* tmp = new dictNode();
    tmp ->isWord = false;
    for(int i = 0; i< NUMOfCHARS; i++){
        tmp->next[i] = nullptr;
    }
    return tmp;
}

//helped out by TA Manan
bool add(dictNode* root, const char* remainingChars, const char* wordBeingInserted){      
    dictNode* head = root;//root node instantiated
    //while you have chracters remaining
    while(strlen(remainingChars) != 0){ //check if the character is null, update head for both if and else, check corresponding index if the child node exists
        int index = charPosition(remainingChars);
        if(head->next[index] == nullptr){
            //if it's null, initialize new node
            //assign head->next[index] = newNode
            dictNode* newNode = node(false);
            head->next[index] = newNode;
        }
        if(head->next[index] != nullptr){
            head = head->next[index];
        }
        remainingChars++;
    }
    if(strlen(remainingChars) == 0){
        head->isWord = true;
    }
}

//checks if the word exists from the end of the tree, if the next node in the tree is null then return null ptr
//otherwise increment to the next char until it reaches the end of the word which is head
dictNode* findEndingNodeOfAStr(struct dictNode* root, const char *remainingStr, const char *strBeingSearched){
    dictNode* head = root; //declare a root node
    while(strlen(remainingStr) > 0){ //iterate till 
        int index = charPosition(remainingStr);
        if (head->next[index] == nullptr){
            return nullptr;
        }
        else{
            head = head->next[index];
            remainingStr++;
        }
    }
    return head;
}
//increments count when the word/end of the word is true and goes through all of the characters then increments to the next one.
void countWordsStartingFromANode(struct dictNode *node, int &count){
    if (node == nullptr){ // If the dictNode given doesn't exist, don't change the count
        return;
    }
    if (node->isWord == true){
        count+=1;
    }
    // Go through all the next nodes to count
    for (int i = 0; i < NUMOfCHARS; i++){
        countWordsStartingFromANode(node->next[i], count);
    }
}


//helper function that determines the position of the character, referenced from stack overflow and c++ tutorial
int charPosition(const char* remainingChars) {
    int index = 0;
    char l;
    l = remainingChars[0]; 
    //if the value of the next 
    if((int) l == 39){
        return index = 26;
    }
    else{ //check if the char value is lowercase or upper case
        l = towlower(l);
        return index = l - 97;
    }
}
   