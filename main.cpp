#include<utility>
#include<list>
#include<queue>
#include<set>
#include<limits>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iterator>
#include<fstream>
#include<vector>

//Structure used in Graph class for representation of adjacency vertex together with distance form source
typedef struct {
  double dist;
  int vertex_id;
} adjVert; 

//Class that represent graph in the form of adjacency list
class Graph 
{ 
	  int no_of_vertices; 
	  std::list< adjVert > *adj; 

    int Next(std::istream_iterator<int> &ptr)
    {
      int i = *ptr;
      ptr++;
      return i;
    }

public:
    //Class initiatlization, required param: number of vertices to be used
    //For simplicity adj. list is not dynamicly resized.
  	Graph(int no_of_v){ 
  	  no_of_vertices = no_of_v;
    	adj = new std::list<adjVert> [no_of_v]; 
    } 

    //Intitailization form input file provided for the excercise
    Graph(std::string s){
        std::ifstream data_file(s);
        std::istream_iterator<int> start(data_file), end;

        int i,j,cost;

        no_of_vertices = Next(start);
    	  adj = new std::list<adjVert> [no_of_vertices]; 

        while(start != end){
          i = Next(start);
          j = Next(start);
          cost = Next(start);
          AddEdge(i,j,cost);
        }
    }
    
    //Add edge between selected verices with specifed distance
  	void AddEdge(int u, int v, double dist){ 
	    adj[u].push_back(adjVert{dist,v}); 
	    adj[v].push_back(adjVert{dist,u}); 
    } 
  
    int NumOfVertices(){
      return no_of_vertices;
    }

    //List of all adjacency vertices to selected verrtex
    std::list< adjVert > & AdjVertList(int vertex){
      return adj[vertex];
    }
};

//Class claculates minimum spanning tree to all provided vertices from sources node.
//https://www.thetopsites.net/article/51605961.shtml
class MinimumSpanningTree {

   std::vector<double> * dist_f_src;
   std::vector<int> * pred_vert;
   Graph & g;

public:
  MinimumSpanningTree(Graph & g) : g(g)
  { 
    dist_f_src = new std::vector<double> (g.NumOfVertices(), INT32_MAX); //vertex dist from source  
    pred_vert  = new std::vector<int> (g.NumOfVertices(), -1);           //vertes path predecessor.
  }

  ~MinimumSpanningTree(){
    delete dist_f_src;
    delete pred_vert; 
  }

  //Calcluates shortest paths for all vertices from source. 
  MinimumSpanningTree & source(int src) 
  { 
    auto cmp_dist = [](adjVert left, adjVert right) { return   (left.dist > right.dist); };
	  std::priority_queue< adjVert, std::vector <adjVert> , decltype(cmp_dist) > p_queue(cmp_dist); 

	  p_queue.push(adjVert{0, src}); // Source vertex insert into prority queue, distance 0 
	  (*dist_f_src)[src] = 0; 

	  while (!p_queue.empty()) 
	  { 
		  int u = p_queue.top().vertex_id; //
		  p_queue.pop(); 

      for (auto adj_vert : g.AdjVertList(u)) //all adjustence veritices to u 
        { 
          int v = adj_vert.vertex_id; 
          double dist_u_v = adj_vert.dist; 

          if ((*dist_f_src)[v] > (*dist_f_src)[u] + dist_u_v) { 
            (*dist_f_src)[v] = (*dist_f_src)[u] + dist_u_v; 
            (*pred_vert)[v] = u;
            p_queue.push(adjVert{(*dist_f_src)[v], v}); 
          } 
        } 
	  } 
  return *this; //this allow for command chaning eg: cout << a.source(0)
} 

  friend std::ostream& operator<<(std::ostream& os,  const MinimumSpanningTree &sp); //friend funciton has access to private variables
};

std::ostream& operator<<(std::ostream& out, const MinimumSpanningTree &sp){
  double sum = 0; 
	for (int i = 0; i < sp.g.NumOfVertices(); ++i){
    sum += (*sp.dist_f_src)[i];
  } 
  out << "average distance :" << sum / sp.g.NumOfVertices() << "\n";
  return out;
}

int main() 
{ 
  Graph g_span_tree("input.txt");

	auto a = MinimumSpanningTree(g_span_tree);
  std::cout << "Graph  \n" << a.source(0);

	return 0; 
} 