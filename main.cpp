#include<utility>
#include<list>
#include<queue>
#include<set>
#include<limits>
#include<iostream>
#include<cstdlib>
#include<ctime>

typedef struct {
  double dist;
  int vertex_id;
} adjVert; 

class Graph 
{ 
	int no_of_vertices; 
	std::list< adjVert > *adj; 

public: 
	Graph(int no_of_v){ 
  	no_of_vertices = no_of_v; 
  	adj = new std::list<adjVert> [no_of_v]; 
  } 

	void AddEdge(int u, int v, double dist){ 
	  adj[u].push_back(adjVert{dist,v}); 
	  adj[v].push_back(adjVert{dist,u}); 
  } 
  
  int NumOfVertices(){
    return no_of_vertices;
  }

  std::list< adjVert > & AdjVertList(int vertex){
    return adj[vertex];
  }
};


void ShortestPath(Graph & g, int src) 
{ 
  auto cmp_dist = [](adjVert left, adjVert right) { return   (left.dist > right.dist); };
	std::priority_queue< adjVert, std::vector <adjVert> , decltype(cmp_dist) > p_queue(cmp_dist); 

	std::vector<double> dist_f_src(g.NumOfVertices(), INT32_MAX); //vertex dist from source  
  std::vector<int> pred_vert(g.NumOfVertices(), -1); //vertes path predecessor.

	// Source vertex insert into prority queue, distance 0 
	p_queue.push(adjVert{0, src}); 
	dist_f_src[src] = 0; 

	while (!p_queue.empty()) 
	{ 
		int u = p_queue.top().vertex_id; //
		p_queue.pop(); 

    for (auto adj_vert : g.AdjVertList(u)) //all adjustence veritices to u 
      { 
          int v = adj_vert.vertex_id; 
          double dist_u_v = adj_vert.dist; 

          if (dist_f_src[v] > dist_f_src[u] + dist_u_v) { 
            dist_f_src[v] = dist_f_src[u] + dist_u_v; 
            pred_vert[v] = u;
            p_queue.push(adjVert{dist_f_src[v], v}); 
          } 
      } 
	} 

  double sum = 0; 
	for (int i = 0; i < g.NumOfVertices(); ++i){
    sum += dist_f_src[i];
  } 
  std::cout << "Average distance :" << sum / g.NumOfVertices() << "\n";
} 


inline double randDist(){
  return 1.0 + 9.0 * (std::rand() / (double) RAND_MAX);
}

inline bool randEdgExist(double p_threshold){
  return (std::rand()/(double) RAND_MAX)<p_threshold ? true : false;
}

void randInitGraph(Graph & g, double p_edge_exist){
  for(int u=0;u<g.NumOfVertices();u++){
    for(int v=0;v<g.NumOfVertices();v++){
      if (randEdgExist(p_edge_exist)){
        g.AddEdge(u,v,randDist());
      }
    }
  }
}

int main() 
{ 
  std::srand(std::time(nullptr));

	Graph g_10(50); 
	Graph g_20(50);
	Graph g_40(50);

  randInitGraph(g_10,0.10);
  randInitGraph(g_20,0.20);
  randInitGraph(g_40,0.40);

	ShortestPath(g_10,0);
	ShortestPath(g_20,0);   
	ShortestPath(g_40,0);

	return 0; 
} 
