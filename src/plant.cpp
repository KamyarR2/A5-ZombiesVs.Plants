#include "../include/plant.hpp"


Plant :: Plant(int x, int y, float v, float h, float d, float s, float hRate, string plantA, string projA)
{
    resetClock();
    resetSunClock();

    if(!projA.empty()){
        hasProjectile = true;
    }
    address = plantA;
    value = v;
    health = h; 
    damaging = d;
    speed = s;
    projAddress = projA;
    hitRate = hRate;
    totalHealth = h;


    if (!texture.loadFromFile(PICS_PATH + "/Plants/"+address)){return;}

    sprite.setScale(0.15,0.15);
    sprite.setTexture(texture);
    sprite.setPosition(x,y);
    
}

Plant :: ~Plant(){}



void Plant :: render(RenderWindow &window)
{
    for(auto projectile : projectiles)
    {
        projectile->render(window);
    }
    
    FloatRect bounds = sprite.getGlobalBounds();
    sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
    rect.setPosition(bounds.left, bounds.top);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Red); 
    rect.setOutlineThickness(2);
    // window.draw(rect);    
    window.draw(sprite);
}

void Plant :: update(Vector2i pos)
{
    for(auto projectile : projectiles)
    {
        projectile->update();
    }
    if(isDragging()){
        Vector2f mousePos = {static_cast<float>(pos.x), static_cast<float>(pos.y)};
        sprite.setPosition({mousePos.x-sprite.getGlobalBounds().width/2, mousePos.y-sprite.getGlobalBounds().height/2});
    }
    if (health < totalHealth/2){
        sprite.setColor(grey);
    }
    else if (health < totalHealth/4){
        sprite.setColor(Color::Black);
    }
}

void Plant :: startDrag()
{
    DraggedOrNot = true;
}

void Plant :: stopDrag(Vector2f tileOrigin)
{
    DraggedOrNot = false;
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    sprite.setPosition(tileOrigin);
}

void Plant :: planted()
{
    PlantedOrNot = true;
}



bool Plant :: isFlower()
{
    if(address == "Sunflower.png")
        return true;
    return false;
}

Vector2f Plant :: getCenter()
{
    float xSun = getSpriteRect().left;
    float ySun = getSpriteRect().top ;
    return Vector2f {xSun, ySun};
}


void Plant :: letSeedCardKnow(SeedCard *seedCard)
{
    seedCard->startCoolDown();
}

void Plant ::  resetClock()
{
    clock.restart();  
}
void Plant ::  resetSunClock()
{
    sunClock.restart();
}


Projectile* Plant :: addProjectile(Vector2f pos, string projAddress)
{
    float elapsedTime = clock.getElapsedTime().asSeconds(); 
    if(elapsedTime >=hitRate){
            Projectile *projectile = new Projectile(pos.x,pos.y, speed, projAddress);
            projectiles.push_back(projectile);
            return projectile;
    }
    return nullptr;
}

void Plant :: deleteOutOfBound(Vector2u windowSize)
{
    for(auto projectile : projectiles){
        if(projectile->isOut(windowSize)){
            projTrash.push_back(projectile);
        }
    }
    projectiles.erase(remove_if(projectiles.begin(), projectiles.end(), [windowSize](Projectile* projectile) {
        return projectile->isOut(windowSize);}), projectiles.end());

    for(auto projectile : projTrash) {
        delete projectile;
    }
    projTrash.clear();
}

bool Plant :: checkProjCollision(FloatRect zombieBound)
{
    for(auto projectile : projectiles)
    {
        FloatRect bounds = projectile->getBound();
        if(bounds.intersects(zombieBound)){
                projectile->Delete();
                projTrash.push_back(projectile);
                deleteProjCollision();
                return true;
        }
    }
    return false;
}

bool Plant :: checkPlantCollision(FloatRect zombieBound)
{
    FloatRect bounds = getSpriteRect();
    if(bounds.intersects(zombieBound)){
            return  true;
    }
    return false;
}



void Plant :: deleteProjCollision(){
    projectiles.erase(remove_if(projectiles.begin(), projectiles.end(), [](Projectile* projectile)
                         { return projectile->isDelete(); }),projectiles.end());

    for (auto projectile : projTrash)
    {
        delete projectile;
    }
    projTrash.clear();
}

void Plant :: damage(){
        health -= 1;
}

void Plant :: dead()
{
    if  (health == 0){
        DeadOrNot = true;
    }
}

Sun* Plant :: addSun()
{
    float elapsedTime = sunClock.getElapsedTime().asSeconds();
    if((elapsedTime >= SUNFLOWER_SUN_RATE)){
            Sun *sun = new Sun(getCenter().x, getCenter().y);
            suns.push_back(sun);
            return sun;
    }
    return nullptr;
}



