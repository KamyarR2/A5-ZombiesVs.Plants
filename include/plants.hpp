#include "global.hpp"


class Plants{
    
public:
    Plants(int x, int y, int v, string address);
    ~Plants();
    void render(RenderWindow &window);
    FloatRect getBound(){return sprite.getGlobalBounds();}
    void update(Vector2i pos);
    bool isDragged = false;
private:
    Texture texture;
    Texture grayTexture;
    Sprite sprite;
    Sprite graySprite;
    int value;
    string address;
    Font font;
    Text text;
};