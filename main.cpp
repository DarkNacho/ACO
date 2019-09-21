//#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "Graph.h"
#include "Ant.h"
#include "utils.h"
int main(int argc , char *argv[])
{
    //graph init
    int n,k;
    double  alpha, beta, rho;
    k = std::stoi(argv[2]);
    alpha = std::stod(argv[3]);
    beta = std::stod(argv[4]);
    rho = std::stod(argv[5]);
    std::ifstream cin(argv[1]);
    std::string test;
    std::map<int, int> graphMap;
    Graph graph;

    //reading first lines of the tsp file
    getline(cin, test);
    getline(cin, test);
    getline(cin, test);
    cin >> test >> n;
    getline(cin, test);
    getline(cin, test);
    getline(cin, test);
    //reading tsp nodes and creating graph
    for (int i = 0; i < n; ++i) {
        int k, u, v;
        cin >> k >> u >> v;
        graphMap[i] = k; //mapping graph index
        graph.addVertex(PT(u, v)); //initial Vertex
    }
    //connecting all nodes with all
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            graph.addEdge(i, j); //connect every vertex with edges
        graph.vertexes[i].setPheromones(1);  //init pheromones
    }
    //end graph init

     //aco init
    double minDist = INFINITY;
    std::vector<std::pair<int, int>> bestPath(n + 1);

    //aco end
    while (k--)
    {
        //make tour with k ant
        double dist = 0;
        Ant ant(0, graph.vertexes[0], alpha, beta);
        while (ant.path.size() < n)
            dist += ant.move(graph.vertexes[ant.path.back().second]);

        dist += graph.vertexes[ant.path.back().second].edges[0].d;
        ant.path[0] = {ant.path.back().second, 0};
        //end tour

        //update pheromones
        for (int j = 0; j < n; ++j)
        {
            int v = ant.path[j].first;
            int u = ant.path[j].second;
            graph.vertexes[j].evaporatePheromones(rho);
            graph.vertexes[v].edges[u].addPheromone(1 / dist);
            graph.vertexes[u].edges[v].addPheromone( 1 / dist);
        }


        if (dist < minDist) //check if solution is better
        {
            minDist = dist;
            std::copy(ant.path.begin(), ant.path.end(), bestPath.begin());
        }
    }

    //Print solution
    for (int i = 0; i < n; ++i)
        printf("%d ", graphMap[bestPath[i].second]);
    printf("\nDistance: %.2lf\n", minDist);
    return 0;
}