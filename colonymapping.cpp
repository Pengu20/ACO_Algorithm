#include "colonymapping.h"

ColonyMapping::ColonyMapping(vector<point> vertices)
    :_vertices(vertices)
{

}

vector<point> ColonyMapping::RunACO(int likeFactor, int pheromoneFactor)
{

    vector<point> antRoute;

    Ant anthony;
    PheromoneTrail pheromoneMapping;

    int antNumber = 10;

    vector<point> shortestTour;
    float ShortestDistance = 0;


    for(int antAmount = 0; antAmount < antNumber; antAmount++){
        anthony.forgetRoute();
        antRoute = _vertices;

        int randomRoute = rand() % antRoute.size();

        point startPos = antRoute[randomRoute];
        antRoute.erase(antRoute.begin()+randomRoute);


        anthony.addRouteStart(startPos);


    while(antRoute.size() > 0){

        vector<float> pheromone;

        for(unsigned int i = 0; i < antRoute.size(); i++){
            pheromone.push_back(pheromoneMapping.getpheromone(startPos,antRoute[i]));
        }
        vector<point> travel;

        if(antAmount != antNumber-1){
            travel = anthony.chooseRoute(startPos, antRoute, pheromone,likeFactor);
        }else{
            travel = anthony.followPheromonetrail(startPos, antRoute, pheromone);
        }

        antRoute.erase(std::remove(antRoute.begin(), antRoute.end(), travel[1]), antRoute.end());
        pheromoneMapping.setPheromone(travel[0], travel[1], anthony.feromoneRelease(travel, pheromoneFactor));

        startPos = travel[1];
    }

    if(antAmount%5 == 0){
    pheromoneMapping.evaporate();
    }

    if(antAmount == 0){
        ShortestDistance = anthony.getDistance();
        shortestTour = anthony.getRoute();
    }else if(anthony.getDistance() < ShortestDistance){
        ShortestDistance = anthony.getDistance();
        shortestTour = anthony.getRoute();

    }


// Prune mappings were their lines collide.

    if(antAmount == antNumber-1){
        if(!MapValid(shortestTour)){
            antAmount = -1;
            anthony.forgetRoute();
            pheromoneMapping.clear();
        }
    }


    }

    return shortestTour;




}

bool ColonyMapping::MapValid(vector<point> map)
{

    point start1Line;
    point end1Line;

    point start2Line;
    point end2Line;

    point startPoint = map[0];


    while(map.size() > 0){

        start1Line.setX(map[0].x());
        start1Line.setY(map[0].y());

        end1Line.setX(map[1].x());
        end1Line.setY(map[1].y());


    for(unsigned int j = 1; j < map.size(); j++){


        if(j != map.size()-1){

            start2Line.setX(map[j].x());
            start2Line.setY(map[j].y());

            end2Line.setX(map[j+1].x());
            end2Line.setY(map[j+1].y());
        }else{

            start2Line.setX(map[j].x());
            start2Line.setY(map[j].y());

            end2Line.setX(startPoint.x());
            end2Line.setY(startPoint.y());

        }

        float x1 = start1Line.x();
        float y1 = start1Line.y();

        float x2 = end1Line.x();
        float y2 = end1Line.y();

        float x3 = start2Line.x();
        float y3 = start2Line.y();

        float x4 = end2Line.x();
        float y4 = end2Line.y();


        float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
        float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));


        if (uA > 0 && uA < 1 && uB > 0 && uB < 1) {
//            cout << "Collision detected, between: " << endl;
//            cout << "line: (" << x1 << "," << y1 <<") (" << x2 << ","<< y2 << ")" << endl;
//            cout << "line: (" << x3 << "," << y3 <<") (" << x4 << ","<< y4 << ")" << endl;
//            cout << endl;
            return false;
            break;
        }
    }

    map.erase(map.begin());


    }




    return true;

}


