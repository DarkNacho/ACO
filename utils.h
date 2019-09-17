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
    /***
     * first update the probablity with probablitySum, then you can use this variable.
     */
    double  probability;

    double probablitySum(double alpha, double beta)
    {
        probability = 0;
        for(edge e: edges)
            probability += e.getProbability(alpha,beta);
        return probability;
    }
    /***
     * This will update every edge pheromone, with their evaporation and then adding the new pheromones.
     * @param pheromones
     * @param evaporation
     */
    void updatePheromone(double alpha, double beta, double pheromones, double evaporation)
    {
        for(int i=0; i<edges.size();++i)
        {
            edges[i].evaporatePheromone(evaporation);
            edges[i].addPheromone(pheromones);
            edges[i].getProbability(alpha,beta); //just for update
        }
        this->probablitySum(alpha,beta);
        //std::sort(edges.begin(), edges.end(), std::greater<edge>()); // for a more easy roulete
    }


};

#endif //ACO_UTILS_H
