#include "global.hpp"
#include "player.hpp"
#include "sun.hpp"
#include "sunBar.hpp"
#include "plants.hpp"

class Handler
{

public:
    Handler(Player *player);
    ~Handler();
    void update(RenderWindow &window);
    void render(RenderWindow &window);
    void handleMousePressed(Vector2i pos);
    void handleMouseReleased(Vector2i pos);
private:
    Player *player;
    vector <Sun*> suns;
    vector <Plants*> plants;
    SunBar *sunBar;
    void deleteOutOfBound(RenderWindow &window);
    void deleteIsClicked(RenderWindow &window);
    void addSun(RenderWindow &window);
    int clock = 0;
    int time = 0;
};