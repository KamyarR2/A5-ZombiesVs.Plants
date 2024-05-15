#include "../include/handler.hpp"

Handler ::Handler(Player *p)
{
    player = p;
    zombieHandler = new HandleZombie();
    clock.restart();
    sunBar = new SunBar(140, 0, INIT_SUN, "sunBar.png");
    seedCards.push_back(new SeedCard(0, 0, SNOWPEA_PRICE, SNOWPEA_COOL_TIME, SNOWPEA_HEALTH, SNOWPEA_DAMAGE, SNOWPEA_SPEED, SNOWPEA_HIT_RATE, "SnowPea.png", "SnowPeaGray.png","Snowpea.png", "Icepea.png"));
    seedCards.push_back(new SeedCard(0, 80, SUNFLOWER_PRICE, SUNFLOWER_COOL_TIME, SUNFLOWER_HEALTH, SUNFLOWER_DAMAGE, SUNFLOWER_SPEED, SUNFLOWER_HIT_RATE, "Sunflower.png", "SunflowerGray.png", "Sunflower.png"));
    seedCards.push_back(new SeedCard(0, 2 * 80, WALLNUT_PRICE, WALLNUT_COOL_TIME, WALLNUT_HEALTH, WALLNUT_DAMAGE, WALLNUT_SPEED, WALLNUT_HIT_RATE, "Wallnut.png", "WallnutGray.png", "Wallnut.png"));
    seedCards.push_back(new SeedCard(0, 3 * 80, PEA_PRICE, PEA_COOL_TIME, PEA_HEALTH, PEA_DAMAGE, PEA_SPEED, PEA_HIT_RATE,"peashooter.png", "peashooterGray.png", "peashooter.png", "Pea.png"));
    seedCards.push_back(new SeedCard(0, 4 * 80, MELONPULT_PRICE, MELONPULT_COOL_TIME, MELON_HEALTH, MELON_DAMAGE, MELON_SPEED, MELON_HIT_RATE,"MelonPult.png", "MelonPultGray.png", "Melonpult.png"));

    for(int j=0; j<COL_NUM; j++){
        for(int i=0; i<ROW_NUM; i++){
            auto xPos = stepHorizontal*j+topLeft[0];
            auto yPos = stepVertical*i+topLeft[1];
            Vector2f position(static_cast<float>(xPos), static_cast<float>(yPos));
            Vector2f size(static_cast<float>(stepHorizontal), static_cast<float>(stepVertical));
            FloatRect rect(position, size);
            tiles.push_back(new Tile(rect));           
        }
    }
}

Handler ::~Handler()
{
    for (auto sun : suns)
    {
        delete sun;
    }
    for (auto plant : plants)
    {
        delete plant;
    }
}

void Handler :: update(RenderWindow &window)
{
    unlockPlant();

    Vector2i pos = Mouse ::getPosition(window);

    for(auto tile : tiles)
    {
        tile->update();
    }
    
    for (auto sun : suns)
    {
        sun->update();
    }
    zombieHandler->addZombie(window);
    zombieHandler->update();

    for(auto seedCard : seedCards)
    {
        seedCard->update();
    }
    for(auto plant : plants)
    {
        if(!plant->isDead() && plant->isPlanted() && plant->canShoot()){
            FloatRect bounds = plant->getSpriteRect();
            Vector2f pos = {bounds.left + bounds. width, bounds.top};
            Projectile* projectile = plant->addProjectile(pos, plant->getProjAddress());
            if(projectile != nullptr)
            {
                plant->resetClock();
            }
        }

        
        else if(plant->isFlower() && plant->isPlanted())
        {
                Sun *sun = plant->addSun();
                if(sun != nullptr)
                {
                    suns.push_back(sun);
                    plant->resetSunClock();
                }
        }
        plant->update(pos);
    }


    
    if(zombieHandler->checkGameOver())
        gameOver = true;
    if(zombieHandler->checkWin())
        win = true;
    addSun();
    deleteOutOfBound(window);
    deleteIsClicked();
    handleCollision();
}


