/*

The goal of this problem is to implement the "Median Maintenance" algorithm (covered in the Week 5 lecture on heap applications). The text file contains a list of the integers from 1 to 10000 in unsorted order; you should treat this as a stream of numbers, arriving one by one. Letting xi denote the ith number of the file, the kth median mk is defined as the median of the numbers x1,…,xk. (So, if k is odd, then mk is ((k+1)/2)th smallest number among x1,…,xk; if k is even, then mk is the (k/2)th smallest number among x1,…,xk.)

In the box below you should type the sum of these 10000 medians, modulo 10000 (i.e., only the last 4 digits). That is, you should compute (m1+m2+m3+⋯+m10000)mod10000.

 */


#include <set> 
#include <fstream>
#include <sstream>
#include <iostream>

#define FILENAME "Median.txt"

using namespace std;


int main()
{
  multiset<int> set;

  // Ref to median
  multiset<int>::iterator med;  


  ifstream infile(FILENAME);

  int sum = 0;

  string line;
  while (getline(infile, line))
    {
      stringstream ss;
      ss << line;

      int num;
      ss >> num;
      
      // Ref to recent insert
      multiset<int>::iterator it = set.insert(num);
      
      // Size of set
      int size = set.size();
       
      if (size == 1)
	med = it;
      else if (size % 2 == 0)
	{
	  // To the left, med decrease
	  if (*it < *med)
	    med = --med;
	  // To the right, med unchange   	   
	}
      else
	{
	  // To the right, med increase
	  if (*it > *med || *it == *med)
	    med = ++med;	  
	  // To the left, med unchange
	}
      
      sum += *med;
    }
  
  cout << sum%10000 << endl;


}

