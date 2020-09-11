#include<utility>
#include<list>
#include<queue>
#pragma once



// iPair ==> Integer Pair 
typedef std::pair<int, int> iPair; 

class Graph 
{ 
	int V; 
	std::list< std::pair<int, int> > *adj; 

public: 
	Graph(int V);

	void addEdge(int u, int v, int w);  
  int number_of_vertices();
  std::list<iPair> & adj_vertices(int vertex);

}; 

// Allocates memory for adjacency list 
Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new std::list<iPair> [V]; 
} 

int Graph::number_of_vertices(){
  return V;
}

void Graph::addEdge(int u, int v, int w) 
{ 
	adj[u].push_back(std::make_pair(v, w)); 
	adj[v].push_back(std::make_pair(u, w)); 
} 

std::list<iPair> & Graph::adj_vertices(int vertex){
  return adj[vertex];
}

