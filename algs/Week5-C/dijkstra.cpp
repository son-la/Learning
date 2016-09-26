#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>

#define SIZE 200
#define FILENAME "dijkstraData.txt"
#define SOURCE 1

using namespace std;

struct head{
  int val;
  int cost;
};

bool edge_sort(head const& a, head const& b)
{
  return a.cost >= b.cost;
}

vector<head> vertices[SIZE+1];

int main()
{
  ifstream infile(FILENAME);

  string line; 
  while(getline(infile, line))
    {
      stringstream ssLine;
      ssLine << line;
      
      // Index vertex (Tail)
      int index;
      ssLine >> index;
      
      // Destination (Head) and Cost String
      string headNcost;     
     
      // Extract head and cost
      while(ssLine >> headNcost)
      	{	
     
	  stringstream ssHead;
	  ssHead << headNcost;
	  
	  //Initlaize struct
	  head tHead = {};
	  string val;
	  
	  // Get head
	  getline(ssHead, val, ',');
	  tHead.val = atoi(val.c_str());
	  
	  // Get cost
	  getline(ssHead, val, ',');
	  tHead.cost = atoi(val.c_str());
	  
	  // Vector of heads
	  vertices[index].push_back(tHead);
	 
      	}
    }
  
  
  // Initliaze set of processed nodes
  int source[1] = {SOURCE};
  set<int> processed(&source[0], &source[0]+1);
  
  // Initlaize of shortest path for each vertex
  int shortest_paths[SIZE+1];
  
  // Assume not to have connection
  for (int i = 0; i <= SIZE; i++)
    shortest_paths[i] = 1000000;

  // Source to source = 0
  shortest_paths[SOURCE] = 0;
  
  
  // Iterator of set
  set<int>::iterator it;

  // Going through all procesed nodes, compute available path cost and 
  // process
  while(processed.size() < SIZE)
    {
      
      int min_cost = -1;
      int n_vertex = -1;

      // Check processed vertex
      for (it = processed.begin(); it != processed.end(); ++it)
	{
	  // Check heads
	  for (int j = 0; j < vertices[*it].size(); j++)
	    {
	      head h = vertices[*it][j];
	      
	      // Check processed ?
	      if (processed.find(h.val) != processed.end())
		continue;
	      else
		{
		  // Not processed
		  if (n_vertex == -1 || (shortest_paths[*it] + h.cost) < min_cost)
		    {
		      n_vertex = h.val;
		      min_cost = shortest_paths[*it] + h.cost;
		    }		   	  
		}
	    }	  
	}
      if (n_vertex != -1)
	{
	  // Add node to processed
	  shortest_paths[n_vertex] = min_cost;
	  processed.insert(n_vertex);
	}	
      
      
    }
  
  cout << endl;
  cout << "Path from " << SOURCE << " to: " << endl;
  for (int i = 1; i <= SIZE; i++)
    {
      cout << setw(4) << i << ": " << setw(5) << shortest_paths[i] << "\t";
      if (i%4 == 0)
	cout << endl;
    }
  cout << endl;
  
}
