#include "../include/tile.hpp"



Tile :: Tile(FloatRect rect)
{
    rectangle = rect;
}


void Tile :: seed()
{
    PlantedOrNot = true;
}

void Tile :: render(RenderWindow &window)
{
    RectangleShape rect(sf::Vector2f(rectangle.width, rectangle.height));
    rect.setPosition(rectangle.left, rectangle.top);
    rect.setFillColor(sf::Color::Transparent); 
    rect.setOutlineColor(sf::Color::Red); 
    rect.setOutlineThickness(2);

    //window.draw(rect);
}

bool Tile :: isInside(FloatRect plantRect)
{
    bool condition1 = rectangle.contains(plantRect.left, plantRect.top) && 
           rectangle.contains(plantRect.left + plantRect.width, plantRect.top) && 
           rectangle.contains(plantRect.left, plantRect.top + plantRect.height) && 
           rectangle.contains(plantRect.left + plantRect.width, plantRect.top + plantRect.height);

    float centerX = plantRect.left + plantRect.width/2;
    float centerY = plantRect.top + plantRect.height/2;

    Vector2f plantCenter = Vector2f(centerX, centerY);

    bool condition2 = rectangle.contains(plantCenter);
    return condition1 || condition2 ; 

}

Vector2f Tile :: tileCenter()
{
    float centerX = rectangle.left + rectangle.width/2;
    float centerY = rectangle.top + rectangle.height/2;

    Vector2f plantCenter = Vector2f(centerX, centerY);
    return plantCenter;
}
