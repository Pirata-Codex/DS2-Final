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
	unsigned int Merge_copy;

	double Quick_time;
	unsigned int Quick_comp;
	unsigned int Quick_swap;

	double Heap_time;
	unsigned int Heap_comp;
	unsigned int Heap_swap;

public:
	void create_array(unsigned short int);
	void set_size(unsigned short int);

	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::: ALGORITHMS :::::::::::::::::::::::::::::::::::::::::::::::::::::
	void bubble_sorting();
	void insertion_sorting();
	void selection_sorting();
	
	//Heap sort functions
	void max_heapify(unsigned short int *, unsigned short int, unsigned short int);
	void heapsort(unsigned short int *, unsigned short int);
	void build_maxheap(unsigned short int *, unsigned short int);

	//Merge sort functions
	void merge(unsigned short int *, unsigned short int, unsigned short int, unsigned short int);
	void mergesort(unsigned short int *, unsigned short int, unsigned short int);

	//Quick sort functions
	void swap(unsigned short int *, unsigned short int *);
	int partition(unsigned short int arr[], unsigned short int low, unsigned short int high);
	void quicksort(unsigned short int *, unsigned short int, unsigned short int);
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	void sort_array();

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
	Heap_comp = Heap_swap = 0;
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

	double temp_time = clock_t();
	for (unsigned short int i = n; i >= 2; i--)
	{
		temp = a[i];
		a[i] = a[1];
		a[1] = temp;
		Heap_swap++;
		max_heapify(a, 1, i - 1);
		Heap_comp++;

	}
	Heap_time = (clock_t() - temp_time);
}



//:::::::::::::::::::::::::::::::::::::::::::::::::::::::: MERGE SORT :::::::::::::::::::::::::::::::::::::::::::::::::::::

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void array_::merge(unsigned short int * arr, unsigned short int l, unsigned short int m, unsigned short int r)
{
	unsigned short int i, j, k;
	unsigned short int n1 = m - l + 1;
	unsigned short int n2 = r - m;

	/* create temp arrays */
	unsigned short int * L, *R;
	L = new unsigned short int[n1];
	R = new unsigned short int[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
	{
		L[i] = arr[l + i];
		Merge_copy++;
		Merge_comp++;
	}
		
	for (j = 0; j < n2; j++)
	{
		R[j] = arr[m + 1 + j];
		Merge_copy++;
		Merge_comp++;
	}
		

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			Merge_comp++;
			arr[k] = L[i];
			Merge_copy++;
			i++;
		}
		else
		{
			Merge_comp++;
			arr[k] = R[j];
			Merge_copy++;
			j++;
		}
		k++;
		Merge_comp++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		arr[k] = L[i];
		Merge_copy++;
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		arr[k] = R[j];
		Merge_copy++;
		j++;
		k++;
	}
}

void array_::mergesort(unsigned short int * arr, unsigned short int l, unsigned short int r)
{
	Merge_comp = Merge_copy = 0;
	if (l < r)
	{
		Merge_comp++;
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		unsigned short int m = l + (r - l) / 2;

		// Sort first and second halves
		mergesort(arr, l, m);
		mergesort(arr, m + 1, r);

		merge(arr, l, m, r);
	}

}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::: QUICK SORT :::::::::::::::::::::::::::::::::::::::::::::::::::::
void array_::swap(unsigned short int * a, unsigned short int * b)
{
	int t = *a;
	*a = *b;
	*b = t;
	Quick_swap++;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int array_::partition(unsigned short int arr[], unsigned short int low, unsigned short int high)
{
	unsigned short int pivot = arr[high];    // pivot
	unsigned short int i = (low - 1);  // Index of smaller element

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (arr[j] <= pivot)
		{
			Quick_comp++;
			i++;    // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
		Quick_comp++;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}


/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low  --> Starting index,
high  --> Ending index */
void array_::quicksort(unsigned short int * arr, unsigned short int low, unsigned short int high)
{
	Quick_comp = Quick_swap = 0;

	double temp_time = clock_t();
	if (low < high)
	{
		Quick_comp++;
		/* pi is partitioning index, arr[p] is now
		at right place */
		unsigned short int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quicksort(arr, low, pi - 1);
		quicksort(arr, pi + 1, high);
	}
	Quick_time = (clock_t() - temp_time);
}

void array_::sort_array()
{
	create_array(size);

}



int main()
{

}
