#include <vector>
#include "utils.h"

#ifndef ACO_ANT_H
#define ACO_ANT_H


class Ant
{
private:
    double alpha = 1; double beta = 1;
    std::vector<bool> visited;

    Vertex init;
    double distance;
    int roulette(std::vector<edge> v);
public:
    Ant(int vertex, Vertex _init, double _alpha, double _beta);
    Ant(int vertex, Vertex _init);
    std::vector<std::pair<int,int>> path; //
    double move(Vertex v);
};


#endif //ACO_ANT_H
