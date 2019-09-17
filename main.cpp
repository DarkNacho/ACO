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
        graph.addVertex(PT(u,v));
    }
    for(int i =0; i<n; ++i)
    {
        for (int j = 0; j < n; ++j)
            graph.addEdge(i, j);

        //init pheromones with 1
        graph.vertexes[i].probablitySum(1,1);
        graph.vertexes[i].updatePheromone(1,1,0,0);
    }
    //end graph init

    //ants...
    double pheromones = 0;
    double minDist = INFINITY;
    std::vector<std::pair<int,int>> bestPath(n+1);
    for(int k = 0; k<500; ++k)
    {
        double dist;
        Ant ant(0,graph.vertexes[0],5,5);
        while(ant.path.size() < n)
            dist += ant.move(graph.vertexes[ant.path.back().second]);
        dist += graph.vertexes[ant.path.back().second].edges[0].d;
        ant.path.push_back({ant.path.back().second,0});
        if(dist < minDist)
        {
            minDist = dist;
            std::copy(ant.path.begin(),ant.path.end(), bestPath.begin());
        }
        pheromones += 1/dist;
    }
    for(int i =0; i<n; ++i)
       graph.vertexes[i].updatePheromone(5,5,pheromones,0.1);


    for(int i=0; i<n; ++i)
        std::cout << bestPath[i].second << " - " <<bestPath[i+1].second << std::endl;
    std::cout << "dist: " << minDist << std::endl;
    //std::cout << graph.tostring() << std::endl;
    return 0;
}