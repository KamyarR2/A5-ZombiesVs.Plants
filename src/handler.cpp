#include "../include/handler.hpp"

Handler ::Handler(Player *p)
{
    player = p;
    sunBar = new SunBar(140, 0, 1000, "sunBar.png");
    seedCards.push_back(new SeedCard(0, 0, 120, "SnowPea.png", "SnowPeaGray.png","Snowpea.png", "Icepea.png"));
    seedCards.push_back(new SeedCard(0, 80, 50, "Sunflower.png", "SunflowerGray.png", "Sunflower.png"));
    seedCards.push_back(new SeedCard(0, 2 * 80, 50, "Wallnut.png", "WallnutGray.png", "Wallnut.png"));
    seedCards.push_back(new SeedCard(0, 3 * 80, 100, "peashooter.png", "peashooterGray.png", "peashooter.png", "Pea.png"));
    seedCards.push_back(new SeedCard(0, 4 * 80, 100, "MelonPult.png", "MelonPultGray.png", "Melonpult.png"));

    for(int j=0; j<COL_NUM; j++){
        for(int i=0; i<ROW_NUM; i++){
            auto xPos = stepHorizontal*j+topLeft[0];
            auto yPos = stepVertical*i+topLeft[1];
            // cout << xPos << " " << yPos<<endl;
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
    clock++;
    unlockPlant();

    Vector2i pos = Mouse ::getPosition(window);
    

    for (auto sun : suns)
    {
        sun->update();
    }
    for(auto zombie : zombies)
    {
        zombie->update();
    }
    for(auto projectile : projectiles)
    {
        projectile->update();
    }
    for(auto plant : plants)
    {
        if(!plant->isAlive() && plant->isPlanted() && plant->canShoot()){
            FloatRect bounds = plant->getSpriteRect();
            Vector2f pos = {bounds.left + bounds. width, bounds.top};
            addProjectile(window, pos, plant->getProjAddress());
        }
        plant->update(pos);
    }

    checkGameOver();
    addZombie(window);
    addSun(window);
    deleteOutOfBound(window);
    deleteIsClicked(window);
    handlerCollision(window);
}

void Handler :: addProjectile(RenderWindow &window, Vector2f pos, string address)
{
        if(clock%60 == 0){
            int time = clock/60;
            if((time%4) == 0){
                Projectile *projectile = new Projectile(pos.x,pos.y, address);
                projectiles.push_back(projectile);
            }
        }
    }




void Handler :: addZombie(RenderWindow &window)
{
    if(clock% 60 == 0){
        time = clock/60;
        if((time % 3) == 0){
            int xZombie = window.getSize().x;
            int randomRow = rand() % 5;
            int yZombie = downRight[1] - ((randomRow) * stepVertical);
            Zombie *zombie = new Zombie(xZombie,yZombie,"Giant.png");
            zombies.push_back(zombie);
        }
    }
}

void Handler ::addSun(RenderWindow &window)
{
    if (clock % 60 == 0)
    {
        time = clock / 60;
        if ((time % 4) == 0)
        {
            int xSun = std::rand() % window.getSize().x;
            int ySun = 0;
            Sun *sun = new Sun(xSun, ySun);
            suns.push_back(sun);
        }
    }
}

void Handler ::render(RenderWindow &window)
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
        tile->render(window);
    }
    sunBar->render(window);
    for (auto zombie : zombies)
    {
        zombie->render(window);
    }
    for (auto sun : suns)
    {
        sun->render(window);
    }
    for(auto projectile : projectiles)
    {
        projectile->render(window);
    }
}

void Handler :: handleMousePressed(Vector2i pos)
{
    for (auto sun : suns)
    {
        if (sun->contains(pos))
        {
            sun->clicked();
            sunBar->update(+10);
        }
    }

    for (auto seedCard : seedCards)
    {
        if (seedCard->contains(pos) && !seedCard->isLocked())
        {
                // cout << seedCard->getProjAddress() <<endl;
                addPlant(pos, seedCard->getPlantAdress(), seedCard->getValue(), seedCard->getProjAddress());
        }
    }
}

void Handler ::handleMouseReleased(Vector2i pos)
{
    vector <Plant*> trash;
    for (auto plant : plants)
    {
        for(auto tile : tiles){
            if(tile->isInside(plant->getSpriteRect()) && !tile->isPlanted()){
                plant->stopDrag(tile->tileCenter());
                tile->seed();
                plant->planted();
                sunBar->update(-plant->getValue());
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

    vector <Projectile*> ProjTrash;

    for(auto projectile : projectiles){
        if(projectile->isOut(windowSize)){
            ProjTrash.push_back(projectile);
        }
    }
    projectiles.erase(remove_if(projectiles.begin(), projectiles.end(), [windowSize](Projectile* projectile) {
        return projectile->isOut(windowSize);}), projectiles.end());

    for(auto projectile : ProjTrash) {
        delete projectile;
    }
}

void Handler :: checkGameOver()
{
    vector <Zombie*> zombieTrash;

    for(auto zombie : zombies){
        if(zombie->isOut()){
            gameOver = true;
            zombieTrash.push_back(zombie);
        }
    }
    zombies.erase(remove_if(zombies.begin(), zombies.end(), [](Zombie* zombie) {
        return zombie->isOut();}), zombies.end());

    for(auto zombie : zombieTrash) {
        delete zombie;
    }

}

void Handler ::deleteIsClicked(RenderWindow &window)
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


void Handler :: addPlant(Vector2i pos, string address, int value, string projAddress)
{
    // cout << projAddress.empty()<<endl;
    Vector2f mousePos = {static_cast<float>(pos.x), static_cast<float>(pos.y)};
    Plant *plant = new Plant(mousePos.x, mousePos.y, address, value, projAddress);
    plant -> startDrag();
    plants.push_back(plant);
}

void Handler :: handlerCollision(RenderWindow &window){
    vector <Projectile*> trashProj;
    vector <Zombie*> trashZombie;
    for (auto zombie : zombies){
        for (auto projectile:projectiles){
            FloatRect projBound = projectile->getBound();
            FloatRect zombieBound = zombie->getInnerRect();
            if(projBound.intersects(zombieBound)){
                projectile->Delete();
                trashProj.push_back(projectile);
                zombie->Delete();
                trashZombie.push_back(zombie);
            }
        }
    }
    projectiles.erase(remove_if(projectiles.begin(), projectiles.end(), [](Projectile *projectile)
                         { return projectile->isDelete(); }),projectiles.end());

    for (auto projectile : trashProj)
    {
        delete projectile;
    }
    zombies.erase(remove_if(zombies.begin(), zombies.end(), [](Zombie *zombie)
                         { return zombie->isDelete(); }),zombies.end());

    for (auto zombie : trashZombie)
    {
        delete zombie;
    }
}

