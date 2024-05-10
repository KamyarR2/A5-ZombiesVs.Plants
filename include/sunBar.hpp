#include "global.hpp"


class SunBar{
    
public:
    SunBar(int x, int y, int v, string address);
    ~SunBar();
    void render(RenderWindow &window);
    void update();
private:
    Texture texture;
    Sprite sprite;
    int value;
    string address;
    Font font;
    Text text;
};