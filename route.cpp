#include "route.h"

Route::Route(){

}


Route::Route(string input)
{

    createRoutes(input);


    _innerRoute = createShortestTour(_innerRoute);

    _outerRoute = createShortestTour(_outerRoute);
    cout << "Shortest tours has been created" << endl;


}

void Route::testRandomVertices(vector<point> vertices)
{
    _innerRoute = createShortestTour(vertices);

    _outerRoute = _innerRoute;
}

vector<point> Route::getInnerRoute()
{
    return _innerRoute;
}

vector<point> Route::getOuterRoute()
{
    return _outerRoute;
}

bool Route::onRoad(point object)
{
    int Collision = 0;


    point start1Line;
    point end1Line;

    point start2Line;
    point end2Line;

    start1Line.setX(0);
    start1Line.setY(0);

    end1Line.setX(object.x());
    end1Line.setY(object.y());

    point startPoint;


    vector<vector<point>> Lane;
    Lane.push_back(_outerRoute);
    Lane.push_back(_innerRoute);


    for(int i = 0; i < 2; i++){

        startPoint = Lane[i][0];

    for(unsigned int j = 0; j < Lane[i].size(); j++){

        if(j != Lane[i].size()-1){

            start2Line.setX(Lane[i][j].x());
            start2Line.setY(Lane[i][j].y());

            end2Line.setX(Lane[i][j+1].x());
            end2Line.setY(Lane[i][j+1].y());
        }else{

            start2Line.setX(Lane[i][j].x());
            start2Line.setY(Lane[i][j].y());

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
            Collision++;
        }
    }


    if(i == 0){ // if the outer route collides an even number of times, dont bother looking at the inner route, return false;
        if(Collision%2 == 0){
            return false;
        }
    }

    }

    if(Collision%2 == 0){
        return false;
    }else{
        return true;
    }

}

vector<point> Route::createShortestTour(vector<point> vertices)
{

    ColonyMapping routeMapping(vertices);

    vector<point> shortestTour;
    float shortestDistance = 0;

    int likefactor = 7;
    int pheromonefactor = 7;

    int cycles = 20;

    for(int i = 0; i < cycles; i++){
    vertices = routeMapping.RunACO(likefactor, pheromonefactor);

    likefactor++;
    if(likefactor == 10){
        likefactor = 7;
        pheromonefactor++;
        if(pheromonefactor == 10){
            pheromonefactor = 7;
        }
    }


    Ant anthony;

    float distance = anthony.getDistance(vertices);

    cout << "distance: " << distance << " : " << "like -> " << likefactor << " : " << "pheromone -> " << pheromonefactor << endl;

    if(distance < shortestDistance){
        shortestDistance = distance;
        shortestTour = vertices;
    }else if(i == 0){
        shortestDistance = distance;
        shortestTour = vertices;
    }

    }


    cout << endl;
    cout << "Sorted vertices" << endl;
    cout << "{";
    for(unsigned int i = 0; i < shortestTour.size(); i++){
        cout << "{" << shortestTour[i].x() << "," << shortestTour[i].y() << "}";

        if(i != shortestTour.size()-1){
            cout << ",";
        }
    }
    cout << "}" << endl;

    cout << endl;
    cout << "Shortest Distance: " << shortestDistance<< endl;
    cout << "Amount of Vertices: " << shortestTour.size()+1 << endl;

    return shortestTour;



}

void Route::createRoutes(string input)
{

    int startRead = 0;
    int endRead = 0;


    //Lav string input om til tal datatyper fordelt ud i de to lister.

    while(true){
        if(input.length() == 0){
            break;
        }
        if(input.at(startRead+endRead) == ')'){
            endRead++;

            string coords = input.substr(startRead+1,endRead-startRead-2); //Get input coordinates as "Coordinate_X,Coordinate_Y"
            int commapos = 1;

            while(true){
                if(coords.at(commapos) == ','){
                    break;
                }else{
                    commapos++;
                }
            }

            int posX = stoi(coords.substr(0,commapos));
            int posY = stoi(coords.substr(commapos+1,coords.length()-commapos));

            int emptySpace = 0;
            while(input.at(startRead+endRead+emptySpace) == ' '){
                emptySpace++;
            }

            point pos(posX, posY);

            if (input.substr(startRead+endRead+emptySpace, 4) == "blue"){

                _innerRoute.push_back(pos);
                int lastPos = startRead+endRead+emptySpace+4;
                input = input.substr(lastPos,input.length()-lastPos);

            }else{

                _outerRoute.push_back(pos);
                int lastPos = startRead+endRead+emptySpace+6;
                input = input.substr(lastPos,input.length()-lastPos);

            }

            endRead = 0;
            emptySpace = 0;

        }else{
            endRead++;
        }

    }

}

