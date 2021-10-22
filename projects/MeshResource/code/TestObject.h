#pragma once

struct Pos
{
    float x, y;

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

class TestObject {
public:
    int ID;
    Pos pos;
    float size;
};