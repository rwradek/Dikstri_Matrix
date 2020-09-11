#include "Graph.h"
#include<iostream>

#define INF 0x3f3f3f3f 

// Prints shortest paths from src to all other vertices 
void shortestPath(Graph g, int src) 
{ 
	std::priority_queue< iPair, std::vector <iPair> , std::greater<iPair> > pq; 

	//vector for distances and initialize all as infinite (INF) 
	std::vector<int> dist(g.number_of_vertices(), INF); 
  std::vector<int> pred(g.number_of_vertices(), -1);

	// Insert source itself in priority queue and initialize distance as 0. 
	pq.push(std::make_pair(0, src)); 
	dist[src] = 0; 

	/* Looping till priority queue becomes empty (or all 
	distances are not finalized) */
	while (!pq.empty()) 
	{ 
		// The first vertex in pair is the minimum distance vertex 
		int u = pq.top().second; 
    std::cout << "pop:d= "<< pq.top().first 
              << " v= " << pq.top().second << std::endl;
		pq.pop(); 

	 // Get all adjacent of u.  
    for (auto adj_edge : g.adj_vertices(u)) 
      { 
          int v = adj_edge.first; 
          int weight = adj_edge.second; 
  
          // If there is shorted path to v through u. 
          if (dist[v] > dist[u] + weight) 
          { 
             // Updating distance of v 
             dist[v] = dist[u] + weight; 
             pred[v] = u;
             pq.push(std::make_pair(dist[v], v)); 
             std::cout << "  push:d= " << dist[v] 
                       << " v= " << v <<std::endl;
           } 
      } 
	} 

  std::cout << "Vertex Distance from Source\n"; 
	for (int i = 0; i < g.number_of_vertices(); ++i){
    std::cout << i << " pred= "<< pred[i]  << " dist= "<< dist[i] << std::endl;
  } 

} 


// Driver program to test methods of graph class 
int main() 
{ 
	// create the graph given in above fugure 
	int V = 9; 
	Graph g(V); 

	// making above shown graph 
	g.addEdge(0, 1, 4); 
	g.addEdge(0, 7, 8); 
	g.addEdge(1, 2, 8); 
	g.addEdge(1, 7, 11); 
	g.addEdge(2, 3, 7); 
	g.addEdge(2, 8, 2); 
	g.addEdge(2, 5, 4); 
	g.addEdge(3, 4, 9); 
	g.addEdge(3, 5, 14); 
	g.addEdge(4, 5, 10); 
	g.addEdge(5, 6, 2); 
	g.addEdge(6, 7, 1); 
	g.addEdge(6, 8, 6); 
	g.addEdge(7, 8, 7); 

	shortestPath(g,0); 

	return 0; 
} 
