#pragma once
#include "core/VectorMath.h"

enum class ObjectType
{
    PLAYER,
    ENEMY
};

class GameObject {
public:
    int ID;
    ObjectType objectType;
    VectorMath2 pos;
    VectorMath2 tilePos;
    float size;
};