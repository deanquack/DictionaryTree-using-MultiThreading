/*CS480, Spring 2022
Assignment #1, Dictionary Tree
FILE: dicttree.h
Dean Quach, cssc1445
Copyright (c) 2022 Dean Quach. All rights reserved.
*/

#ifndef DICTTREE_H_
#define DICTTREE_H_

#include <stdlib.h>

#define NUMOfCHARS 27 // a-z + '
using namespace std;

struct dictNode {
        dictNode* next[NUMOfCHARS];
        bool isWord;
    };

dictNode *node(bool isWord);
bool add(struct dictNode *root, const char *remainingChars, const char *wordBeingInserted = nullptr); 
dictNode* findEndingNodeOfAStr(struct dictNode* root, const char *remainingStr, const char *strBeingSearched);
void countWordsStartingFromANode(struct dictNode* root, int &count);
int charPosition(const char* character);

#endif