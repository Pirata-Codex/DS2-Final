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
	unsigned int Bubble_comp;                      //comp = comparison
	unsigned int Bubble_swap;

	double Insertion_time;
	unsigned int Insertion_comp;
	unsigned int Insertion_swap;


	double Selection_time;
	unsigned int Selection_comp;
	unsigned int Selection_swap;

	double Merge_time;
	unsigned int Merge_comp;
	unsigned int Merge_swap;

	double Quick_time;
	unsigned int Quick_comp;
	unsigned int Quick_swap;

	double Heap_time;
	unsigned int Heap_comp;
	unsigned int Heap_swap;

public:
	void create_array(unsigned short int);
	void set_size(unsigned short int);

	//Sorting algorithms
	void bubble_sorting();
	void insertion_sorting();
	void selection_sorting();
	
	//Heap sort functions
	void max_heapify(unsigned short int *, unsigned short int, unsigned short int);
	void heapsort(unsigned short int *, unsigned short int);
	void build_maxheap(unsigned short int *, unsigned short int);

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
	Bubble_comp = Bubble_swap = 0;
	double temp_time = clock_t();
	for (unsigned short int i = 1; i < size; i++)
	{
		for (unsigned short int j = 1; i < (size - i); i++)
		{
			if (set[j - 1] > set[j])
			{
				Bubble_comp++;
				temp = set[i - 1];
				set[i] = set[i - 1];
				set[i - 1] = temp;
				Bubble_swap++;
				
			}
			Bubble_comp++;
		}
		Bubble_comp++;
				
	}
	Bubble_time = (double)(clock_t() - temp_time);
	set = backup;
	return;
}

void array_::insertion_sorting()
{
	unsigned short int tmp;
	unsigned short int j;
	Insertion_comp = Insertion_swap = 0;
	double temp_time = clock_t();
	for (unsigned short int i = 1; i < size; i++)
	{
		tmp = set[i];
		j = i - 1;
		while ((j >= 0) && (set[j] > tmp))
		{
			Insertion_comp += 2;
			set[j + 1] = set[j];	Insertion_swap++;
			j -= 1;
		}
		set[j + 1] = tmp;
		Insertion_comp++;
	}
	Insertion_time = (double)(clock_t() - temp_time);
	set = backup;
	return;
}

void array_::selection_sorting()
{
	unsigned short int first, temp;
	unsigned short int numLength = size;
	Selection_comp = Selection_swap = 0;

	double temp_time = clock_t();
	for (unsigned short int i = numLength - 1; i > 0; i--)
	{
		first = 0;                                    // initialize to subscript of first element
		for (unsigned short int j = 1; j <= i; j++)   // locate smallest between positions 1 and i.
		{
			if (set[j] < set[first])
			{
				Selection_comp++;
				first = j;
			}
				

			Selection_comp++;
		}
		temp = set[first];	         // Swap smallest found with element in position i.
		set[first] = set[i];	 
		set[i] = temp;
		Selection_swap++;

		Selection_comp++;
	}

	Selection_time = (clock_t() - temp_time);
	set = backup;
	return;
}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::: HEAP SORT :::::::::::::::::::::::::::::::::::::::::::::::::::::
void array_::build_maxheap(unsigned short int * a, unsigned short int n)
{
	for (unsigned short int i = n / 2; i >= 1; i--)
	{
		max_heapify(a, i, n);
		Heap_comp++;

	}
}

void array_::max_heapify(unsigned short int * a, unsigned short int i, unsigned short int n)
{
	unsigned short int j, temp;
	temp = a[i];
	j = 2 * i;
	while (j <= n)
	{
		if (j < n && a[j + 1] > a[j])
		{
			Heap_comp++;
			j = j + 1;
		}
		
		if (temp > a[j])
		{
			Heap_comp++;
			break;
		}
		
		else if (temp <= a[j])
		{
			Heap_comp++;
			a[j / 2] = a[j];
			j = 2 * j;
			Heap_swap++;
		}

		Heap_comp++;
	}
	a[j / 2] = temp;
	return;
}

void array_::heapsort(unsigned short int * a, unsigned short int n)
{
	unsigned short int temp;
	for (unsigned short int i = n; i >= 2; i--)
	{
		temp = a[i];
		a[i] = a[1];
		a[1] = temp;
		Heap_swap++;
		max_heapify(a, 1, i - 1);
		Heap_comp++;

	}
}

int main()
{

}