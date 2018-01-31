/*
This module implements various classic sorting algorithms and analyzes the perfomance by providing the metrics of
number of data values compied and compared. It covers - bubble sort, insertion sort, counting sort, merge sort and quick sort.
The program takes three files as input parameters - the first one with the list of input integers and the other two to
write the sorted list and output the performance metrics.


PIVOT SELECTION FOR QUICK SORT :
========================================
The quick sort implementation in this programs adapts Hoare's partion scheme where two pointers, one from the start & one from end
traverse inwards into the array until they crossover.

A random pivot selection technique has been used in this program upon several readings and experiments with popular choices. 

The following points are taken into consideration to select a random pivot :
	- When a fixed index pivot is used, in the event of an already sorted array, the time complexity becomes O(N^2), which is undesirable.
	- A randomly chosen pivot gives a better and desired complexity in such scenarios.
	- Also, Random pivot provides better behaviour in cases when the input contains mostly repeated numbers. 
	- Although "median-of-3", another popular pivot selction technique, provides a relatively better complexity over random pivot
		, a trade has to between complexity and number of data swaps.

Analysis:
For the following input (almost sorted),
6 -2 -1 0 1 2 3 4 5 -3 

First element as pivot: 	Quick Sort: 63 comparisons, 36 copies
Random element as pivot: 	Quick Sort: 31 comparisons, 33 copies

*/


#include <stdio.h>
#include<stdlib.h>
#include<time.h>

/*
bubble_sort method takes three inputs - array 'a', number of elements to be sorted 'n' and the file pointer 'evaluation_file'.
upon completion of the sorting process, the performance metrics i.e, # of data copies and # of data comparisons are written to evalution_file.
Finally, the pointer to the sorted array is returned.
*/
int * bubble_sort(int a[], int n, FILE * evaluation_file){
	int i = 0, j=0 , num_copies = 0, num_comp = 0, tmp;

	for( ; i< n; i++)
	{
		for (j = n - 1; j >= i + 1; j--)
		{
			num_comp++;				//++ for data value comparison 
			if (a[j] < a[j - 1])
			{
				num_copies += 3;	//+3 copies for the following swap of data values
				tmp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = tmp;
      		}
  		}
	}
	//print the # of data copies and # of data comparisons to evaluation file
	fprintf(evaluation_file, "Bubble Sort: %d comparisons, %d copies\n",num_comp,num_copies );
	return a;	//return starting index of sorted array
}


/*
insertion_sort method takes three inputs - array 'a', number of elements to be sorted 'n' and the file pointer 'evaluation_file'.
upon completion of the sorting process, the performance metrics i.e, # of data copies and # of data comparisons are written to evalution_file.
Finally, the pointer to the sorted array is returned.
*/
int * insertion_sort(int a[], int n, FILE * evaluation_file){
	int i = 0, j=0 , num_copies = 0, num_comp = 0, tmp;

	for (i = 1; i < n; i++)
	{
		tmp = a[i];
		num_copies++;				//++ for data value copy 

	    j = i-1;
	    num_comp++;					//++ for data value comparison 
	    while (j >= 0 && tmp < a[j])
	    {
	    	num_comp++;				//++ for data value comparison 
			a[j + 1] = a[j];
			num_copies++;			//++ for data value copy
			j--;
	    }
	    
	    a[j + 1] = tmp;
	    num_copies++;				//++ for data value copy 

	}
	//print the # of data copies and # of data comparisons to evaluation file
	fprintf(evaluation_file, "Insertion Sort: %d comparisons, %d copies\n",num_comp,num_copies );
	return a;	//return starting index of sorted array
}


