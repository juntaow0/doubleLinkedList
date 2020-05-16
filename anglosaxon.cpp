/* File Name: anglosaxon.cpp
 * -------------------------
 * Purpose: find top 10 most frequently
 * appearing words in the poetry files
 * that are not in the prose files
 * Author: Griffin Jeanette, Juntao Wang
 * Date: 3/3/2018
 * ----------------------
 * Modified for project 6
 * Author: Griffin Jeanette, Juntao Wang
 * Date: 4/11/2018
 * ----------------------
 * Modified for project 7
 * Author: Juntao Wang & Nam Pham
 * Data: 4/19/2018
 */

#include <iostream>
#include <string>
#include "Dlist.h"
#include "glob.h"
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <sstream>
using namespace std;

const string INPUT_DIR = "angloSaxon_Corpus";
const string POETRY_DIR  = "Poetry";
const string PROSE_DIR = "Prose";

// Return a list of filenames starting with the given pattern.
void getFiles(string pattern, List<string>& fileList)
{
	glob_t globBuffer;
	glob(pattern.c_str(), GLOB_TILDE, NULL, &globBuffer);

	for(int i = 0; i < globBuffer.gl_pathc; i++)
	{
		fileList.add(globBuffer.gl_pathv[i]);
	}

	if (globBuffer.gl_pathc > 0)
	{
		globfree(&globBuffer);
	}
}

// make each letter of a word uppercase
void toUpperCaseInPlace(string & str)
{
	for (int i = 0; i < str.length(); i++)
	{
		str[i] = toupper(str[i]);
	}
}

// remove period after some words
void removeChar(string & str)
{
 for (int i = 0; i < str.length(); i++)
 {
 	if (str[i] == '.' || str[i] == '!' || str[i] == '?')
 		str.erase(i,1);
 }
}

/*
 * Function: createVectorProse(List filenames, List & wordList)
 * Usage: createVectorProse(filenames, wordList)
 * -----------------------------------------------------------------------------
 * Creates a vector containing the unique words to the prose file.  Passes it by
 * reference so that no value is returned.
 */

void createVectorProse(List<string> filenames, List<string> & wordList)
{
	int index;
	string word;
	bool inList;
	ifstream inputFile;
	for (int i = 0; i < filenames.size(); i++)
	{
		inputFile.open(filenames[i]);
		while (inputFile >> word)
		{
			inList = true;
			toUpperCaseInPlace(word);
			removeChar(word);
			// checks to see if the word is already been found
			int i = wordList.index(word);
			if (i != -1)
			{
				inList = false;
			}
			if (inList)
			{
				wordList.add(word);
			}
		}
		inputFile.close();
	}
}

/*
 * Function: createVectorPoetry(List filenames, List & wordList,
 												 List & pwordList, List<int> & pfreqList)
 * Usage: createVectorPoetry(filenames, wordList,pwordList, pfreqList)
 * -----------------------------------------------------------------------------
 * Creates two vectors: one containing the words unique to the poetry file, meaning
 * they are not in the prose file, and then the other containing the corresponding
 * frequencies. These two lists are parallel.
 */

void createVectorPoetry(List<string> filenames, List<string> & wordList,
												 List<string> & pwordList, List<int> & pfreqList) {

	int index;
	string word;

	// true if the word is not in the pwordList
	bool inPoem;

	// true if the word is not in the prose list but in the poetry list
	bool unique;
	ifstream inputFile;
	for (int i = 0; i < filenames.size(); i++)
	{
		inputFile.open(filenames[i]);
		while (inputFile >> word)
		{
			toUpperCaseInPlace(word);
			removeChar(word);
			inPoem = true;

			// checks to see if the word is already in the poem word list first
			int i = pwordList.index(word);
			if (i != -1)
			{
				pfreqList[i] += 1;
				// if the word is found, we don't want to check the prose list
				inPoem = false;
			}
			if (inPoem)
			{
				unique = true;
				int i = wordList.index(word);
				if (i != -1)
				{
					// if the word is found, it is not unique, so we don't want to add it
					unique = false;
				}
				// add the new word because it is unique to the poetry file
				if (unique)
				{
					pwordList.add(word);
					pfreqList.add(1);
				}
			}
		}
		inputFile.close();
	}
}

/*
 * Function: sortVector(List & pwordList, List<int> & pfreqList,
 *								      List & sortWords, List<int> & sortFreq)
 * Usage: sortVector(pwordList, pfreqList, sortWords, sortFreq)
 * -----------------------------------------------------------------------------
 * Takes the poetry file words and frequencies vectors and finds the words
 * corresponding to the top ten frequencies overall.
 */

void sortVector(List<string> & pwordList, List<int> & pfreqList,
								List<string> & sortWords, List<int> & sortFreq) {

	int max;
	int index, i, j, k;

	// current word is not in the sorted list
	bool inSorted = true;
	for (i = 0; i < 10; i++)
	{
		max = -1;
		index = 0;
		for (j = 0; j < pfreqList.size(); j++)
		{
			// assume that the current word is not already in the sorted list
			inSorted = true;

			// check to see if it is in the list
			for (k = 0; k < sortWords.size(); k++)
			{
				if (pwordList[j] == sortWords[k])
				{
					// word has been included in the sorted list already
					// so we do not want to consider it as a potential max
					inSorted = false;
					break;
				}
			}
			// check to see if the max is bigger than those in the frequency list
			if (inSorted && (pfreqList[j] > max))
			{
				max = pfreqList[j];
				index = j;
			}
		}
		sortWords.add(pwordList[index]);
		sortFreq.add(max);
	}
}

/*
 * Function: findMaxTenVec(List sortWords, List<int> sortFreq)
 * Usage: findMaxTenVec(sortWords, sortFreq)
 * -----------------------------------------------------------------------------
 * Takes the poetry file words and frequencies vectors and finds the words
 * corresponding to the top ten frequencies overall.
 */

void findMaxTenVec(List<string> proseFiles, List<string> poetryFiles) {

	List<string> pwordList, wordList, sortWords;
	List<int> pfreqList, sortFreq;
	createVectorProse(proseFiles, wordList);
	createVectorPoetry(poetryFiles, wordList, pwordList, pfreqList);

	sortVector(pwordList, pfreqList, sortWords, sortFreq);

	cout << endl;
	cout << "Top 10 Words Using Vector" << endl;
	cout << "-------------------------" << endl;
	for (int i = 0; i < sortWords.size(); i++)
	{
		cout << sortWords[i] << " ------- (" << sortFreq[i] << ")" << endl;
	}
	cout << endl;
}

// main function
int main()
{
	List<string> poetryFiles, proseFiles;
	getFiles(INPUT_DIR + "/" + POETRY_DIR + "/*", poetryFiles);
	getFiles(INPUT_DIR + "/" + PROSE_DIR + "/*", proseFiles);
	findMaxTenVec(proseFiles, poetryFiles);
	return 0;
}
