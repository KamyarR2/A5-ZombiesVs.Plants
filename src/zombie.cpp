#include "../include/zombie.hpp"


Zombie :: Zombie(int x, int y, float s, float h, int d, string address)
{
    speed = s;
    xScale = 1;
    yScale = 1;
    boundScalex = 2.4;
    boundScaley = 3.1;

    hitPoint = h;
    hitDamage = d;

    if (!texture.loadFromFile(PICS_PATH + "Zombies/" + address))
    {
        return;
    }
    sprite.setTexture(texture);
    sprite.setScale(xScale, yScale);
    sprite.setPosition(x - sprite.getGlobalBounds().width,y - sprite.getGlobalBounds().height);

    FloatRect bounds = sprite.getGlobalBounds();
    innerRect.setSize(Vector2f(bounds.width/boundScalex, bounds.height/boundScaley));
    innerRect.setFillColor(Color::Transparent);
    innerRect.setOutlineColor(Color::Red);
    innerRect.setOutlineThickness(2);

    
}

Zombie :: ~Zombie(){}


void Zombie :: render(RenderWindow &window){

    window.draw(sprite);

    // window.draw(innerRect);

}

void Zombie :: update(){
    

    if(isFreezed())
    {
        sprite.setPosition(sprite.getPosition().x-speed/10 , sprite.getPosition().y);
        sprite.setColor(Color :: Blue);
        float elapsedTime = clock.getElapsedTime().asSeconds(); 
        if(elapsedTime>=2)
        {
            clock.restart();
            freezeOrNot = false;
        }
    }
    else if (isStop()){
        sprite.setPosition(sprite.getPosition().x , sprite.getPosition().y);

    }
    else
    {
        sprite.setPosition(sprite.getPosition().x -speed , sprite.getPosition().y);
        sprite.setColor(Color :: White);
    }
    
    

    FloatRect bounds = sprite.getGlobalBounds();
    innerRect.setPosition(bounds.left + bounds.width/2.7, bounds.top + bounds.height/2.7);
    
}




bool Zombie :: isOut()
{
    FloatRect bounds = getBound();
    if(bounds.left + bounds.width/2 < topLeft[0]) {
        return true;
    }
    return false;
}

void Zombie :: freeze()
{
    freezeOrNot = true;
    clock.restart();
}

void Zombie :: stop()
{
    stopOrNot = true;
}
void Zombie :: move()
{
    stopOrNot = false;
}

void Zombie :: damage(){
    hitPoint -= 1;
}
void Zombie :: iceDamaged(){
    hitPoint -= 0.5;
}
bool Zombie :: isDead(){
    if  (hitPoint <= 0 ){
        return true;
    }
    else{
        return false;
    }
}