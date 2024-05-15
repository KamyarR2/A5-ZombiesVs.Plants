#pragma once

#include "global.hpp"
#include "player.hpp"
#include "handler.hpp"
#include "screen.hpp"



enum State
{
    MENU,
    IN_GAME,
    GAME_OVER,
    WIN,
    EXIT
};


class System{

public:
    System(int width, int height, int frameRate);
    void run();
    ~System();
    RenderWindow window;
private:
    Player* player;
    Handler* handler;
    Screen* menuScreen;
    Screen* gameScreen;
    Screen* inGameMenuScreen;
    State state;
    Texture backgroundTexture;
    Sprite backgroundSprite;

    Music music;
    Texture gameOverTexture;
    Sprite gameOverSprite;
    Texture winTexture;
    Sprite winSprite;
 
    int frameRate;
    void render(RenderWindow &window);
    void update();
    void handleEvents();
    
    void handleMousePressed(Event event);
    void handleMouseReleased(Event event);
};