#pragma once
#include "core/VectorMath.h"

struct Pos
{
    VectorMath2 posVar;

    Pos();
    Pos(float x, float y);
    Pos(VectorMath2);

    void operator=(Pos posIn){
        posVar = posIn.posVar;
    }
    bool operator==(const Pos& posIn){
        if(posVar == posIn.posVar)
            return true;

        return false;
    }
    bool operator<(const Pos& posIn) const {
        if(posVar.x < posIn.posVar.x) return true;
        if(posVar.x > posIn.posVar.x) return false;
        //x == coord.x
        if(posVar.y < posIn.posVar.y) return true;
        if(posVar.y > posIn.posVar.y) return false;

        return false;
    }
};

class GameObject {
public:
    int ID;
    Pos pos;
    Pos previousPos;
    float size;
};