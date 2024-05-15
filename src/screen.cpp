#include "../include/screen.hpp"


Screen :: Screen(string i, string m)
{
    cout << i<<endl;
    imageAddress = i;
    musicAddress = m;
    if (!screenTexture.loadFromFile(PICS_PATH + i))
    {
        return;
    }
    if (!screenMusic.openFromFile(MUSICS_PATH  + musicAddress))
    {
        return;
    }
    screenMusic.setLoop(true);
    screenSprite.setTexture(screenTexture);    
}

Screen :: ~Screen(){};

void Screen :: render(RenderWindow &window)
{
    if (screenMusic.getStatus() != SoundSource::Playing) {
        screenMusic.play();
    }
    window.clear();
    window.draw(screenSprite);
}

void Screen :: update()
{

}

bool Screen :: startPressed(Vector2i pos)
{
    if((pos.x > START_BAR_TOP[0] && pos.x < START_BAR_DOWN[0])
        &&(pos.y > START_BAR_TOP[1] && pos.y < START_BAR_DOWN[1]))
        {
            return true;
        }
    return false;
}

