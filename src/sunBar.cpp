#include "../include/sunBar.hpp"


SunBar :: SunBar(int x, int y, int v, string address)
{
    if (!texture.loadFromFile(PICS_PATH + address)){return;}
    if (!font.loadFromFile(FONTS_PATH + "HouseofTerror.ttf")) {return;}
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

void SunBar :: update(int plusMinus)
{
    value+=plusMinus;
    stringstream ss;
    ss << value;
    string numberString = ss.str();
    text.setString(numberString);
}

