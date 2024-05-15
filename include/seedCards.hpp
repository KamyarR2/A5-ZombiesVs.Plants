#pragma once

#include "global.hpp"

class SeedCard
{

public:
    SeedCard(int x, int y, float v, float c, float h, float d, float s, float hrate, string address, string grayAddress, string plantAddress, string projAddress = "");
    ~SeedCard();

    void render(RenderWindow &window);
    void update();
    bool isDragged() { return DraggedOrNot;}
    bool contains(Vector2i pos);
    bool isLocked() {return lockOrUnlock;}
    void checkAndUnlock(int sunMoney);
    string getPlantAdress(){return plantAddress;}
    string getProjAddress(){return projAddress;}
    float getValue(){return value;}
    float getDamage(){return damage;}
    float getHealth(){return health;}
    float getSpeed(){return speed;}
    float getHitRate(){return hitRate;}
    void startCoolDown(){coolDown = true;}
    bool isCoolDown(){return coolDown;}
    void resetClock();

private:
    Texture texture;
    Texture grayTexture;
    Sprite sprite;
    Sprite graySprite;
    string address;
    string grayAddress;
    string plantAddress;
    string projAddress;
    Font font;
    Text text;
    Text timeText;


    float coolDownTime;
    Clock clock;
    float elapsedTime = 0;
    bool coolDown = false;
    float value;
    float health;
    float damage;
    float speed;
    float hitRate;
    bool lockOrUnlock = true;
    bool DraggedOrNot = false;
};