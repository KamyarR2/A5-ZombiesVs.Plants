#pragma once

#include "global.hpp"


class Zombie
{
public:
    Zombie(int x, int y, float s, float h, int d, string address);
    ~Zombie();
    void render(RenderWindow &window);
    void update();
    FloatRect getBound(){return sprite.getGlobalBounds();}
    FloatRect getInnerRect(){return innerRect.getGlobalBounds();}
    bool isDelete(){return DelOrNot;}
    void Delete(){DelOrNot = true;}
    bool isOut();
    void freeze();
    bool isFreezed(){return freezeOrNot;}
    void startClock(){clock.restart();}
    void damage();
    void iceDamaged();
    bool isDead();
    bool isStop(){return stopOrNot;}
    void stop();
    void move();

private:
    float speed;
    float hitPoint;
    float hitDamage;
    Texture texture;
    Sprite sprite;
    FloatRect rectangle;
    RectangleShape innerRect;
    Vector2f pos;
    string address;
    Clock clock;
    bool DelOrNot = false;
    float xScale;
    float yScale;
    float boundScalex;
    float boundScaley ;
    bool freezeOrNot = false;
    bool stopOrNot = false;
};
