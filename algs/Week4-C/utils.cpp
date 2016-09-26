#include "scc.h"

/* Finishing time sort */
void exch_time(unsigned long n1, unsigned long n2)
{
  // Swap vertices[i] with place finish_time
  node tmp = vertices_rev[n1];
  unsigned long time = vertices_rev[n1].finish_time;
  vertices_rev[n1] = vertices_rev[n2];
  vertices_rev[n2] = tmp;
}

void sort_time(unsigned long lo, unsigned long hi)
{
 
  if ( hi <= lo) return;

  unsigned long lt = lo, gt = hi;
  node pv = vertices_rev[lo];

  unsigned long i = lo;
  while (i <= gt)
    {
      if (vertices_rev[i].finish_time < pv.finish_time)
	exch_time(lt++, i++);
      else if (vertices_rev[i].finish_time > pv.finish_time)
	exch_time(i, gt--);
      else i++;
    }

  sort_time(lo, lt-1);
  sort_time(gt+1, hi);
}

/****** SCC sort */
void exch_scc(unsigned long n1, unsigned long n2)
{
  // Swap vertices[i] with place finish_time
  unsigned long tmp = leader[n1];
  leader[n1] = leader[n2];
  leader[n2] = tmp;
}

void sort_scc(unsigned long lo, unsigned long hi)
{
 
  if ( hi <= lo) return;

  unsigned long lt = lo, gt = hi;
  unsigned long pv = leader[lo];

  unsigned long i = lo;
  while (i <= gt)
    {
      if (leader[i] > pv)
	exch_scc(lt++, i++);
      else if (leader[i] < pv)
	exch_scc(i, gt--);
      else i++;
    }

  sort_scc(lo, lt-1);
  sort_scc(gt+1, hi);
}

/* DFS */
void DFS(int cur)
{
  if (FIRST) // Run on Grev
    {
      // Mark as explored
      vertices_rev[cur].discovered = true;
      
      // DFS all arcs
      while (vertices_rev[cur].edge.size() > 0)
	{
	  unsigned long next_proc = vertices_rev[cur].edge.top(); // LIFO
	  vertices_rev[cur].edge.pop(); // LIFO
	  if (!vertices_rev[next_proc].discovered)
	    DFS(next_proc);
	}

      processed_nodes++;
      
       // Set finishing time
      vertices_rev[cur].finish_time = processed_nodes;
      vertices[cur].finish_time = processed_nodes; 
    }
  else // Run on G
    {
      // Mark as explored
      vertices[cur].discovered = true;

      // Increase SCC of leading node
      leader[current_source]++;
      
      // DFS all arcs
      while (vertices[cur].edge.size() > 0)
	{
	  unsigned long next_proc = vertices[cur].edge.top(); // LIFO
	  vertices[cur].edge.pop(); // LIFO

	  if (!vertices[next_proc].discovered)
	    DFS(next_proc);
	}
    }

}
