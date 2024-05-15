#pragma once

#include "global.hpp"
#include "projectile.hpp"
#include "seedCards.hpp"
#include "sun.hpp"


class Plant{

public:
    Plant(int x, int y, float v, float h, float d, float speed, float hitRate, string address, string projAddress);
    ~Plant();

    Vector2f getSpritePosition(){return sprite.getPosition();}
    FloatRect getSpriteRect(){return sprite.getGlobalBounds();}
    Vector2f getCenter();
    string getProjAddress(){return projAddress;}
    Projectile* addProjectile(Vector2f pos, string projAddress);
    Sun* addSun();


    void render(RenderWindow &window);
    void update(Vector2i pos);
    void startDrag();
    void stopDrag(Vector2f tileOrigin);
    bool isDragging(){return DraggedOrNot;}
    void planted();
    bool isPlanted(){return PlantedOrNot;}
    int getValue(){return value;}
    bool isDead(){return DeadOrNot;}
    bool canShoot(){return hasProjectile;}
    bool isFlower();
    void letSeedCardKnow(SeedCard *seedCard);
    void resetClock();
    void deleteOutOfBound(Vector2u windowSize);
    void deleteProjCollision();
    bool checkProjCollision(FloatRect zombieBound);
    bool checkPlantCollision(FloatRect zombieBound);
    void resetSunClock();
    void damage();
    void dead();


private:
    int value;
    float health;
    float damaging;
    float speed;
    float hitRate;
    float totalHealth;
    Sprite sprite;
    Texture texture;
    string address;
    vector <Projectile*> projTrash;
    vector <Projectile*> projectiles;
    vector <Sun*> suns;
    Sun* sun;
    Projectile* projectile;
    SeedCard *seedCard;

    bool PlantedOrNot = false;
    bool DraggedOrNot = false;
    bool arrivedOrNot = false;
    bool DeadOrNot = false;
    bool hasProjectile = false;
    string projAddress;
    Clock clock;
    Clock sunClock;
    bool clockOn = false;
    int frequency;
};