#include <fstream> // Read file
#include <sstream>  // Read file
#include <iostream> // Print
#include <time.h> // Random
#include <random> // Random
#include <vector> // Vector
#include <algorithm> // Remove

using namespace std;

struct node {
  int val;
  vector<int> edge;
  int num = 0;
};
 
int cnt = 0;

int main()
{
  // Master array
  vector<node> master;


  /* Get data */
  std::ifstream infile("kargerMinCut.txt");
  //std::ifstream infile("9.txt");
  bool nline;
  
  string line;
  while(getline(infile, line))
    {
      //Get line
      stringstream ss;
      ss << line;			   

      //Get vertex label
      int tmp;   
      ss >> tmp;
      
      //Initlize node with vertex label as value
      node*  n = new node;
      n->val = tmp;
      
      //Scan all adjacent vertices (edge)
      while (ss >> tmp)
	{
	  n->edge.push_back(tmp);
	}
            
      //Add vertex to master array
      master.push_back(*n);
    }


  int min = -1;
  
  //Number of try
  int k = 1000;


  srand(time(NULL));
  while (k-- > 0)
    {
      // Make a clone
      vector<node> nodes = master;

      // random choose edge  
      while (nodes.size() > 2)
	{
	  
	  // get head  - Index of head vertex in array
	  // Choose vertex label in nodes array
	  int n_head = rand() % nodes.size();      	 	  	 
	  int head_label = nodes[n_head].val;

	  // get tail
	  // Choose vertex label in nodes[--head index--].edge

	  int tail_label = nodes[n_head].edge[rand() % nodes[n_head].edge.size()];

	  // Then find the index in master array
	  int n_tail = 0;  // - Index of tail vertex in array	  
	  for (n_tail = 0; n_tail < nodes.size(); n_tail++)
	    if (tail_label == nodes[n_tail].val) break;

	 	  
	  // Remove self-loop
    
	  // Remove tail in head
	  nodes[n_head].edge.erase(remove(nodes[n_head].edge.begin(), nodes[n_head].edge.end(), tail_label), nodes[n_head].edge.end());

	  // Remove head in tail
	  nodes[n_tail].edge.erase(remove(nodes[n_tail].edge.begin(), nodes[n_tail].edge.end(), head_label), nodes[n_tail].edge.end());
    
	  
	  // Combine two vertices into 1
	  // Merge edge of two vertices into tmp array	  
	  nodes[n_head].edge.insert(nodes[n_head].edge.end(), nodes[n_tail].edge.begin(), nodes[n_tail].edge.end());
	  
	  
	 
	      
	  // Change connection in all nodes
	  for (int i = 0; i < nodes.size(); i++)
	    {	             
	      for (int j = 0; j < nodes[i].edge.size(); j++)
		if (nodes[i].edge[j] == tail_label)		  
		  nodes[i].edge[j] = head_label;
	    }// End of for

	  nodes.erase(nodes.begin() + n_tail);
	  
	  
	} // End of while
    
    
      //cout << nodes[0].edge.size() << "  " << nodes[1].edge.size() << endl;
      //getchar();
      
          
      if (min == -1 || nodes[0].edge.size() < min)
	min = nodes[0].edge.size();                

      cout << min << endl;
    }

  cout << min << endl;
}
