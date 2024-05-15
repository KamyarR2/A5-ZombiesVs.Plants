#include "../include/projectile.hpp"

Projectile :: Projectile(int x, int y, float s, string address)
{
   if (!texture.loadFromFile(PICS_PATH + "/Projectile/" + address))
        {
            return;
        }
    sprite.setTexture(texture);
    sprite.setScale(1,1);
    sprite.setPosition(x,y);
    speed = s;
}

Projectile :: ~Projectile(){}

void Projectile :: render(RenderWindow &window){
   window.draw(sprite);
}

void Projectile :: update(){
      sprite.setPosition(sprite.getPosition().x + speed, sprite.getPosition().y);
}

bool Projectile :: isOut(Vector2u windowSize)
{
   FloatRect bounds = sprite.getGlobalBounds();
   if (bounds.left + bounds.width < 0 || 
            bounds.left > 3*windowSize.x/4 ||
            bounds.top + bounds.height < 0 ||
            bounds.top > windowSize.y) {
      return true;
        }
   return false;
}