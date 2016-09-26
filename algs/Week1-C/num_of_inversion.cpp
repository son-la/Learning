#include <fstream>
#include <iostream>

#define SIZE 100000

// Merge two sorted sub array and count inversion
int merge(int* a, int* array, int lo, int hi, int mid)
{
  int inverse = 0;

  for (int k=lo; k <= hi; k++)
    {
      array[k] = *(a+k);
    }
  int i = lo;
  int j = mid + 1;
  
  for (int k = lo; k <= hi; k++)
    {
      if (i > mid) a[k] = *(array + j++);
      else if (j > hi) a[k] = *(array + i++);
      else if (array[i] < array[j]) a[k] = *(array + i++);
      else
	{
	  inverse += (mid - i + 1);
	  a[k] = *(array + j++);
	}
    }
  
  return inverse;
}


// Do merge sort
void sort(int* a, int* array, int lo, int hi)
{
  if (hi <= lo)
    return;
  
  int mid = lo + (hi-lo)/2;

  sort(a, array, lo, mid);
  sort(a, array, mid+1, hi);

  merge(a, array, lo, hi, mid);
}


// Count split

unsigned long count_split(int* a, int* array, int lo, int hi, int mid)
{  
  sort(a, array, lo, mid);
  sort(a, array, mid+1, hi);

  return merge(a, array, lo, hi, mid);
}

// funcion
unsigned long count (int* a, int* array, int lo, int hi)
{
  if (hi <= lo)
    return 0;
  
  int mid = lo + (hi-lo)/2;

  return count(a, array, lo, mid) + count(a, array, mid+1, hi) + count_split(a, array, lo, hi, mid);
}


int main(void)
{
  std::ifstream infile("IntegerArray.txt");
  
  int temp[SIZE];
  int array[SIZE];
  for (int i = 0; i < SIZE; i++)
    {
      infile >> temp[i];
      array[i] = temp[i];
    }
  
  std::cout << cout << "Number of inversion: " << endl;
  std::cout << count(temp, array, 0, SIZE-1) << std::endl;
}
