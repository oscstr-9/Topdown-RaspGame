#pragma once

struct Pos
{
    float x, y;

    Pos();
    Pos(float x, float y);

    void operator=(const Pos pos) {
        x = pos.x;
        y = pos.y;
    }
    bool operator==(const Pos& pos) const {
        if(pos.x == x && pos.y == y)
            return true;

        return false;
    }
    bool operator<(const Pos& pos) const {
        if(x < pos.x) return true;
        if(x > pos.x) return false;
        //x == coord.x
        if(y < pos.y) return true;
        if(y > pos.y) return false;

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