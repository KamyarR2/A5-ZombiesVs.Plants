#include "../include/sunBar.hpp"


SunBar :: SunBar(int x, int y, int v, string address)
{
    if (!texture.loadFromFile("../Pics/"+address)){return;}
    if (!font.loadFromFile("../Fonts/HouseofTerror.ttf")) {return;}
    value = v;
    sprite.setTexture(texture);
    sprite.setPosition(x,y);
    text.setPosition(texture.getSize().x/2 + x,texture.getSize().y/10);
    text.setFont(font);
    text.setCharacterSize(48);
    text.setFillColor(Color::Black);

    stringstream ss;
    ss << value;
    string numberString = ss.str();
    text.setString(numberString);

}

SunBar :: ~SunBar(){}

void SunBar :: render(RenderWindow &window)
{
    window.draw(sprite);
    window.draw(text);

}

void SunBar :: update()
{
    value+=10;
    stringstream ss;
    ss << value;
    string numberString = ss.str();
    text.setString(numberString);
}

