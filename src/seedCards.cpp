#include "../include/seedCards.hpp"



SeedCard :: SeedCard(int x, int y, int v, string address, string grayAddress, string plantA, string projA)
{
    if (!texture.loadFromFile("../Pics/SeedPackets/"+address)){return;}
    
    sprite.setScale(0.5,0.5);
    sprite.setTexture(texture);
    sprite.setPosition(x,y);

    if (!grayTexture.loadFromFile("../Pics/SeedPackets/"+grayAddress)){return;}
    
    graySprite.setScale(0.5,0.5);
    graySprite.setTexture(grayTexture);
    graySprite.setPosition(x,y);

    if (!font.loadFromFile("../Fonts/HouseofTerror.ttf")) {return;}
    value = v;
    text.setPosition(sprite.getPosition().x+texture.getSize().x/3.3,sprite.getPosition().y+texture.getSize().y/4);
    text.setFont(font);
    text.setCharacterSize(32);
    text.setFillColor(Color::Black);

    stringstream ss;
    ss << value;
    string numberString = ss.str();
    text.setString(numberString);
    plantAddress  = plantA;
    projAddress = projA;
}

SeedCard :: ~SeedCard(){}

void SeedCard :: render(RenderWindow &window)
{

    if(isLocked()){
        window.draw(graySprite);
        window.draw(text);
    }
    else{
        window.draw(sprite);
        window.draw(text);
    }
}

void SeedCard :: update(Vector2i pos)
{
}

bool SeedCard :: contains(Vector2i pos)
{
    FloatRect bounds = sprite.getGlobalBounds();
    return(pos.x >= bounds.left && pos.y >= bounds.top &&
                    pos.x <= (bounds.left + bounds.width) &&
                    pos.y <= (bounds.top + bounds.height));
}


void SeedCard :: checkAndUnlock(int sunMoney)
{
    if(sunMoney >= value)
        lockOrUnlock = false;
    else
        lockOrUnlock = true;
}

