#include "../include/seedCards.hpp"



SeedCard :: SeedCard(int x, int y, float v, float ct, float h, float d, float s, float hrate, string address, string grayAddress, string plantA, string projA)
{
    coolDownTime = ct;
    plantAddress  = plantA;
    projAddress = projA;
    value = v;
    health = h;
    damage = d;
    speed = s;
    hitRate = hrate;
    

    if (!texture.loadFromFile(PICS_PATH + "SeedPackets/"+address)){return;}
    
    sprite.setScale(0.5,0.5);
    sprite.setTexture(texture);
    sprite.setPosition(x,y);

    if (!grayTexture.loadFromFile(PICS_PATH + "SeedPackets/"+grayAddress)){return;}
    
    graySprite.setScale(0.5,0.5);
    graySprite.setTexture(grayTexture);
    graySprite.setPosition(x,y);

    if (!font.loadFromFile(FONTS_PATH + "HouseofTerror.ttf")) {return;}
    text.setPosition(sprite.getPosition().x+texture.getSize().x/3.3,sprite.getPosition().y+texture.getSize().y/4);
    text.setFont(font);
    text.setCharacterSize(32);
    text.setFillColor(Color::Black);

    stringstream ss;
    ss << value;
    string numberString = ss.str();
    text.setString(numberString);


    timeText.setPosition(sprite.getPosition().x,sprite.getPosition().y);
    timeText.setFont(font);
    timeText.setCharacterSize(25);
    timeText.setFillColor(Color::Yellow);

    stringstream ssTime;
    ssTime << fixed <<setprecision(1) <<coolDownTime - elapsedTime;
    string timeString = ssTime.str();
    timeText.setString(timeString);

}

SeedCard :: ~SeedCard(){}

void SeedCard :: render(RenderWindow &window)
{

    if(isLocked()){
        window.draw(graySprite);
        window.draw(text);
    }

    else if (coolDown)
    {
        stringstream ssTime;
        ssTime << fixed << setprecision(1) << coolDownTime - elapsedTime;
        string timeString = ssTime.str();
        timeText.setString(timeString);
        window.draw(graySprite);
        window.draw(timeText);
        window.draw(text);
    }
    else{
        window.draw(sprite);
        window.draw(text);
    }
}

void SeedCard :: update()
{
    if(coolDown){
        elapsedTime = clock.getElapsedTime().asSeconds(); 
        if(elapsedTime >= coolDownTime)
            coolDown = false;
    } 
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

void SeedCard :: resetClock()
{
    clock.restart();
    elapsedTime = 0;
}



