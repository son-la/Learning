#ifndef SCC_H
#define SCC_H

#include <stack>
/* 
 * CONFIGURATIONS
 */

#define SIZE 875714
#define FILENAME "SCC.txt"
#define TOP 5

struct node {
  unsigned long val;
  unsigned long leader;
  std::stack<unsigned long> edge;
  bool discovered = false;
  unsigned long finish_time;
};


/* 
 * GLOBAL VARIABLES
 */
extern unsigned long leader[SIZE + 1]; // each node is leader and value is SCC
extern node vertices[SIZE + 1]; // graph G
extern node vertices_rev[SIZE + 1]; // reversed

extern unsigned long processed_nodes;// Tracking number of processed node
extern unsigned long current_source; // Current processing node

extern bool FIRST;

/* Utils function */

// Finishing time sorting
void exch_time(unsigned long n1, unsigned long n2);
void sort_time(unsigned long lo, unsigned long hi);

// SCC sorting
void exch_scc(unsigned long n1, unsigned long n2);
void sort_scc(unsigned long lo, unsigned long hi);

// DFS
void DFS(int cur);

#endif