void Handler :: addSun()
{
    float xSun = std::rand() % (downRight[0] - topLeft[0]);
    float ySun = 0;
    float elapsedTime = clock.getElapsedTime().asSeconds();   
    if((elapsedTime >= SYSTEM_SUN_RATE)){
            Sun *sun = new Sun(xSun, ySun);
            suns.push_back(sun);
            clock.restart();
        }
}

void Handler :: render(RenderWindow &window)
{
    for (auto seedCard : seedCards)
    {
        seedCard->render(window);
    }
    for(auto plant : plants)
    {
        plant->render(window);
    }
    for(auto tile : tiles)
    {
        tile->render();
    }
    sunBar->render(window);

    for (auto sun : suns)
    {
        sun->render(window);
    }
    zombieHandler->render(window);
}

void Handler :: handleMousePressed(Vector2i pos)
{
    for (auto sun : suns)
    {
        if (sun->contains(pos))
        {
            sun->clicked();
            sunBar->update(SUN_VALUE);
        }
    }

    for (auto seedCard : seedCards)
    {
        if (seedCard->contains(pos) && !seedCard->isLocked() && !seedCard->isCoolDown())
        {
                selectedSeedCard = seedCard;
                addPlant(pos ,seedCard->getValue(), seedCard->getHealth(), seedCard->getDamage(), 
                        seedCard->getSpeed(), seedCard->getHitRate(), seedCard->getPlantAdress(), 
                        seedCard->getProjAddress());
        }
    }
}

void Handler ::handleMouseReleased()
{
    vector <Plant*> trash;
    for (auto plant : plants)
    {
        for(auto tile : tiles){

            if(tile->isInside(plant->getSpriteRect()) && !tile->isPlanted()){
                tile->seed(plant);
                plant->stopDrag(tile->tileCenter());
                plant->planted();
                sunBar->update(-plant->getValue());
                selectedSeedCard->resetClock();
                plant->letSeedCardKnow(selectedSeedCard);
                selectedSeedCard = nullptr; 
                break;
            }
        }
        if(!plant->isPlanted())
            trash.push_back(plant);
    }
    

    for (auto plant : trash)
    {
        plants.erase(remove_if(plants.begin(), plants.end(), [](Plant *plant)
                         {return !plant->isPlanted();}),
               plants.end());
        delete plant;
    }
}

void Handler ::deleteOutOfBound(RenderWindow &window)
{
    vector<Sun *> trash;
    auto windowSize = window.getSize();
    for (auto sun : suns)
    {
        if (sun->isOut(windowSize))
        {
            trash.push_back(sun);
        }
    }

    suns.erase(remove_if(suns.begin(), suns.end(), [windowSize](Sun *sun)
                         { return sun->isOut(windowSize); }),
               suns.end());

    for (auto sun : trash)
    {
        delete sun;
    }
    for(auto plant : plants)
    {
        plant->deleteOutOfBound(windowSize);
    }
    
}

void Handler ::deleteIsClicked()
{
    vector<Sun*> trash;
    for (auto sun : suns)
    {
        if (sun->isClicked())
        {
            trash.push_back(sun);
        }
    }

    suns.erase(remove_if(suns.begin(), suns.end(), [](Sun *sun)
                         { return sun->isClicked(); }),
               suns.end());

    for (auto sun : trash)
    {
        delete sun;
    }
}

void Handler ::unlockPlant()
{
    for (auto seedCard : seedCards)
    {
        int money = sunBar->sunMoney();
        seedCard->checkAndUnlock(money);
    }
}


void Handler :: addPlant(Vector2i pos, float value, float health, float damage, float speed, float hitRate, string address, string projAddress)
{
    Vector2f mousePos = {static_cast<float>(pos.x), static_cast<float>(pos.y)};
    Plant *plant = new Plant(mousePos.x, mousePos.y, value, health, damage, speed, hitRate, address, projAddress);
    plant -> startDrag();
    plants.push_back(plant);
}


void Handler :: handleCollision()
{
    zombieHandler->deleteCollision(plants);
}

