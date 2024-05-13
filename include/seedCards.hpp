#pragma once

#include "global.hpp"

class SeedCard
{

public:
    SeedCard(int x, int y, int v, string address, string grayAddress, string plantAddress, string projAddress = "");
    ~SeedCard();

    void render(RenderWindow &window);
    void update(Vector2i pos);
    bool isDragged() { return DraggedOrNot;}
    bool contains(Vector2i pos);
    bool isLocked() {return lockOrUnlock;}
    void checkAndUnlock(int sunMoney);
    string getPlantAdress(){return plantAddress;}
    string getProjAddress(){return projAddress;}
    int getValue(){return value;}

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

    int value;
    bool lockOrUnlock = true;
    bool DraggedOrNot = false;
};