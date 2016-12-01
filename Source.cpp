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
	unsigned short int * temp_array; //Array should turn back to his first situation after sorting
	unsigned short int size;
	

	//Time that takes to sort the array with these algorithms
	double Bubble_time;
	int Bubble_counter;

	double Insertion_time;
	int Insertion_counter;

	double Selection_time;
	int Selection_counter;

	double Merge_time;
	int Merge_counter;

	double Quick_time;
	int Quick_counter;

public:
	void create_array(unsigned short int);
	void set_size(unsigned short int);
	void bubble_sorting();
	void insertion_sorting();
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
	temp_array = set;

}

void array_::set_size(unsigned short int size_)
{
	size = size_;
}

void array_::bubble_sorting()
{
	unsigned short int temp;
	Bubble_counter = 0;
	double temp_time = clock_t();
	for (unsigned short int i = 1; i < size; i++)
	{
		for (unsigned short int j = 1; i < (size - i); i++)
		{
			if (set[j - 1] > set[j])
			{
				temp = set[i - 1];
				set[i] = set[i - 1];
				set[i - 1] = temp;
				Bubble_counter += 3;
			}
		}
				
	}
	Bubble_time = (double)(clock_t() - temp_time);
	set = temp_array;
}

void array_::insertion_sorting()
{
	unsigned short int tmp;
	unsigned short int j;
	Insertion_counter = 0;
	double temp_time = clock_t();
	for (unsigned short int i = 1; i < size; i++)
	{
		tmp = set[i];
		Insertion_counter++;
		j = i - 1;
		while ((j >= 0) && (set[j] > tmp))
		{
			set[j + 1] = set[j];
			Insertion_counter++;
			j -= 1;
		}
		set[j + 1] = tmp;
		Insertion_counter++;
	}
	Insertion_time = (double)(clock_t() - temp_time);
	set = temp_array;
}


int main()
{

}