#pragma once

#include "global.hpp"
#include "player.hpp"
#include "sun.hpp"
#include "sunBar.hpp"
#include "seedCards.hpp"
#include "plant.hpp"
#include "tile.hpp"
#include "zombie.hpp"
#include "projectile.hpp"

class Handler
{

public:
    Handler(Player *player);
    ~Handler();
    void update(RenderWindow &window);
    void render(RenderWindow &window);
    void handleMousePressed(Vector2i pos);
    void handleMouseReleased(Vector2i pos);
    void handlerCollision(RenderWindow &window);
    void unlockPlant();
    void addPlant(Vector2i pos, string address, int value, string projAddress);
    void checkGameOver();
    bool isGameOver(){return gameOver;}
    
private:
    Player *player;
    vector <Sun*> suns;
    vector <SeedCard*> seedCards;
    vector <Plant*> plants;
    vector <Tile*> tiles;
    vector <Zombie*> zombies;
    vector <Projectile*> projectiles;




    SunBar *sunBar;
    void deleteOutOfBound(RenderWindow &window);
    void deleteIsClicked(RenderWindow &window);
    void deleteReleased(RenderWindow &window);
    void deletePlant();
    void addSun(RenderWindow &window);
    void addZombie(RenderWindow &window);
    void addProjectile(RenderWindow &window, Vector2f pos, string address);
    
    int clock = 0;
    int time = 0;
    bool isDragged = false;
    bool gameOver = false;
};