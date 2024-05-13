#include "../include/system.hpp"

System :: System(int width, int height, int frameRate){
    window.create(VideoMode(width,height),"PvZ", Style::Close);
    window.setFramerateLimit(frameRate);
    window.setMouseCursorVisible(false);
    if (!backgroundTexture.loadFromFile("../Pics/Map.png"))
        {
            return;
        }
    if (!gameOverTexture.loadFromFile("../Pics/GameOver.png"))
        {
            return;
        }
    
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition((topLeft[0] + downRight[0])/3, (topLeft[1] + downRight[1])/5);

    backgroundSprite.setTexture(backgroundTexture);


    player = new Player(Mouse::getPosition().x, Mouse::getPosition().y);
    handler = new Handler(player);
    state = IN_GAME;
}

System :: ~System(){
    delete player;
    delete handler;
}


void System :: run(){
    while (window.isOpen() && state != EXIT)
    {
        update();
        handleEvents();
        render();
    }
}

void System :: render()
{
    window.clear();
    window.draw(backgroundSprite);

    handler->render(window);
    player->render(window);
    if(handler->isGameOver()){
        window.draw(gameOverSprite);
        backgroundSprite.setColor(grey);
        state = EXIT;
    }
    window.display();
}

void System :: update()
{
    Vector2i mousePosition = Mouse::getPosition(window);
    handler->update(window);
    player->update(mousePosition);
}

void System :: handleEvents()
{
    Event event;

    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case Event::Closed:
                state = EXIT;
                window.close();
                break;

            case Event::MouseButtonPressed:
                handleMousePressed(event);
                break;

            case Event::MouseButtonReleased:
                handleMouseReleased(event);
                break;
            default:
                break;
        }
    }
}

void System :: handleMousePressed(Event event)
{
    if(event.mouseButton.button == Mouse::Right)
        return;
    Vector2i pos  = {event.mouseButton.x, event.mouseButton.y};
    switch(state){
        case(IN_GAME):
            handler -> handleMousePressed(pos);
            break;
        case(EXIT):
            break;
    }

}

void System :: handleMouseReleased(Event event)
{
    if(event.mouseButton.button == Mouse::Right)
        return;
    Vector2i pos  = {event.mouseButton.x, event.mouseButton.y};
    switch(state){
        case(IN_GAME):
            handler -> handleMouseReleased(pos);
            break;
        case(EXIT):
            break;
    }
}
