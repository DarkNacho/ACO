#include "Graph.h"

Graph::Graph()
{
    vertexes = std::vector<Vertex>();;
}
Graph::Graph(int _vertex)
{
    vertexes = std::vector<Vertex>(_vertex);;
}

void Graph::addEdge(int u, int v)
{
    double d = vertexes[v].p.dist(vertexes[u].p);
    //vertexes[v].edges.push_back(edge(v,u,d));
    vertexes[u].edges.push_back(edge(u,v,d));
}

void Graph::addVertex(PT p)
{
    vertexes.push_back(Vertex(p));
}


std::string Graph::tostring()
{
    std::string msg = "";
    for(Vertex v: vertexes)
    {
        msg += "Node: " + v.p.tostring() + "\n";
        msg += "Probability: " + std::to_string(v.probability) + "\n";
        msg += "\tChild:\n";
        for(edge e: v.edges)
            msg += "\t\t" + e.tostring() + "\n";
    }
    return  msg;
}
