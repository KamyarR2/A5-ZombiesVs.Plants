# pragma once
#include "global.hpp"

class Projectile
{
public:
    Projectile(int x, int y, string address);
    ~Projectile();
    void render(RenderWindow &window);
    void update();
    FloatRect getBound(){return sprite.getGlobalBounds();}
    bool isOut(Vector2u windowSize);
    bool isDelete(){return DelOrNot;}
    void Delete(){DelOrNot = true;}
private:
    float const speed = 0.8;
    string address;
    Texture texture;
    Sprite sprite;
    Vector2f pos;
    bool DelOrNot = false;
};