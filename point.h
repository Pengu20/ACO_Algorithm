#ifndef POINT_H
#define POINT_H

#include <cmath>>

class point
{
public:
    point();
    point(float x, float y);
    float x();
    float y();

    void setX(float x);
    void setY(float y);

    float distance(point end);


    bool operator==(point n){
        //Overloader "==" kommando således at jeg kan checke to Pos objekter ved blot at bruge "=="
        if(_x == n.x() && _y == n.y()){
            return true;
        }else{
            return false;
        }
    }


    bool operator!=(point n){
        if(_x == n.x() && _y == n.y()){
            return false;
        }else{
            return true;
        }
    }

private:
    float _x;
    float _y;
};



#endif // POINT_H
