#include "pheromonetrail.h"

PheromoneTrail::PheromoneTrail()
{

}

void PheromoneTrail::setPheromone(point start, point end, float pheromone)
{


//    if(start == end){
//        cout << "ERROR: Pheromonetrail start and end position is identical" << endl;
//        cout << "start and end position: {" << start.x() << "," << start.y() << "}" << endl;
//    }

   vector<point> current_trail = sort(start,end);

    _trail.push_back(current_trail);
    _pheromone.push_back(pheromone);


}

float PheromoneTrail::getpheromone(point start, point end)
{

    vector<point> testRoute = sort(start,end);

    for(unsigned int i = 0; i < _trail.size(); i++){

        if(testRoute[0] == _trail[i][0] && testRoute[1] == _trail[i][1]){

            return _pheromone[i];
        }

    }

    return 1;

}

void PheromoneTrail::evaporate()
{
    float evaporation = 0.01;

    for(unsigned int i = 0; i < _trail.size(); i++){

        if(_pheromone[i] >= 1/(1-evaporation)){

            _pheromone[i] = (1-evaporation)*_pheromone[i];  // Evaporate pheromone
        }else{

             _pheromone.erase(_pheromone.begin()+i);  // If Pheromone is less than 1 (negative pheromone), delete trail instead;
             _trail.erase(_trail.begin()+i);
             i--;
        }
    }

}

void PheromoneTrail::clear()
{
    _trail.clear();
    _pheromone.clear();

}




vector<point> PheromoneTrail::sort(point start, point end)
{

    vector<point> current_trail;

    if(start.x() > end.x()){

        current_trail = {start, end};
    }else if(start.x() == end.x() && start.y() > end.y()){

        current_trail = {start, end};
    }else{

        current_trail = {end, start};
    }

    return current_trail;


}
