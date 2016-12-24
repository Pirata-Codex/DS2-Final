/*

> Sorting Project by Reza Khaleghi
> Sort kinds: Selection, Insertion, Bubble, Merge, Quick
> Range of the index amounts is between 0 and 10000
> Array Sizes starts from 10 to 1000
> We will use "int" to create arrays because the required range is in this kind (uses less storage and less to process)
> The purpose of this program is to assign the best sort algorithm for an specific array size 

*/

#include<iostream>
#include<time.h>
#include<fstream>

using namespace std;


struct array_
{
	int * set; //The Array that wants to get sorted
	int * backup; //Array should turn back to his first situation after sorting
	int size;
	

	//Time that takes to sort the array with these algorithms
	double Bubble_time;
	unsigned int Bubble_comp;                      //comp = comparison
	unsigned int Bubble_swap;
	unsigned int B_Sum;

	double Insertion_time;
	unsigned int Insertion_comp;
	unsigned int Insertion_swap;
	unsigned int I_Sum;


	double Selection_time;
	unsigned int Selection_comp;
	unsigned int Selection_swap;
	unsigned int S_Sum;


	double Merge_time;
	unsigned int Merge_comp;
	unsigned int Merge_copy;
	unsigned int M_Sum;


	double Quick_time;
	unsigned int Quick_comp;
	unsigned int Quick_swap;
	unsigned int Q_Sum;


	double Heap_time;
	unsigned int Heap_comp;
	unsigned int Heap_swap;
	unsigned int H_Sum;


public:
	void create_array(int);
	void set_size(int);
	void minimum();

	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::: ALGORITHMS :::::::::::::::::::::::::::::::::::::::::::::::::::::
	void bubble_sorting();
	void insertion_sorting();
	void selection_sorting();
	
	//Heap sort functions
	void max_heapify(int *, int, int);
	void heapsort(int *, int);
	void build_maxheap(int *, int);

	//Merge sort functions
	void merge(int *, int, int, int);
	void mergesort(int *, int, int);

	//Quick sort functions
	void swap(int *, int *);
	int partition(int *, int , int );
	void quicksort(int *, int, int);
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	void sort_array();

};

void array_::create_array(int size)
{
	//srand(time(NULL));
	set = new int[size];
	int random; //The generated integer will be saved in this
	for (int i = 0; i < size; i++)
	{
		random = rand() % 10000;
		//cout << random << " ,";
		set[i] = random;
	}

	backup = new int[size];
	backup = set;
	return;
}

void array_::set_size(int size_)
{
	size = size_;
	return;
}

