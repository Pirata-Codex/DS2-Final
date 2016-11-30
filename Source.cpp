/*

> Sorting Project by Reza Khaleghi
> Sort kinds: Selection, Insertion, Bubble, Merge, Quick
> Range of the index amounts is between 0 and 10000
> Array Sizes starts from 10 to 1000
> We will use "unsigned short int" to create arrays because the required range is in this kind (uses less storage and less to process)
> The purpose of this program is to assign the best sort algorithm for an specific array size 

*/

#include<iostream>
#include<time.h>

using namespace std;


struct array_
{
	unsigned short int * set; //The Array that wants to get sorted

public:
	void create_array(unsigned short int size)
	{
		srand(time(NULL));
		unsigned short int random; //The generated integer will be saved in this
		for (unsigned short int i = 0; i < size; i++)
		{
			random = time(NULL) % 10000;
			set[i] = random;
		}

	}
};

int main()
{

}