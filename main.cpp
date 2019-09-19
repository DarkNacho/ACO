#include <iostream>
#include <string>
#include "Graph.h"
#include "Ant.h"
#include "utils.h"
#define alpha 1
#define beta 5
#define rho 0.2  //evaporation rate

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
        graph.vertexes[i].setPheromones(1);  //init pheromones
    }
    //end graph init

    //ants...
    double minDist = INFINITY;
    std::vector<std::pair<int,int>> bestPath(n+1);
    for(int i =0; i<36; ++i) //iterations
    {
        double pheromones = 0;
        for (int k = 0; k < n; ++k) // k = number of ants ,
        {
            //make tour with k ant
            double dist = 0;
            Ant ant(0, graph.vertexes[0], alpha, beta);
            while (ant.path.size() < n)
                dist += ant.move(graph.vertexes[ant.path.back().second]);
            dist += graph.vertexes[ant.path.back().second].edges[0].d;
            ant.path.push_back({ant.path.back().second, 0});
            //end tour
            if (dist < minDist) //check if that solution is better
            {
                minDist = dist;
                std::copy(ant.path.begin(), ant.path.end(), bestPath.begin());
            }
            pheromones += 1/dist;
        }
        //optional, you could update after each ant. In this case is after each iteration
        //update pheromones
        for (int i = 0; i < n; ++i)
            graph.vertexes[i].updatePheromone(alpha, beta, pheromones, rho);
    }
    //Print solution
    for(int i=0; i<n; ++i)
        std::cout << bestPath[i].second << " ";
    std::cout << "\nDistance: " << minDist << std::endl;

    return 0;
}