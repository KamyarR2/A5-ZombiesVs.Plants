#pragma once

#include "global.hpp"
#include "player.hpp"
#include "handleZombie.hpp"
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
    void handleMouseReleased();
    void handleCollision();
    void unlockPlant();
    void addPlant(Vector2i pos, float value, float health, float damage, float speed, float hitRate, string address, string projAddress);
    bool isGameOver(){return gameOver;}
    bool isWin(){return win;}
    
private:
    Player *player;
    vector <Sun*> suns;
    vector <SeedCard*> seedCards;
    vector <Plant*> plants;
    vector <Tile*> tiles;
    vector <Zombie*> zombies;
    vector <Projectile*> projectiles;
    vector <Zombie*> zombieTrash;
    HandleZombie *zombieHandler;

    SeedCard *selectedSeedCard = nullptr;




    SunBar *sunBar;
    void deleteOutOfBound(RenderWindow &window);
    void deleteIsClicked();
    void addSun();
    
    Clock clock;
    int time = 0;
    bool isDragged = false;
    bool gameOver = false;
    bool win = false;
};