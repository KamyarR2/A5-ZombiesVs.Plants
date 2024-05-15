#include "../include/handleZombie.hpp"


HandleZombie :: HandleZombie()
{
    clock.restart();   
    addClock.restart();
    gameClock.restart();
}
HandleZombie :: ~HandleZombie(){}



void HandleZombie :: addZombie(RenderWindow &window)
{
        float elapsedTime = clock.getElapsedTime().asSeconds();   
        
        if((ATTACK_STAGES - trackStage) == 0)
            return;
        if((elapsedTime >= (ATTACK_STAGES - trackStage)*4)){
            int xZombie = window.getSize().x;
            int randomRow = rand() % ROW_NUM;
            int yZombie = downRight[1] - (randomRow * stepVertical);



            int randomIndex = rand() % ZOMBIES_ADDRESS.size();
            if(ZOMBIES_ADDRESS[randomIndex] == GIANT_ADDRESS)
            {
                Zombie *zombie = new Zombie(xZombie,yZombie, GIANT_SPEED, GIANT_HEALTH, GIANT_DAMAGE, GIANT_ADDRESS);
                zombies.push_back(zombie);
            }
            else if(ZOMBIES_ADDRESS[randomIndex] == ZOMBIE_ADDRESS)
            {
                Zombie *zombie = new Zombie(xZombie,yZombie, ZOMBIE_SPEED, ZOMBIE_HEALTH, ZOMBIE_DAMAGE, ZOMBIE_ADDRESS);
                zombies.push_back(zombie);
            }

            clock.restart(); 
        }
}


void HandleZombie :: render(RenderWindow &window)
{
    for(auto zombie : zombies)
    {

        zombie->render(window);
    }
}


void HandleZombie :: update()
{
    float elapsedTime = addClock.getElapsedTime().asSeconds();
    if(elapsedTime >= ATTACK_TIME_STEPS && abs(ATTACK_STAGES - trackStage) > 0)
    {
        addClock.restart();
        trackStage++;
    }
    for(auto zombie : zombies)
    {
        zombie->update();
    }
}


bool HandleZombie :: checkGameOver()
{
    vector <Zombie*> zombieTrash;

    for(auto zombie : zombies){
        if(zombie->isOut()){
            zombieTrash.push_back(zombie);
            return true;
        }
    }
    return false;
}

bool HandleZombie :: checkWin()
{
    float elapsedTime = gameClock.getElapsedTime().asSeconds(); 
    if(zombies.size() == 0 && elapsedTime > ATTACK_TIME)
        return true;
    return false;
}





void HandleZombie :: deleteCollision(vector<Plant*> &plants)
{   
    vector <Plant*> plantTrash;
    vector <Zombie*> zombieTrash;
    for(auto zombie : zombies)
    {
        
        for(auto plant : plants)
        {
            
            FloatRect zombieBound = zombie->getInnerRect();
            if(plant->checkProjCollision(zombieBound) && plant->isPlanted())
            {   
                if (plant->getProjAddress() == "Icepea.png"){
                    zombie->freeze();
                    zombie->iceDamaged();
                }
                else{
                    zombie->damage();
                }
                if (zombie->isDead()){
                        zombieTrash.push_back(zombie);
                }
            }
            if(plant->checkPlantCollision(zombieBound) && !plant->isDead() && plant->isPlanted())
            {   
                zombie->stop();
                plant->damage();
                plant->dead();
                
            }
            if (plant->isDead()){
                    zombie->move();
                    plantTrash.push_back(plant);
                }
        }
    }
    
    zombies.erase(remove_if(zombies.begin(), zombies.end(), [](Zombie* zombie) {
        return zombie->isDead();}), zombies.end());

    for(auto zombie : zombieTrash) {
        delete zombie;
    }
    zombieTrash.clear();

    plants.erase(remove_if(plants.begin(), plants.end(), [](Plant* plant) {
        return plant->isDead();}), plants.end());
}

void HandleZombie ::  clocksRestart()
{
    clock.restart();   
    addClock.restart();
    gameClock.restart();
}