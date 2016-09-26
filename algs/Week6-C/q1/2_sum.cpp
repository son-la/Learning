#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define INV 10000
#define FILENAME "algo1_programming_prob_2sum.txt"

int main()
{

  map<long, vector<long> > my_map;

  ifstream infile(FILENAME);

  string line;
  while (getline(infile, line))
    {
      stringstream ss;
      ss << line;

      long num;
      ss >> num;
      
      // Read data to hash table with key = num / 10000
      if (my_map.find(num/INV) == my_map.end())
	{
	  vector<long> tmp;
	  tmp.push_back(num);
	  my_map.insert(pair<long, vector<long> >(num/INV, tmp));
	}
      else
	{
	  vector<long> tmp = my_map.find(num/INV)->second;	  
	  if (find(tmp.begin(), tmp.end(), num) == tmp.end())
	    my_map.find(num/INV)->second.push_back(num);
	}

    }


 

  long cnt = 0;
  vector<long> target;
  for ( map<long,vector<long> >::iterator it = my_map.begin(); it != my_map.end(); ++it)
    {
      for (long j = 0; j < it->second.size(); j++)
	{
	  long a = -INV - it->second[j]; // Lower bound
	  long b = INV - it->second[j]; // Upper bound 




	  // find  a < x < b	  
	  // -1 and +1 to guarentee the round of division
	  for (long i = a/INV - 1; i <= b/INV + 1; i++)
	    {	      
	      // find i, if found return vector
	      if (my_map.find(i) != my_map.end())
		{
		  for (long l = 0; l < my_map.find(i)->second.size(); l++)
		    {

		      long sum = it->second[j] + my_map.find(i)->second[l];
		      // Avoid duplicate
		      if (it->second[j] > my_map.find(i)->second[l] && sum >= -INV && sum <= INV)
		      {
			// Check target exists
			if (find(target.begin(), target.end(), sum) == target.end())
			  {
			    target.push_back(sum);
			    cnt = cnt + 1;
			  }
		      }
		    }
		}
	    }	  
	}
     
    }
  
  cout << cnt << endl;

  
}
