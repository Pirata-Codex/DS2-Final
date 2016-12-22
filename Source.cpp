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
#include<fstream>

using namespace std;


struct array_
{
	unsigned short int * set; //The Array that wants to get sorted
	unsigned short int * backup; //Array should turn back to his first situation after sorting
	unsigned short int size;
	

	//Time that takes to sort the array with these algorithms
	double Bubble_time;
	int Bubble_swap;
	int Bubble_copy;

	double Insertion_time;
	int Insertion_swap;
	int Insertion_copy;


	double Selection_time;
	int Selection_swap;
	int Selection_copy;

	double Merge_time;
	int Merge_swap;
	int Merge_copy;

	double Quick_time;
	int Quick_swap;
	int Quick_copy;

public:
	void create_array(unsigned short int);
	void set_size(unsigned short int);
	void bubble_sorting();
	void insertion_sorting();
	void selection_sorting();
};

void array_::create_array(unsigned short int size)
{
	srand(time(NULL));
	unsigned short int random; //The generated integer will be saved in this
	for (unsigned short int i = 0; i < size; i++)
	{
		random = time(NULL) % 10000;
		set[i] = random;
	}
	backup = set;
	return;
}

void array_::set_size(unsigned short int size_)
{
	size = size_;
	return;
}

void array_::bubble_sorting()
{
	unsigned short int temp;
	Bubble_swap = Bubble_copy = 0;
	double temp_time = clock_t();
	for (unsigned short int i = 1; i < size; i++)
	{
		for (unsigned short int j = 1; i < (size - i); i++)
		{
			if (set[j - 1] > set[j])
			{
				temp = set[i - 1];
				Bubble_copy += 1;
				set[i] = set[i - 1];
				set[i - 1] = temp;
				Bubble_swap += 1;
				
			}
		}
				
	}
	Bubble_time = (double)(clock_t() - temp_time);
	set = backup;
	return;
}

void array_::insertion_sorting()
{
	unsigned short int tmp;
	unsigned short int j;
	Insertion_copy = Insertion_swap = 0;
	double temp_time = clock_t();
	for (unsigned short int i = 1; i < size; i++)
	{
		tmp = set[i];
		Insertion_copy++;
		j = i - 1;
		while ((j >= 0) && (set[j] > tmp))
		{
			set[j + 1] = set[j];	Insertion_swap++;
			j -= 1;
		}
		set[j + 1] = tmp;
	}
	Insertion_time = (double)(clock_t() - temp_time);
	set = backup;
	return;
}

void array_::selection_sorting()
{
	int i, j, first, temp;
	int numLength = size;
	Selection_copy = Selection_swap = 0;
	for (i = numLength - 1; i > 0; i--)
	{
		first = 0;                 // initialize to subscript of first element
		for (j = 1; j <= i; j++)   // locate smallest between positions 1 and i.
		{
			if (set[j] < set[first])
				first = j;
		}
		temp = set[first];	     Selection_copy++;  // Swap smallest found with element in position i.
		set[first] = set[i];	 Selection_swap++;
		set[i] = temp;
	}
	return;
}

int main()
{

}