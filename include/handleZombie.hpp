#pragma once

#include "global.hpp"
#include "zombie.hpp"
#include "plant.hpp"
#include "tile.hpp"

class HandleZombie
{
public:
    HandleZombie();
    ~HandleZombie();
    void render(RenderWindow &window);
    void update();
    void addZombie(RenderWindow &window);
    bool checkGameOver();
    void deleteCollision(vector <Plant*>& plants);
    bool checkWin();
    void clocksRestart();


private:
    Clock clock;
    Clock gameClock;
    Clock addClock;
    float elapsedTime;
    Vector2f zombiePos;
    int trackStage = 0;
    vector <Zombie*> zombies;
};
