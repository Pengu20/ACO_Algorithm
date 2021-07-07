#ifndef COLONYMAPPING_H
#define COLONYMAPPING_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;

//Point list sorting
#include<math.h>

#include "ant.h"

#include "pheromonetrail.h"

class ColonyMapping
{
public:
    ColonyMapping(vector<point> vertices);
    vector<point> RunACO(int likefactor, int pheromonefactor);
    float getDistance();

private:
    bool MapValid(vector<point> map); //checks if lines cross -> true in collision
    vector<point> _vertices;


};

#endif // COLONYMAPPING_H
