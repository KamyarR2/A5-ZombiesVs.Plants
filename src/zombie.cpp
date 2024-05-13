#include "../include/zombie.hpp"


Zombie :: Zombie(int x, int y, string address)
{
   Vector2i pos = {x,y};
    if (!texture.loadFromFile("../Pics/Zombies/" + address))
    {
        return;
    }
    sprite.setTexture(texture);
    sprite.setScale(0.35,0.35);
    sprite.setPosition(x - sprite.getGlobalBounds().width,y - sprite.getGlobalBounds().height);

    FloatRect bounds = sprite.getGlobalBounds();
    innerRect.setSize(Vector2f(bounds.width/2.8, bounds.height/2.8));
    innerRect.setFillColor(Color::Transparent);
    innerRect.setOutlineColor(Color::Red);
    innerRect.setOutlineThickness(2);
}

Zombie :: ~Zombie(){}



void Zombie :: render(RenderWindow &window){

    window.draw(sprite);
    // if(isOut()){
    //     window.draw(innerRect);
    // }
}

void Zombie :: update(){
    
    sprite.setPosition(sprite.getPosition().x + speed, sprite.getPosition().y);
    FloatRect bounds = sprite.getGlobalBounds();
    innerRect.setPosition(bounds.left + bounds.width/2.7, bounds.top + bounds.height/2.7);
    
}




bool Zombie :: isOut()
{
    FloatRect bounds = getBound();
    if(bounds.left + bounds.width/2 < topLeft[0]) {
        return true;
        cout << "raft biroon!" <<endl;
    }
    return false;
}