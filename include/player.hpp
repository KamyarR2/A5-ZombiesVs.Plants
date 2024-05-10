# pragma once

#include "global.hpp"



class Player{

public:
    Player(int x, int y);
    ~Player();
    void render(RenderWindow &window);
    void update(Vector2i mousePose);
    void handleMousePressed(Vector2i pos);
    void handleMouseReleased(Vector2i pos);

private:
    Texture texture;
    Sprite sprite;
    RenderWindow *window;
    Vector2f pos;
    bool isDragged = false;
    bool isClicked = false;
    int clock = 0;
    int time = 0;
};