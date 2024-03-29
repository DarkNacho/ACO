#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#ifndef ACO_UTILS_H
#define ACO_UTILS_H


struct PT
{
    float x, y;
    PT(float _x, float _y) : x(_x), y(_y) {}
    PT() {};
    //PT(const PT &p) : x(p.x), y(p.y) {}
    double dist2(PT p) { return ((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y)); }
    double dist(PT p) { return sqrt(dist2(p));}
    std::string tostring() { return "(" + std::to_string(x) + "," + std::to_string(y) + ")"; }
    bool operator==(const PT &p) { return x == p.x && y == p.y; }
};

class edge
{
public:
    int u, v; double d, pheromone;
    edge(int _u, int _v, double _d): u(_u), v(_v), d(_d), pheromone(1) {}
    void addPheromone(double p) {pheromone += p;}
    void evaporatePheromone(double evaporation) {pheromone *= (1-evaporation);}
    double getProbability(double alpha, double beta) const{return   u==v ? 0 : pow(pheromone,alpha) * pow((1/d), beta);}
    std::string tostring() {return std::to_string(u) + "-" + std::to_string(v) + " " + std::to_string(d) + " " + std::to_string(pheromone); }
    bool operator>(const edge& a) const { return this->getProbability(1,1) > a.getProbability(1,1); }
};

class Vertex
{
public:
    PT p;
    std::vector<edge> edges;
    Vertex() {};
    Vertex(PT _p): p(_p){}
    void evaporatePheromones(double evaporation)
    {
        for(int i=0;i<edges.size();++i)
            edges[i].evaporatePheromone(evaporation);
    }
    void setPheromones(double pheromone)
    {
        for(int i =0; i<edges.size(); ++i)
            edges[i].pheromone = 1;
    }


};

#endif //ACO_UTILS_H
