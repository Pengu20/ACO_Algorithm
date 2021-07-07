#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "colonymapping.h"

#include "point.h"


#include<math.h>

#include "route.h"


using namespace std;


int main()
{
    srand (static_cast <unsigned> (time(0)));

    //et punkt må ikke befinde sig i origo!
    string input  =
                    "(4,8) blue"
                    "(13,11) blue"
                    "(14,8) blue"
                    "(14,5) blue"
                    "(4,6) blue"
                    "(10,12) blue"
                    "(12,3) blue"
                    "(10,4) blue"
                    "(4,10) blue"
                    "(4,3) blue"
                    "(10,6) blue"
                    "(14,3) blue"
                    "(10,11) blue"
                    "(8,9) blue"
                    "(8,12) blue"
                    "(10,10) blue"
                    "(12,10) blue"
                    "(2,4) blue"
                    "(12,9) blue"
                    "(3,3) blue"
                    "(10,3) blue"
                    "(11,3) blue"
                    "(7,8) blue"
                    "(3,5) blue"
                    "(11,9) blue"
                    "(7,5) blue"
                    "(6,3) blue"
                    "(5,2) blue"
                    "(6,11) blue"
                    "(8,6) yellow"
                    "(8,4) yellow"
                    "(9,8) blue"
                    "(7,2) yellow"
                    "(5,1) yellow"
                    "(3,1) yellow"
                    "(1,3) yellow"
                    "(1,6) yellow"
                    "(1,8) yellow"
                    "(2,9) yellow"
                    "(2,10) yellow"
                    "(1,13) yellow"
                    "(2,14) yellow"
                    "(3,15) yellow"
                    "(4,15) yellow"
                    "(5,14) yellow"
                    "(6,13) yellow"
                    "(7,14) yellow"
                    "(8,15) yellow"
                    "(9,16) yellow"
                    "(10,16) yellow"
                    "(11,17) yellow"
                    "(12,15) yellow"
                    "(12,14) yellow"
                    "(13,13) yellow"
                    "(14,13) yellow"
                    "(15,12) yellow"
                    "(2,11) yellow"
                    "(2,12) yellow"
                    "(12,16) yellow"
                    "(16,10) yellow"
                    "(16,9) yellow"
                    "(16,11) yellow"
                    "(16,6) yellow"
                    "(16,7) yellow"
                    "(16,4) yellow"
                    "(15,2) yellow"
                    "(12,1) yellow"
                    "(10,1) yellow"
                    "(9,3) yellow";

    //Lav string input om til tal datatyper fordelt ud i de to lister.



    //Oprettelse af sorterings klasser

    Route collisionRoad(input);

    vector<point> InnerMap = collisionRoad.getInnerRoute();

    vector<point> OuterMap = collisionRoad.getOuterRoute();



    //Partikle Movement
    point objectMovement(rand() % 14, rand() % 14);
    int stepcount = 0;
    bool positiveMovementVertical = true;
    bool positiveMovementHorizontal = true;



    unsigned int WindowHeight = 700;
    unsigned int WindowWidth = 700;


    //Oprettelse af vinduet
    sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "Ant_Colony_Optimization_Algorithm");
    sf::Color Grey(245,245,245,255);
    window.clear(Grey);


    sf::CircleShape point(8);
    point.setFillColor(sf::Color(20, 95, 182));


    int MapScaling = 40;

    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){

            if(event.type == sf::Event::Closed){
                window.close();
            }

        }

        sf::Color Grey(245,245,245,255);
        window.clear(Grey);


        //Oprettelse af linjerne mellem punkterne
        sf::VertexArray polygon(sf::LinesStrip, InnerMap.size()+1);

        for(unsigned int i = 0; i < InnerMap.size(); i++){
            polygon[i].position = sf::Vector2f(InnerMap[i].x()*MapScaling, InnerMap[i].y()*MapScaling);
            polygon[i].color = sf::Color::Red;
        }

        polygon[InnerMap.size()].position = sf::Vector2f(InnerMap[0].x()*MapScaling, InnerMap[0].y()*MapScaling);
        polygon[InnerMap.size()].color = sf::Color::Red;

        window.draw(polygon);



        //Oprettelse af linjerne mellem punkterne
        sf::VertexArray polygon2(sf::LinesStrip, OuterMap.size()+1);

        for(unsigned int i = 0; i < OuterMap.size(); i++){
            polygon2[i].position = sf::Vector2f(OuterMap[i].x()*MapScaling, OuterMap[i].y()*MapScaling);
            polygon2[i].color = sf::Color::Blue;
        }

        polygon2[OuterMap.size()].position = sf::Vector2f(OuterMap[0].x()*MapScaling, OuterMap[0].y()*MapScaling);
        polygon2[OuterMap.size()].color = sf::Color::Blue;

        window.draw(polygon2);



        //Oprettelse af punkter i SFML vinduet

        point.setFillColor(sf::Color(20, 95, 182));

        for(auto i : InnerMap){

            point.setPosition(i.x()*MapScaling, i.y()*MapScaling);
            window.draw(point);
        }


        point.setFillColor(sf::Color(235, 223, 60));

        for(auto i : OuterMap){

            point.setPosition(i.x()*MapScaling, i.y()*MapScaling);
            window.draw(point);
        }


        //Oprettelse af det bevægelige object i sfml vinduet
        point.setFillColor(sf::Color(255, 0, 0));

        point.setPosition(objectMovement.x()*MapScaling, objectMovement.y()*MapScaling);
        window.draw(point);

        //Bevægelse logik for objektet
        stepcount++;
        if(stepcount == 1){

            if(collisionRoad.onRoad(objectMovement)){
                cout << "All is gut it is on road" << endl;
            }else{
                cout << "It is outside the road! not good!" << endl;
            }


            if(positiveMovementVertical == true){
                objectMovement.setX(objectMovement.x()+0.01);
            }else{
                objectMovement.setX(objectMovement.x()-0.01);
            }

            if(positiveMovementHorizontal == true){
                objectMovement.setY(objectMovement.y()+0.01);
            }else{
                objectMovement.setY(objectMovement.y()-0.01);
            }


            if(objectMovement.x()*MapScaling > WindowWidth || objectMovement.x()*MapScaling < 0){
                positiveMovementVertical = !positiveMovementVertical;

            }

            if(objectMovement.y()*MapScaling > WindowHeight || objectMovement.y()*MapScaling < 0){
               positiveMovementHorizontal = !positiveMovementHorizontal;
            }


            stepcount = 0;
        }





    window.display();



    }
    return 0;

}