/*
counting_sort method takes three inputs - array 'a', number of elements to be sorted 'n' and the file pointer 'evaluation_file'.
upon completion of the sorting process, the performance metrics i.e, # of data copies and # of data comparisons are written to evalution_file.
Finally, the pointer to the sorted array is returned.

It is to be noted that in this algorithm, there will be no data comparions at all. Therefore num_comp will always be 0.
*/
int * counting_sort(int a[], int n, int small, int large, int c[], FILE * evaluation_file){

	//create array b to get the count of each value in the list
	int  b[large-small+1], num_copies = 0, num_comp = 0, i;
    
    for(i = 0; i< large-small+1; i++){
        b[i] =0;			//initialize each count to 0
    }
    
    for(i =0; i < n ; i++){
        b[a[i]-small] += 1;	//increment count of occurence of the value
    }
    
    for( i = 1; i < large-small+1 ; i++){
        b[i] += b[i-1];		//add the counts to get the order of values
    }

    for(i = 0; i< n ;i++){
        c[b[a[i]-small]-1] = a[i];	//place the data value at the right index in sorted order
        num_copies++;				//++ for data value copy 
        b[a[i]-small] += -1;
    }
    //print the # of data copies and # of data comparisons to evaluation file
    fprintf(evaluation_file, "Counting Sort: %d comparisons, %d copies\n",num_comp,num_copies );
	return c;	//return starting index of sorted output array
}


/*
merge method takes five inputs - array 'a' that has to be sorted; 'start' and 'end' indices of the array and
integer pointers to # of data copies and # of data comparisons. It copies the data values from two sorted arrays
in a sorted manner to the original array 'a'.
*/
void merge(int a[],int start, int middle, int end, int * num_copies, int * num_comp){

	int n1 = middle-start+1, n2 = end-middle;
	int l[n1], r[n2], i, j = 0, k = 0;

	//copy all elements up until left of middle to left array l
	for(i =0 ; i< n1; i++){
		l[i] = a[start+i];
		(*num_copies)++;		//++ for data value copy
	}
	//copy all elements up after middle to right array r
	for(i =0 ; i< n2; i++){
		r[i] = a[middle+1+i];
		(*num_copies)++;		//++ for data value copy
	}

	i = 0, k= start;

	while(i<n1 && j<n2){
		(*num_comp)++;			//++ for data value comparison for the if else condition
		if(l[i]<=r[j]){
			a[k] = l[i]; i++;
			(*num_copies)++;	//++ for data value copy
		}
		else{
			a[k] = r[j]; j++;
			(*num_copies)++;	//++ for data value copy
		}
		k++;
	}
	while(i < n1){				//for the case where n1 is greater than n2 --> copy the remaining elements in order
		a[k] = l[i]; i++; k++;
		(*num_copies)++;		//++ for data value copy
	}
	while(j < n2){				//for the case where n2 is greater than n1 --> copy the remaining elements in order
		a[k] = r[j]; j++; k++;
		(*num_copies)++;		//++ for data value copy
	}
}


/*
merge_sort method takes five inputs - array 'a' that has to be sorted; 'start' and 'end' indices of the array and
integer pointers to # of data copies and # of data comparisons.
The method then recursively calls itself followed by calls to merge method
upon completion of the sorting process, the pointer to the sorted array is returned.
*/
int * merge_sort(int a[],int start, int end, int * num_copies, int * num_comp){
	int middle = (start+end)/2;  //index of the middle element
	if(start<end){				 //condition to break recursion
		merge_sort (a, start, middle, num_copies, num_comp);	//recursive call to all elements from start to middle
      	merge_sort (a, middle + 1, end,num_copies, num_comp);	//recursive call to all elements after middle to end
      	merge (a, start, middle, end,num_copies, num_comp);		//merge call to arrange the elements in order
	}
	return a;					 //return starting index of sorted array
}


/*
partition method takes five inputs - array 'a' that has to be sorted; 'start' and 'end' indices of the array and
integer pointers to # of data copies and # of data comparisons. It rearranges the data values around the choosen pivot.
Then, it returns the index of the pivot value in the rearranged array.
*/
int partition(int a[], int start, int end, int * num_copies, int * num_comp,int pivot_pos){
    int pivot = a[pivot_pos]; //a[start];
    a[pivot_pos] = a[start];
    a[start] = pivot;
    (*num_copies) += 3;			//3 copies for data value copy into pivot and swap
    int i = start+1,j = end, temp;
    
    while(i<=j){
        while(a[i]<=pivot && i<=j){
        	i++; (*num_comp)++;	//++ for data value comparion in while condition
        }
        (*num_comp)++;			//++ for failed while comparison
       while(a[j]>pivot && i<=j){
       		j--; (*num_comp)++;	//++ for data value comparion in while condition
       	}
       	(*num_comp)++; 			//++ for failed while comparison
        if(i<=j){
        	temp = a[i];
       		a[i] = a[j];
        	a[j] = temp;
        	(*num_copies) += 3;	//+3 copies for the swap of data values
        }
    }

    temp = a[start];
    a[start] = a[j];
    a[j] = temp;
    (*num_copies) += 3;	//+3 copies for the swap of data values
    return j;			//return the index of pivot in the rearranged array
}


