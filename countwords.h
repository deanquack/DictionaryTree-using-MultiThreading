/*CS480, Spring 2022
Assignment #1, Dictionary Tree
FILE: countwords.h
Dean Quach, cssc1445
Copyright (c) 2022 Dean Quach. All rights reserved.
*/

#ifndef COUNTWORDS_H_
#define COUNTWORDS_H_

#include <stdlib.h>

#define NUMOfCHARS 27 // a-z + '
using namespace std;

void * posix_countWordsStartingFromANode(void *ptr); //counts the words in the test file
#endif