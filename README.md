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
