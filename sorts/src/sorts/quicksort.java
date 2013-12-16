/*
 * quicksort.java
 *
 *   Created on: Dec 15, 2013
 *       Author: ablink4
 *	Description:	Implementation of quicksort algorithm.  Provides both
 * 					randomized and non-randomized pivot selection.
 */

package sorts;


public class quicksort
{
	private static int ARRAY_SZ = 100000;
	
	private static boolean useRandomizedPivot = false;
	
	/*
	 * @name qsort()
	 * 
	 * @param arr: array to be sorted
	 * @param lo_lim: low array index for this sort partition
	 * @param hi_lim: high array index for this sort partition 
	 * 
	 * @brief This method sorts an array from lo_lim to hi_lim
	 * 			using quicksort.
	 */
	public static void qsort(int[] arr, int lo_lim, int hi_lim)
	{
		int	split_idx = 0;

		if(lo_lim < hi_lim)
		{
			/* 
			 * use boolean flag to determine which type of 
			 * partitioning to use
			 * 
			 */
			if(useRandomizedPivot == true)
			{
				split_idx = randomized_partition(arr, lo_lim, hi_lim);
			}
			else
			{
				split_idx = partition(arr, lo_lim, hi_lim);	
			}
			

			qsort(arr, lo_lim, split_idx - 1);
			qsort(arr, split_idx + 1, hi_lim);
		}	
	}
	
	/*
	 * @name randomized_partition()
	 * 
	 * @param arr: array to be sorted
	 * @param lo_lim: low array index for this sort partition
	 * @param hi_lim: high array index for this sort partition 
	 * 
	 * @brief This method splits the given array segment around
	 * 			a randomly chosen pivot value.
	 */
	private static int randomized_partition(int[] arr, int lo_lim, int hi_lim)
	{
		int new_idx = 0;
		int pivot_idx = 0;
		int temp = 0;

		// pick a random pivot value that is between the limits
		pivot_idx = ((int)Math.random() * (hi_lim - lo_lim + 1)) + lo_lim;

		// swap the chosen pivot into the end of the partition
		// this is done so that the same partition() function
		// that is used in the non-randomized version of quicksort
		// can be used
		temp = arr[pivot_idx];
		arr[pivot_idx] = arr[hi_lim];
		arr[hi_lim] = temp;

		new_idx = partition(arr, lo_lim, hi_lim);

		return(new_idx);
	}
	
	/*
	 * @name partition()
	 * 
	 * @param arr: array to be sorted
	 * @param lo_lim: low array index for this sort partition
	 * @param hi_lim: high array index for this sort partition 
	 * 
	 * @brief This method splits the given array segment around
	 * 			a pivot value that is always the value in the
	 * 			last position of the array segment.
	 */
	private static int partition(int[] arr, int lo_lim, int hi_lim)
	{
		int	i, j = 0;
		int pivot_val = 0;
		int tmp = 0;

		pivot_val = arr[hi_lim];

		i = lo_lim - 1;

		// even though hi_lim is a valid index, it is skipped from the iteration
		// because that element is picked as the pivot.
		for(j=lo_lim; j < hi_lim; j++)
		{
			if(arr[j] <= pivot_val)
			{
				++i;
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}

		tmp = arr[i + 1];
		arr[i + 1] = arr[hi_lim];
		arr[hi_lim] = tmp;

		return(i + 1);
	}
	
	/*
	 * @name main
	 * 
	 * @param args: program arguments
	 * 
	 * @brief main method
	 */
	public static void main(String[] args) 
	{
		int[] A = new int[quicksort.ARRAY_SZ];
	
		
		
		for(int i=0; i < quicksort.ARRAY_SZ; i++)
		{
			// fill array with random values between 1-100
			A[i] = (int)Math.ceil(Math.random() * 100);
			System.out.println(A[i]);
		}
		
		System.out.println();
		
		long start = System.nanoTime();
		
		quicksort.qsort(A, 0, quicksort.ARRAY_SZ - 1);

		// execution time in microseconds
		double executionTime = (double)((System.nanoTime() - start) / 1000.0);
		
		for(int i=0; i < quicksort.ARRAY_SZ; i++)
		{
			System.out.println(A[i]);
		}
		
		System.out.format("%nExecution time: %f microseconds.%n", executionTime);
	}

}
