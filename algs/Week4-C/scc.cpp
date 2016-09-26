#include <fstream>
#include <iostream>
#include <sstream>
#include "scc.h"

using namespace std;

unsigned long leader[SIZE + 1] = {0}; // each node is leader and value is SCC
node vertices[SIZE + 1]; // graph G
node vertices_rev[SIZE + 1]; // reversed

unsigned long processed_nodes = 0;// Tracking number of processed node
unsigned long current_source; // Current processing node

bool FIRST = true;

/*********************** MAIN ************************************/
int main()
{
  for (unsigned long i = 1; i <= SIZE; i++)
    vertices_rev[i].val = i;


  /******** Read data  */
  ifstream infile(FILENAME);

  string line;
  while(getline(infile, line))
    {
      stringstream ss;
      ss << line;

      unsigned long end;
      unsigned long start;
      ss >> start;
      ss >> end;

      vertices[start].edge.push(end);
      vertices_rev[end].edge.push(start);
    }


  /********** Implement algorithm
   * DFS on Grev
   */

  for (unsigned long i = SIZE; i >= 1; i--)
    {
      if (!vertices_rev[i].discovered)
	{
	  DFS(i);
	}
    }


  // Quick sort finishing time on vertices_rev
  sort_time(1,SIZE);

  /*
   * DFS on G
   */

  FIRST = false;
  

  for (unsigned long i = SIZE; i >= 1; i--)
    {
      if (!vertices[vertices_rev[i].val].discovered)
	{
	  // Set leading node of SCC as current_source
	  current_source = vertices_rev[i].val; 
	  // Run DFS
	  DFS(vertices_rev[i].val);
	}
    }
  

  /* Sort Strongly Connected Components */
  sort_scc(1, SIZE);
  
  /* Print */
  cout << endl;
  cout << "Top " << TOP << " largest SCCs in the graph: " << endl;
  for (int i = 1; i <= TOP; i++)
    cout << leader[i] << "  ";
  cout << endl;

}
