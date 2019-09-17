#include <iostream>
#include "Ant.h"
#define rnd rand() / (RAND_MAX + 1.)

Ant::Ant(int vertex, Vertex _init, double _alpha, double _beta)
{
    alpha = _alpha;
    beta = _beta;
    init = _init;
    visited = std::vector<bool>(init.edges.size(), false);
    path = std::vector<std::pair<int,int>>();
    path.push_back({vertex,vertex});
    visited[vertex] = true;
}

Ant::Ant(int vertex, Vertex _init)
{
    alpha = 1;
    beta = 1;
    init = _init;
    visited = std::vector<bool>(init.edges.size(), false);
    path = std::vector<std::pair<int,int>>();
    path.push_back({vertex,vertex});
    visited[vertex] = true;
}

/**
 *
 * @param v
 * @return index of the edge
 */
int Ant::roulette(std::vector<edge> v)
{
    double r = rand() / (RAND_MAX + 1.);
    int selected = v[0].v;
    double total = v[0].getProbability(alpha,beta);
    //std::vector<edge> sorted(v.edges.begin(),v.edges.end());
    //std::sort(sorted.begin(), sorted.end(), std::greater<edge>());
    for( int i = 1; i < v.size(); ++i)
    {
        double temp = v[i].getProbability(alpha,beta);
        total += temp;
        if( r <= (temp / total) && !visited[i]) selected = v[i].v;
    }

    return selected;
}
bool Ant::compare(edge e1)
{
    return (visited[e1.v]);
}

double Ant::move(Vertex v)
{

    std::vector<edge> sor;
    for(int i=0; i<v.edges.size(); ++i)
        if(!visited[i]) sor.push_back(v.edges[i]);
    std::sort(sor.begin(), sor.end(), std::greater<edge>());
    int u = 0;
    do
        u = roulette(sor);
    while(visited[u]);
    //visited[v.edges[u].u] = true;
    visited[v.edges[u].v] = true;
    path.push_back({v.edges[u].u, v.edges[u].v});
    return v.edges[u].d;
}
