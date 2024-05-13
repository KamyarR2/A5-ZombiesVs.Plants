#include "../include/sun.hpp"


Sun :: Sun(int x, int y)
{
   Vector2i pos = {x,y};
   if (!texture.loadFromFile("../Pics/Sun.png"))
        {
            return;
        }
    sprite.setTexture(texture);
    sprite.setScale(0.5,0.5);
    sprite.setPosition(x,y);
}


Sun :: ~Sun(){}


void Sun :: render(RenderWindow &window){
   window.draw(sprite);
}

void Sun :: update(){
      sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y+speed);
}

bool Sun :: isOut(Vector2u windowSize)
{
   FloatRect bounds = sprite.getGlobalBounds();
   if (bounds.left + bounds.width < 0 || 
            bounds.left > windowSize.x ||
            bounds.top + bounds.height < 0 ||
            bounds.top > windowSize.y) {
      return true;
        }
   return false;
}

bool Sun :: contains(Vector2i pos)
{
    FloatRect bounds = sprite.getGlobalBounds();
    return(pos.x >= bounds.left && pos.y >= bounds.top &&
                    pos.x <= (bounds.left + bounds.width) &&
                    pos.y <= (bounds.top + bounds.height));
}


void Sun :: clicked()
{
    clickOrNot = true;
}