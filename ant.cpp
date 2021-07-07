#include "ant.h"

Ant::Ant()
{

}

vector<point> Ant::chooseRoute(point start, vector<point> endpos, vector<float> feromone, int likeFactor)
{
    vector<point> res;
    res.push_back(start);

    vector<float> pathscores;
    float scoreSum = 0;

    //Create scores for each route
    for(unsigned int i = 0; i < endpos.size(); i ++){

        float score = likability(start, endpos[i], likeFactor) * feromone[i];
        pathscores.push_back(score);
        scoreSum += score;
    }

    //make sum of scores = 1
    transform(pathscores.begin(), pathscores.end(), pathscores.begin(), [scoreSum](float &c){ return c/scoreSum;});

    //Choose route for ant


    float randNum = rand() % 101;

    randNum /= 100;

    float test = 0;
    for(unsigned int i = 0; i < endpos.size(); i ++){

        test += pathscores[i];


        if(test >= randNum){

            _route.push_back(endpos[i]); // Remember route

            res.push_back(endpos[i]);
            return res;
        }



    }



}

vector<point> Ant::getRoute()
{
    return _route;
}

void Ant::addRouteStart(point start)
{
    _route.push_back(start);
}

void Ant::forgetRoute()
{
    _route.clear();
}


float Ant::likability(point start, point end, int likeFactor)
{
    //Like factor = 10

    return pow((1/start.distance(end)),likeFactor);

}

float Ant::feromoneRelease(vector<point> route, int pheromoneFactor)
{
    //Pheromonefactor = 8

    float test = pow((1/route[0].distance(route[1]))+1, pheromoneFactor);

    return test;

}

float Ant::getDistance(vector<point> route)
{

    _route = route;
    return getDistance();

}


float Ant::getDistance()
{

//    cout << "Vertices given" << endl;
//    cout << "{";
//    for(unsigned int i = 0; i < _route.size(); i++){

//        cout << "{" << _route[i].x() << "," << _route[i].y() << "}";
//        if(i != _route.size()-1){
//            cout << ",";
//        }
//    }
//    cout << "}" << endl;



    float distance = 0;

    for(unsigned int i = 0; i < _route.size()-1; i++){
        distance += sqrt(  pow((_route[i+1].x() - _route[i].x()),2) +  pow((_route[i+1].y() - _route[i].y()),2));
    }

    distance += sqrt(  pow((_route[_route.size()-1].x() - _route[0].x()),2) +  pow((_route[_route.size()-1].y() - _route[0].y()),2) );

    return distance;

}
