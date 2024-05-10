#include "../include/plants.hpp"



Plants :: Plants(int x, int y, int v, string address)
{
    if (!texture.loadFromFile("../Pics/SeedPackets/"+address)){return;}
    if (!font.loadFromFile("../Fonts/HouseofTerror.ttf")) {return;}
    value = v;
    sprite.setScale(0.5,0.5);
    sprite.setTexture(texture);
    sprite.setPosition(x,y);
    text.setPosition(sprite.getPosition().x+texture.getSize().x/3.2,sprite.getPosition().y+texture.getSize().y/4);
    text.setFont(font);
    text.setCharacterSize(32);
    text.setFillColor(Color::Black);

    stringstream ss;
    ss << value;
    string numberString = ss.str();
    text.setString(numberString);

}

Plants :: ~Plants(){}

void Plants :: render(RenderWindow &window)
{
    window.draw(sprite);
    window.draw(text);

}

void Plants :: update(Vector2i pos)
{
    FloatRect bounds = sprite.getGlobalBounds();
    if(isDragged){
        sprite.setPosition({sprite.getPosition().x+10, sprite.getPosition().x+10});
    }
}

