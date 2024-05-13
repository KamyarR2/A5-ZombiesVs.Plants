#include "../include/plant.hpp"


Plant :: Plant(int x, int y, string address, int v, string projA)
{
    projAddress = projA;
    if(!projA.empty()){
        hasProjectile = true;
    }

    // cout << hasProjectile <<endl;
    if (!texture.loadFromFile("../Pics/Plants/"+address)){return;}

    sprite.setScale(0.15,0.15);
    sprite.setTexture(texture);
    sprite.setPosition(x,y);
    value = v;
}

Plant :: ~Plant(){}



void Plant :: render(RenderWindow &window)
{
    FloatRect bounds = sprite.getGlobalBounds();
    sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
    rect.setPosition(bounds.left, bounds.top);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Red); 
    rect.setOutlineThickness(2);
    //window.draw(rect);
    // Vector2i mousepose = Mouse :: getPosition(window);
    
    window.draw(sprite);

}
void Plant :: update(Vector2i pos)
{
    if(isDragging()){
        Vector2f mousePos = {static_cast<float>(pos.x), static_cast<float>(pos.y)};
        sprite.setPosition({mousePos.x-sprite.getGlobalBounds().width/2, mousePos.y-sprite.getGlobalBounds().height/2});
    }
    for(auto projectile : projectiles)
    {
        projectile->update();
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
