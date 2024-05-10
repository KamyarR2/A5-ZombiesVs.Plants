#include "../include/handler.hpp"



Handler :: Handler(Player *p)
{
    player = p;
    sunBar =  new SunBar(140, 0, 10, "sunBar.png");
    plants.push_back(new Plants(0, 0, 120, "SnowPea.png"));
    plants.push_back(new Plants(0, 80, 50, "Sunflower.png"));
    plants.push_back(new Plants(0, 160, 50, "Wallnut.png"));
    plants.push_back(new Plants(0, 3*80, 100, "peashooter.png"));
}

Handler :: ~Handler()
{
    for (auto sun : suns){
        delete sun;
    }
}

void Handler :: update(RenderWindow &window)
{
    clock++;
    for(auto sun : suns){
        sun->update();
    }
    addSun(window);
    deleteOutOfBound(window);
    deleteIsClicked(window);
}

void Handler :: addSun(RenderWindow &window)
{
    if(clock%60 == 0){
        time = clock/60;
        if((time%4) == 0){
            int xSun = std::rand() % window.getSize().x;
            int ySun = 0;
            Sun *sun = new Sun(xSun,ySun);
            suns.push_back(sun);
        }
    }
}


void Handler :: render(RenderWindow &window)
{
    for(auto sun : suns){
        sun->render(window);
    }
    for(auto plant : plants){
        plant->render(window);
    }
    sunBar->render(window);
    
}

void Handler :: handleMousePressed(Vector2i pos)
{   
    for(auto sun : suns){
       FloatRect bounds = sun->getBound(); 
       if (pos.x >= bounds.left && pos.y >= bounds.top &&
                    pos.x <= (bounds.left + bounds.width) &&
                    pos.y <= (bounds.top + bounds.height)) 
        {
                    sun->isClicked = true;
                    sunBar->update();
        }
    }

    for(auto plant:plants){
    FloatRect bounds = plant->getBound();
    if (pos.x >= bounds.left && pos.y >= bounds.top &&
                    pos.x <= (bounds.left + bounds.width) &&
                    pos.y <= (bounds.top + bounds.height)) {
                    plant->isDragged = true;
                    for(auto plant : plants){
                    plant->update(pos);
                }          
    }
    }
}


void Handler :: handleMouseReleased(Vector2i pos)
{   
    for(auto plant:plants){
        plant->isDragged = false;
    }
}

void Handler :: deleteOutOfBound(RenderWindow &window)
{
    vector <Sun*> trash;
    auto windowSize = window.getSize();
    for(auto sun:suns){
        if(sun->isOut(windowSize)){
            trash.push_back(sun);
        }
    }

    suns.erase(remove_if(suns.begin(), suns.end(), [windowSize](Sun* sun) {
        return sun->isOut(windowSize);}), suns.end());

    for(auto sun : trash) {
        delete sun;
    }
}

void Handler :: deleteIsClicked(RenderWindow &window)
{
    vector <Sun*> trash;
    for(auto sun:suns){
        if(sun->isClicked){
            trash.push_back(sun);
        }
    }

    suns.erase(remove_if(suns.begin(), suns.end(), [](Sun* sun) {
        return sun->isClicked;}), suns.end());

    for(auto sun : trash) {
        delete sun;
    }
}