void array_::bubble_sorting()
{
	int temp;
	Bubble_comp = Bubble_swap = 0;
	double temp_time = clock_t();
	for (int i = 1; i < size; i++)
	{
		for (int j = 1; j < (size - i); j++)
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
	int tmp;
	int j;
	Insertion_comp = Insertion_swap = 0;
	double temp_time = clock_t();
	for (int i = 1; i < size; i++)
	{
		tmp = set[i];
		j = i - 1;
		while ((j >= 0) && (set[j] > tmp))
		{
			Insertion_comp += 2;
			set[j + 1] = set[j];	
			Insertion_swap++;
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
	int first, temp;
	Selection_comp = Selection_swap = 0;

	double temp_time = clock_t();
	for (int i = (size - 1); i > 0; i--)
	{
		first = 0;                                    // initialize to subscript of first element
		for (int j = 1; j <= i; j++)   // locate smallest between positions 1 and i.
		{
			if (set[j] > set[first])
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
void array_::build_maxheap(int * a, int n)
{
	Heap_comp = Heap_swap = 0;
	for (int i = n / 2; i >= 1; i--)
	{
		max_heapify(a, i, n);
		Heap_comp++;

	}
}

void array_::max_heapify(int * a, int i, int n)
{
	int j, temp;
	temp = a[i];
	j = 2 * i;
	while (j <= n)
	{
		if (j < n && a[j + 1] > a[j])
		{
			Heap_comp += 2;
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

void array_::heapsort(int * a, int n)
{
	int temp;

	double temp_time = clock_t();
	for (int i = n; i >= 2; i--)
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
void array_::merge(int * arr, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int * L, *R;
	L = new int[n1];
	R = new int[n2];

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
		Merge_comp += 2;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		arr[k] = L[i];
		Merge_copy++;
		i++;
		k++;
		Merge_comp++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		arr[k] = R[j];
		Merge_copy++;
		j++;
		k++;
		Merge_comp++;
	}
}

void array_::mergesort(int * arr, int l, int r)
{
	Merge_comp = Merge_copy = 0;

	double temp_time = clock_t();
	if (l < r)
	{
		Merge_comp++;
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;

		// Sort first and second halves
		mergesort(arr, l, m);
		mergesort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
	Merge_time = (clock_t() - temp_time);
	
}

//
////:::::::::::::::::::::::::::::::::::::::::::::::::::::::: QUICK SORT :::::::::::::::::::::::::::::::::::::::::::::::::::::
//void array_::swap(int * a, int * b)
//{
//	int t = *a;
//	*a = *b;
//	*b = t;
//	Quick_swap++;
//}
//
///* This function takes last element as pivot, places
//the pivot element at its correct position in sorted
//array, and places all smaller (smaller than pivot)
//to left of pivot and all greater elements to right
//of pivot */
//int array_::partition(int * arr, int low, int high)
//{
//	int pivot = arr[high];    // pivot
//	int i = (low - 1);  // Index of smaller element
//
//	for (int j = low; j <= high - 1; j++)
//	{
//		// If current element is smaller than or
//		// equal to pivot
//		if (arr[j] <= pivot)
//		{
//			Quick_comp++;
//			i++;    // increment index of smaller element
//			swap(&arr[i], &arr[j]);
//		}
//		Quick_comp++;
//	}
//	swap(&arr[i + 1], &arr[high]);
//	return (i + 1);
//}
//
//
///* The main function that implements QuickSort
//*arr --> Array to be sorted,
//low  --> Starting index,
//high  --> Ending index */
//void array_::quicksort(int * arr, int low, int high)
//{
//	Quick_comp = Quick_swap = 0;
//
//	double temp_time = clock_t();
//	if (low < high)
//	{
//		Quick_comp++;
//		/* pi is partitioning index, arr[p] is now
//		at right place */
//		int pi = partition(arr, low, high);
//
//		// Separately sort elements before
//		// partition and after partition
//		quicksort(arr, low, pi - 1);
//		quicksort(arr, pi + 1, high);
//	}
//	Quick_time = (clock_t() - temp_time);
//}
//
void array_::sort_array()
{
	ofstream file("Results.txt", ofstream::in);
	file << "Size\tBubble time\tBubble swaps\tBubble comparisons\t"
		"Insertion time\tInsertion swaps\tInsertion comparisons\t"
		"Selection time\tSelection swaps\tSelection comparisons\t"
		"Heap time\tHeap swaps\tHeap comparisons"
		"Merge time\tMerge swaps\tMerge comparisons";
		//"Quick time\tQuick swaps\tQuick comparisons";
	file << endl;
		
	for (int i = 10; i <= 1000; i++)
	{
		set_size(i);
		create_array(i);
		bubble_sorting();
		insertion_sorting();
		selection_sorting();
		build_maxheap(set, size);
		heapsort(set, size);
		mergesort(set, 0, (size - 1));
		//quicksort(set, 0, (size - 1));

		file << size << "\t" << Bubble_time << "            \t" << Bubble_swap << "                  " << Bubble_comp
			<< "\t\t" << Insertion_time << "\t\t" << Insertion_swap << "\t\t" << Insertion_comp
			<< "\t\t" << Selection_time << "\t\t" << Selection_swap << "\t\t" << Selection_comp
			<< "\t\t" << Heap_time << "\t\t" << Heap_swap << "\t\t" << Heap_comp
			<< "\t\t" << Merge_time << "\t\t" << Merge_copy << "\t\t" << Merge_comp;
		B_Sum = Bubble_comp + Bubble_swap;
		I_Sum = Insertion_comp + Insertion_swap;
		S_Sum = Selection_comp + Selection_swap;
		M_Sum = Merge_comp + Merge_copy;
		H_Sum = Heap_comp + Heap_swap;
		int Sum[] = { B_Sum,I_Sum,S_Sum ,M_Sum ,H_Sum };
		int min;
		min = Sum[0];
		for (int k = 1; k < 5; k++)
		{
			
			if (Sum[k] < min)
				min = Sum[k];
		}
		if (min == B_Sum)
			file << "\tBubble Sort" << endl;

		else if (min == I_Sum)
			file << "\tInsertion Sort" << endl;

		else if (min == S_Sum)
			file << "\tSelection Sort" << endl;

		else if (min == M_Sum)
			file << "\tMerge Sort" << endl;

		else if (min == H_Sum)
			file << "\tHeap Sort" << endl;
			//<< "\t" << Quick_time << "\t" << Quick_swap << "\t" << Quick_comp << endl;
	}

}

void array_::minimum()
{
	ofstream file;
	B_Sum = Bubble_comp + Bubble_swap;
	I_Sum = Insertion_comp + Insertion_swap;
	S_Sum = Selection_comp + Selection_swap;
	M_Sum = Merge_comp + Merge_copy;
	H_Sum = Heap_comp + Heap_swap;
	int Sum[] = { B_Sum,I_Sum,S_Sum ,M_Sum ,H_Sum };
	int min;
	for (int i = 0; i < 5; i++)
	{
		min = Sum[i];
		if (Sum[i] < min)
			min = Sum[i];
	}
	if (min == B_Sum)
		file << "\tBubble Sort" << endl;

	else if (min == I_Sum)
		file << "\tInsertion Sort" << endl;

	else if (min == S_Sum)
		file << "\tSelection Sort" << endl;

	else if (min == M_Sum)
		file << "\tMerge Sort" << endl;

	else if (min == H_Sum)
		file << "\tHeap Sort" << endl;
}

int main()
{
	array_ a;
	a.sort_array();
	return 0;
}
