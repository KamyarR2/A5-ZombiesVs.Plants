#include "../include/player.hpp"


Player :: Player(int x, int y)
{
    pos = Vector2f(x,y);
    if (!texture.loadFromFile("../Pics/CursorPressed.png")){return;}
    sprite.setTexture(texture);
    sprite.setScale(0.5,0.5);
}

Player :: ~Player(){}


void Player :: render(RenderWindow &window)
{
    window.draw(sprite);
}

void Player :: update(Vector2i mousePose)
{
    pos = {static_cast<float>(mousePose.x), static_cast<float>(mousePose.y)};
    sprite.setPosition(pos);
}

