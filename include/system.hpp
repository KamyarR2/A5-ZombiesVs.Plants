#pragma once

#include "global.hpp"
#include "player.hpp"
#include "handler.hpp"


enum State
{
    IN_GAME,
    GAME_OVER,
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
    State state;
    Texture backgroundTexture;
    Sprite backgroundSprite;

    Texture gameOverTexture;
    Sprite gameOverSprite;

    Shader shader;
    int frameRate;
    void render();
    void update();
    void handleEvents();
    void handleMousePressed(Event event);
    void handleMouseReleased(Event event);
};