#ifndef ACO_GRAPH_H
#define ACO_GRAPH_H

#include "utils.h"
#include <vector>
class Graph
{
public:
    Graph();
    std::vector<Vertex> vertexes;
    Graph(int _vertex);
    void addEdge(edge e);
    void addEdge(int u, int v);
    void addVertex(Vertex v);
    void addVertex(PT p);
    void addVertex(float x, float y);
    std::string tostring();
};


#endif //ACO_GRAPH_H
