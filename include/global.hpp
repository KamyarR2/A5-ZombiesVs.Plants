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


using namespace std;
using namespace sf;
// namespace fs = std::filesystem;
// using namespace fs;

const int COL_NUM = 9;
const int ROW_NUM = 5;

const vector<int> topLeft = {247,60};
const vector<int> downRight = {1000,580};

const int stepHorizontal = abs(topLeft[0] - downRight[0]) / COL_NUM;
const int stepVertical = abs(topLeft[1] - downRight[1]) / ROW_NUM;

const int sunValue = 10;
const int PeashooterCost = 100;
const int SnowPeaCost = 120;
const int MelonPultCost = 100;
const int SunflowerCost = 50;
const int WallnutCost = 50;

const string PEASHOOTER = "peashooter";
const string SNOWPEASHOOTER = "snowPeashooter";
const string SUNFLOWER = "sunflower";
const string MELONPULT = "melonPult";
const string WALLNUT = "Wallnut";

const vector <string> types = {PEASHOOTER, SNOWPEASHOOTER, SUNFLOWER, MELONPULT, WALLNUT};

const Color grey(128, 128, 128);

// const int PeashooterIdx = 0;
// const int SnowPeaIdx = 1;
// const int SunflowerIdx = 2;
// const int MelonPultIdx = 3;
// const int WallnutIdx = 4;


