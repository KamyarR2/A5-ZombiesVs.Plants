#include "global.hpp"



class Sun
{
public:
    Sun(int x, int y);
    ~Sun();
    void render(RenderWindow &window);
    void update();
    FloatRect getBound(){return sprite.getGlobalBounds();}
    bool isClicked = false;
    bool isOut(Vector2u windowSize);

private:
    float const speed = 1;
    Texture texture;
    Sprite sprite;
    Vector2f pos;
};