/*
quick_sort method takes five inputs - array 'a' that has to be sorted; 'start' and 'end' indices of the array and
integer pointers to # of data copies and # of data comparisons.
The method calls the partition method then recursively calls itself.
Upon completion of the sorting process, the pointer to the sorted array is returned.
*/
int * quick_sort(int a[], int start, int end, int * num_copies, int * num_comp){
    int p; 				//pivot partition index
    if(start<end){		//condition to break recursion
    	int pivot_pos = start+ rand()%(end-start); //select random pivot
        p = partition(a,start,end,num_copies,num_comp,pivot_pos); //index of pivot after array rearrangement
        quick_sort(a,start,p-1,num_copies,num_comp);	//recursive call to elements left of pivot
        quick_sort(a,p+1,end,num_copies,num_comp);		//recurisve call to elements right of pivot
    }
    return a;			//return starting index of sorted array
    
}



/*
The main method that runs the program
*/
int main(int argc, char const *argv[])
{
	FILE *input_file = fopen(argv[1],"r"); 			//input file read as command line argument 
	FILE * output_file = fopen(argv[2],"w"); 		//output file read as command line argument - contains the sorted list
	FILE * evaluation_file = fopen(argv[3],"w"); 	//output file read as command line argument - contains the performance metrics

	int n,small,large, inp, *bsort, *isort, *csort, *msort, *qsort;
	
	fscanf(input_file,"%d", &n); 		//# of integers to sort
	fscanf(input_file,"%d", &small);	//smallest value in the list 
	fscanf(input_file,"%d", &large);	//largest value in the list

	srand(time(0));		//seed input for random generator which will be later used in quick sort

	//create arrays to store the input data for each sorting algorthim including the additional output array for counting sort
	int b_sort_array[n], i_sort_array[n], c_sort_array_in[n],c_sort_array_out[n], m_sort_array[n], q_sort_array[n], i=0;

	while(i<n){
		fscanf(input_file,"%d", &inp);
		//copy input number to each of the arrays
		b_sort_array[i] = inp;
		i_sort_array[i] = inp;
		c_sort_array_in[i] = inp;
		m_sort_array[i] = inp;
		q_sort_array[i] = inp;
		i++;
	}

	//bubble sort call
	bsort = bubble_sort(b_sort_array,n,evaluation_file);

	//insertion sort call
	isort = insertion_sort(i_sort_array,n,evaluation_file);

	//counting sort call
	csort = counting_sort(c_sort_array_in,n,small,large,c_sort_array_out,evaluation_file);

	//merge sort call
	//initialize counters for comparions and copies to 0 for merege sort
	int num_copies = 0, num_comp = 0;		
	msort = merge_sort(m_sort_array,0,n-1,&num_copies,&num_comp);
	//print the # of data copies and # of data comparisons to evaluation file
	fprintf(evaluation_file, "Merge Sort: %d comparisons, %d copies\n",num_comp,num_copies );

	//quick sort call
	//re-initialize counters for comparions and copies to 0 quick sort
	num_copies = 0, num_comp = 0;			
	qsort = quick_sort(q_sort_array,0,n-1,&num_copies,&num_comp);
	//print the # of data copies and # of data comparisons to evaluation file
	fprintf(evaluation_file, "Quick Sort: %d comparisons, %d copies\n",num_comp,num_copies );


	// fprintf(output_file, "%s","bubble insertion counting merge quick\n");

	for(i=0; i<n; i++){
		//print the values in sorted order to the output file
		fprintf(output_file, "%3d\t%3d\t%3d\t%3d\t%3d\n", *(bsort + i), *(isort + i), *(csort+i), *(msort+i), *(qsort+i));
	}

	fclose(evaluation_file); //close the output file
	fclose(output_file); //close the output file
	fclose(input_file);  //close the input file

	return 0;
}