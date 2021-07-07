#ifndef ANT_H
#define ANT_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;


#include "point.h"

class Ant
{
public:
    Ant();
    vector<point> chooseRoute(point start, vector<point> endpos, vector<float> feromone, int likeFactor);

    vector<point> getRoute();
    void addRouteStart(point start);
    void forgetRoute();

    float feromoneRelease(vector<point> route, int pheromoneFactor);

    float getDistance();
    float getDistance(vector<point> route);


private:
    vector<point> _route;

    float likability(point start, point slut, int likeFactor); //Rutens længde angivet i point





};

#endif // ANT_H
