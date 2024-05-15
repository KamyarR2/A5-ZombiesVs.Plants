#include "../include/system.hpp"

System :: System(int width, int height, int frameRate){
    window.create(VideoMode(width,height),"PvZ", Style::Close);
    window.setFramerateLimit(frameRate);
    window.setMouseCursorVisible(false);

    if (!gameOverTexture.loadFromFile(PICS_PATH + "GameOver.png"))
        {
            return;
        }
    
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition((topLeft[0] + downRight[0])/3, (topLeft[1] + downRight[1])/5);

    if (!winTexture.loadFromFile(PICS_PATH + "Win.png"))
        {
            return;
        }
    
    winSprite.setTexture(winTexture);
    winSprite.setScale(0.7,0.7);
    winSprite.setPosition((topLeft[0] + downRight[0])/6, (topLeft[1] + downRight[1])/5);

    player = new Player(Mouse::getPosition().x, Mouse::getPosition().y);
    handler = new Handler(player);
    menuScreen = new Screen("MainMenu.png","bg.ogg");
    gameScreen = new Screen("Map.png","In_Game.ogg");
    state = MENU;
}

System :: ~System(){
    delete player;
    delete handler;
}


void System :: run()
{
    while (window.isOpen() && state != EXIT)
    {   
        update();
        handleEvents();
        render(window);
    }
}

void System :: render(RenderWindow &window)
{
    window.clear();
    switch (state)
    {
    case(MENU):
        menuScreen->render(window);
        break;
    case(IN_GAME):
        menuScreen->stopMusic();
        gameScreen->render(window);
        handler->render(window);
        if(handler->isGameOver())
        {
            state = GAME_OVER;
        }
        if(handler->isWin())
        {
            state = WIN;
        }
        break;
    case(GAME_OVER):
        gameScreen->render(window);
        window.draw(gameOverSprite);
        backgroundSprite.setColor(grey);
        break;
    case(WIN):
        gameScreen->render(window);
        window.draw(winSprite);
        backgroundSprite.setColor(grey);
        break;
    case(EXIT):
        break;
    default:
        break;
    };
    player->render(window);
    window.display();
}

void System :: update()
{
    Vector2i mousePosition = Mouse::getPosition(window);
    if(state == IN_GAME)
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
        case(MENU) : 
            if(menuScreen->startPressed(pos))
                state = IN_GAME;
            break;
        case(IN_GAME):
            handler -> handleMousePressed(pos);
            break;
        case(GAME_OVER):
            state = MENU;
            gameScreen->stopMusic();
            break;
        case(WIN):
            state = MENU;
            gameScreen->stopMusic();
            break;
        case(EXIT):
            break;
    }

}

void System :: handleMouseReleased(Event event)
{
    if(event.mouseButton.button == Mouse::Right)
        return;
    switch(state){
        case(MENU):
            break;
        case(IN_GAME):
            handler -> handleMouseReleased();
            handler -> handleMouseReleased();
            break;
        case(GAME_OVER):
            break;
        case(WIN):
            break;
        case(EXIT):
            break;
    }
}
