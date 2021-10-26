#include "GameObject.h"

Pos::Pos()
{
}

Pos::Pos(float x, float y)
{
    VectorMath2 posIn = VectorMath2(x,y);
    this->posVar = posIn;
}

Pos::Pos(VectorMath2 posIn){
    this->posVar = posIn;
}