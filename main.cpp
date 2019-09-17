#include <iostream>
#include <string>
#include "Graph.h"
#include "Ant.h"
#include "utils.h"

int main()
{

    //graph init
    const int n = 280;
    Graph graph;
    for(int i =0; i<n; ++i)
    {
        int k, u,v;
        std::cin >> k >> u >> v;
        graph.addVertex(PT(u,v)); //initial Vertex
    }
    for(int i =0; i<n; ++i)
    {
        for (int j = 0; j < n; ++j)
            graph.addEdge(i, j); //connect every vertex with edges

        //init pheromones with 1
        graph.vertexes[i].probablitySum(1,1);
        graph.vertexes[i].updatePheromone(1,1,0,0);
    }
    //end graph init

    //ants...
    double pheromones = 0;
    double minDist = INFINITY;
    std::vector<std::pair<int,int>> bestPath(n+1);
    for(int k = 0; k<1000; ++k) // k = number of ants
    {
        //make tour with k ant
        double dist=0;
        Ant ant(0,graph.vertexes[0],1,5);
        while(ant.path.size() < n)
            dist += ant.move(graph.vertexes[ant.path.back().second]);
        dist += graph.vertexes[ant.path.back().second].edges[0].d;
        ant.path.push_back({ant.path.back().second,0});
        //end tour
        if(dist < minDist) //check if that solution is better
        {
            minDist = dist;
            std::copy(ant.path.begin(),ant.path.end(), bestPath.begin());
        }
        //update pheromones
        pheromones += 1/dist;
        for(int i =0; i<n; ++i)
            graph.vertexes[i].updatePheromone(1,5,pheromones,0.1);
    }

    //Print solution
    for(int i=0; i<n; ++i)
        std::cout << bestPath[i].second << " - " <<bestPath[i+1].second << std::endl;
    std::cout << "Distance: " << minDist << std::endl;
    return 0;
}