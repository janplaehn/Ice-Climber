#include "gameSettings.h"

const  unsigned int	GameSettings::MAX_NUM_GAME_OBJECTS = 10000;
const  unsigned int	GameSettings::NUM_LIVES = 2;

const  unsigned int	GameSettings::MAX_NUM_ROCKETS = 32;
const  unsigned int	GameSettings::MAX_NUM_BOMBS = 32;
const  unsigned int	GameSettings::POINTS_PER_ALIEN = 100;
const  float		GameSettings::FIRE_TIME_INTERVAL = .5f;
const  float		GameSettings::BOMB_TIME_INTERVAL = 1.25f;
const  float		GameSettings::PLAYER_SPEED = 160.0f;
const  float		GameSettings::ROCKET_SPEED = 160.0f;
const  float		GameSettings::ALIEN_SPEED = 40.0f;
const  float		GameSettings::BOMB_SPEED = 120.0f;
const int			GameSettings::ALIEN_COLUMNS = 11;
const int			GameSettings::ALIEN_ROWS = 5;
const   float		GameSettings::TIME_ACCELERATOR = 1.2f;

float GameSettings::time_multiplier = 1.f;