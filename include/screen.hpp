#include "global.hpp"


class Screen
{

public:
    Screen(string i, string m);
    ~Screen();
    void render(RenderWindow &window);
    void update();
    bool startPressed(Vector2i pos);
    void stopMusic(){screenMusic.stop();}
    void startMusic(){screenMusic.play();}
private:
    Sprite screenSprite;
    Texture screenTexture;
    Music screenMusic;
    string imageAddress;
    string musicAddress;
};