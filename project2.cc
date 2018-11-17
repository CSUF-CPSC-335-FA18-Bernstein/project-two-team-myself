///////////////////////////////////////////////////////////////////////////////
// project2.h
//
// The three algorithms specified in the project 1 requirements
// document, plus helper functions.
//
///////////////////////////////////////////////////////////////////////////////

#include "project2.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <iostream>

using namespace std;


//-----------------------------------------------------------------------------
// Randomize the order of all items in the list
//-----------------------------------------------------------------------------
void randomize_list(string_vector & strings) 
{
	random_shuffle(strings.begin(), strings.end());
}

//-----------------------------------------------------------------------------
void merge(string_vector & strings, size_t start, size_t mid, size_t end) 
{
	size_t i, j, k;
	size_t n1 = mid - start + 1;
	size_t n2 = end - mid;

	string_vector tempS, tempE;

	for (i = 0; i < n1; i++)
	{
		tempS.push_back(strings[start + i]);
	}
	for (j = 0; j < n2; j++)
	{
		tempE.push_back(strings[mid + 1 + j]);
	}
	
	i = 0;
	j = 0;
	k = start;

	while (i < n1&&j < n2)
	{
		if (tempS[i] <= tempE[j])
		{
			strings[k] = tempS[i];
			i++;
		}
		else
		{
			strings[k] = tempE[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		strings[k] = tempS[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		strings[k] = tempE[j];
		j++;
		k++;
	}
}

//-----------------------------------------------------------------------------
// Sort the given list using the merge sort algorithm.
// This is a recursive method which splits the list into two
// parts, recursively calls itself on the two parts and then merges 
// the two parts together using the merge() method.
//-----------------------------------------------------------------------------
void mergesort(string_vector & strings, size_t start, size_t end) 
{

	if (start < end)
	{
		size_t mid = ((start+end) / 2);
		
		mergesort(strings, start, mid);
		mergesort(strings, mid + 1, end);
		merge(strings, start, mid, end);
		
	}

}

//-----------------------------------------------------------------------------
// Implementation of the Hoare Partition.
// This partition uses the first element of the list as a partition
// and divides the list into less than and greater than the pivot value
// It returns the index of the final position of the pivot value.
//-----------------------------------------------------------------------------
int hoare_partition(string_vector & strings, int start, int end) 
{
	string_vector x;
	x.push_back(strings[start]);
	int i = start;
	int j = end;

	while (1)
	{
		while (strings[i] < x[0])
		{
			i++;
		}

		while (strings[j] > x[0])
		{
			j--;
		}
	
		if (i >= j)
		{
			return j;
		}
		swap(strings[i], strings[j]);
	}

	return 0;
}

//-----------------------------------------------------------------------------
// Sort the given list using the quicksort algorithm.
// This is a recursive method which splits the list into two
// parts, recursively calls itself on the two parts and then merges 
// the two parts together using the merge() method.
//-----------------------------------------------------------------------------
void quicksort(string_vector & strings, int start, int end) 
{
	if (start < end)
	{
		int pivot = hoare_partition(strings, start, end);
		quicksort(strings, start, pivot);
		quicksort(strings, pivot + 1, end);
	}
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// ALREADY IMPLEMENTED 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Load words from the file at the given path. The words vector is
// cleared, and then each word from the file is added to the
// vector. Returns true on success or fale on I/O error.
//-----------------------------------------------------------------------------
bool load_words(string_vector& words, const std::string& path)
{
	//std::cout << "Loading words from [" << path << "]" << std::endl;
	words.clear();
	std::ifstream ifs(path.c_str());
	if (!ifs.is_open() || !ifs.good()) {
		//cout << "Failed to open [" << path << "]" << std::endl;
		return false;
	}
	int countWordsLoaded = 0;
	while (!ifs.eof()) {
		std::string lineBuffer;
		std::getline(ifs, lineBuffer);
		if (ifs.eof()) {
			break;
		}
		words.push_back(lineBuffer);
		countWordsLoaded++;
	}
	//std::cout << "Loaded " << countWordsLoaded << " words from [" << path << "]" << std::endl;;
	return true;
}

//-----------------------------------------------------------------------------
// Sort the given list using the merge sort algorithm.
// This method is simply a helper to make the initial 
// call the recursive mergesort() method below that requires
// first and last indexes for sorting range
//-----------------------------------------------------------------------------
void mergesort(string_vector & strings) 
{
	mergesort(strings, 0, strings.size() - 1);
}

//-----------------------------------------------------------------------------
// Sort the given list using the quicksort algorithm.
// This method is simply a helper to make the initial 
// call the recursive mergesort() method below that requires
// first and last indexes for sorting range
//-----------------------------------------------------------------------------
void quicksort(string_vector & strings) 
{
	if (strings.size() == 0) {
		return;
	}
	quicksort(strings, 0, strings.size() - 1);
	return;
}
