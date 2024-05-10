#include "../include/system.hpp"

System :: System(int width, int height, int frameRate){
    window.create(VideoMode(width,height),"PvZ", Style::Close);
    window.setFramerateLimit(frameRate);
    window.setMouseCursorVisible(false);
    if (!backgroundTexture.loadFromFile("../Pics/Map.png"))
        {
            return;
        }
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
        render();
        update();
        handleEvents();
    }
}

void System :: render()
{
    window.clear();
    window.draw(backgroundSprite);
    handler->render(window);
    player->render(window);
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
