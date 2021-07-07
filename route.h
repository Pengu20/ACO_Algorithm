#ifndef ROUTE_H
#define ROUTE_H

#include "colonymapping.h"

#include "point.h"


#include<math.h>


class Route
{
public:
    Route();
    Route(string input);

    vector<point> getInnerRoute();
    vector<point> getOuterRoute();
    bool onRoad(point object);

    void testRandomVertices(vector<point> vertices);


private:

    vector<point> createShortestTour(vector<point> vertices);

    vector<point> _innerRoute;
    vector<point> _outerRoute;
    void createRoutes(string input);




};

#endif // ROUTE_H
