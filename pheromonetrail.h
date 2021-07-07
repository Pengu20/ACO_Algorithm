#ifndef PHEROMONETRAIL_H
#define PHEROMONETRAIL_H

#include <vector>

#include "ant.h"

#include "point.h"

class PheromoneTrail
{
public:
    PheromoneTrail();
    void setPheromone(point start, point end, float pheromone);
    float getpheromone(point start, point end);
    void evaporate();
    void clear();


private:
    vector<vector<point>> _trail;
    vector<float> _pheromone;

    vector<point> sort(point start, point end);

};

#endif // PHEROMONETRAIL_H
