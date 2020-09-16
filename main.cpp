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
#include<set>

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
//Implemented Prim algorithm
class MinimumSpanningTree {

   std::vector<double> * dist;
   std::vector<int> * pred_vert;
   Graph & g;

public:
  MinimumSpanningTree(Graph & g) : g(g)
  { 
    dist = new std::vector<double> (g.NumOfVertices(), INT32_MAX); //vertex dist from predecessor  
    pred_vert  = new std::vector<int> (g.NumOfVertices(), -1); //vertes path predecessor.
  }

  ~MinimumSpanningTree(){
    delete dist;
    delete pred_vert; 
  }

  //Calcluates MST for all vertices from source. 
  MinimumSpanningTree & mst() 
  { 
    auto cmp_dist = [](adjVert left, adjVert right) { return   (left.dist > right.dist); };
	  std::priority_queue< adjVert, std::vector <adjVert> , decltype(cmp_dist) > p_queue(cmp_dist); 
    std::set<int> closed_set;

	  p_queue.push(adjVert{0, 0}); // First vertex (by default 0) insert into prority queue, distance 0 
	  (*dist)[0] = 0; 

	  while (!p_queue.empty()) 
	  { 
		  int u = p_queue.top().vertex_id; //
		  p_queue.pop(); 
      closed_set. insert(u);

      for (auto adj_vert : g.AdjVertList(u)) //all adjustence veritices to u 
        { 
          int v = adj_vert.vertex_id; 
          double dist_u_v = adj_vert.dist; 

          if(closed_set.count(v)) continue; //alredy processed vertex, to be skipped. 

          if ((*dist)[v] > dist_u_v) { 
            (*dist)[v] = dist_u_v; 
            (*pred_vert)[v] = u;
            p_queue.push(adjVert{(*dist)[v], v}); 
          } 
        } 
	  } 
  return *this; //this allow for command chaning eg: cout << a.source(0)
} 

  friend std::ostream& operator<<(std::ostream& os,  const MinimumSpanningTree &mst); //friend funciton has access to private variables
};

//Prints MST
std::ostream& operator<<(std::ostream& out, const MinimumSpanningTree &mst){
	for (int i = 0; i < mst.g.NumOfVertices(); ++i){
    out << "vert :" << i << " pred= " << (*mst.pred_vert)[i] << "\n";
  } 
  
  return out;
}

int main() 
{ 
  Graph g_span_tree("input.txt");

	auto a = MinimumSpanningTree(g_span_tree);
  std::cout << "MST:  \n" << a.mst();

	return 0; 
} 