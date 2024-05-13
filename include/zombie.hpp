#pragma once

#include "global.hpp"


class Zombie
{
public:
    Zombie(int x, int y, string address);
    ~Zombie();
    void render(RenderWindow &window);
    void update();
    FloatRect getBound(){return sprite.getGlobalBounds();}
    bool isClicked = false;
    void setInnerrect();
    FloatRect getInnerRect(){return innerRect.getGlobalBounds();}
    bool isDelete(){return DelOrNot;}
    void Delete(){DelOrNot = true;}
    bool isOut();

private:
    float const speed = -1;
    Texture texture;
    Sprite sprite;
    FloatRect rectangle;
    RectangleShape innerRect;
    Vector2f pos;
    string address;
    bool DelOrNot = false;
};