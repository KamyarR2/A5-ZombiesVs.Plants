#pragma once

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <filesystem>
#include <iomanip>


using namespace std;
using namespace sf;


const int GAME_DURATION = 100;
const int INIT_SUN = 150;
const int COL_NUM = 9;
const int ROW_NUM = 5;

const vector<int> topLeft = {247,60};
const vector<int> downRight = {1000,580};

const vector<int> START_BAR_TOP = {353,522};
const vector<int> START_BAR_DOWN = {1017,583};


const int stepHorizontal = abs(topLeft[0] - downRight[0]) / COL_NUM;
const int stepVertical = abs(topLeft[1] - downRight[1]) / ROW_NUM;

const int SUN_VALUE = 25;


const string PEASHOOTER = "peashooter";
const string SNOWPEASHOOTER = "snowPeashooter";
const string SUNFLOWER = "sunflower";
const string MELONPULT = "melonPult";
const string WALLNUT = "Wallnut";

const vector <string> types = {PEASHOOTER, SNOWPEASHOOTER, SUNFLOWER, MELONPULT, WALLNUT};

const Color grey(128, 128, 128);


const string PICS_PATH = "./Media/Pics/", FONTS_PATH = "./Media/Fonts/",
             MUSICS_PATH = "./Media/Musics/";




const int GIANT_HIT_POINT = 5;
const int ZOMBIE_HIT_POINT = 3;

const int FREEZE_TIME = 5;

const int SNOWPEA_COOL_TIME = 15, SUNFLOWER_COOL_TIME = 7.5, 
          PEA_COOL_TIME = 10, WALLNUT_COOL_TIME = 7.5,
          MELONPULT_COOL_TIME = 15;

const int SNOWPEA_PRICE = 120, SUNFLOWER_PRICE = 50, 
          PEA_PRICE = 100, WALLNUT_PRICE = 50, 
          MELONPULT_PRICE = 120; 

const int SNOWPEA_HEALTH = 200, SUNFLOWER_HEALTH = 100, 
          PEA_HEALTH = 150, WALLNUT_HEALTH = 130, 
          MELON_HEALTH = 150; 

const int SNOWPEA_DAMAGE = 3, SUNFLOWER_DAMAGE = 1, 
          PEA_DAMAGE = 1.5, WALLNUT_DAMAGE = 1, 
          MELON_DAMAGE = 1;

const int SNOWPEA_SPEED = 5, SUNFLOWER_SPEED = 0, 
          PEA_SPEED = 3, WALLNUT_SPEED = 0, 
          MELON_SPEED = 1;

const int SNOWPEA_HIT_RATE = 2, SUNFLOWER_HIT_RATE = 0, 
          PEA_HIT_RATE = 3, WALLNUT_HIT_RATE = 0, 
          MELON_HIT_RATE = 5;

const int SUNFLOWER_SUN_RATE = 12;
const int SYSTEM_SUN_RATE = 10;


const int ATTACK_TIME = 200;
const int ATTACK_STAGES = 5;
const int ATTACK_TIME_STEPS = 40;




const vector <string> ZOMBIES_ADDRESS = {"Giant.png", "Zombie.png"};
const string GIANT_ADDRESS = "Giant.png";
const string ZOMBIE_ADDRESS = "Zombie.png";

const float GIANT_HEALTH = 5, GIANT_DAMAGE = 1 ,GIANT_SPEED = 0.2 , GIANT_HIT_RATE = 2;
const float ZOMBIE_HEALTH = 5, ZOMBIE_DAMAGE = 1 ,ZOMBIE_SPEED = 0.3 , ZOMBIE_HIT_RATE = 2;





