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
