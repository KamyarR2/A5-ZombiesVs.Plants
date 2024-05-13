#pragma once

#include "global.hpp"



class Sun
{
public:
    Sun(int x, int y);
    ~Sun();
    void render(RenderWindow &window);
    void update();
    bool isOut(Vector2u windowSize);
    bool contains(Vector2i pos);
    bool isClicked(){return clickOrNot;}
    void clicked();

private:
    float const speed = 1;
    Texture texture;
    Sprite sprite;
    Vector2f pos;
    bool clickOrNot = false;
};
