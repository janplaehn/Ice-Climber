#pragma once

class GameSettings {

public:

	const static unsigned int	MAX_NUM_GAME_OBJECTS;
	const static unsigned int	NUM_LIVES;
		 
	const static unsigned int	MAX_NUM_ROCKETS;
	const static unsigned int	MAX_NUM_BOMBS;
	const static unsigned int	POINTS_PER_ALIEN;
	const static float			FIRE_TIME_INTERVAL;
	const static float			BOMB_TIME_INTERVAL;
	const static float			PLAYER_SPEED;
	const static float			ROCKET_SPEED;
	const static float			ALIEN_SPEED;
	const static float			BOMB_SPEED;
	const static int			ALIEN_COLUMNS;
	const static int			ALIEN_ROWS;
	const static float			TIME_ACCELERATOR;

	static float time_multiplier;	// speed of the game; it is increased each time all the aliens are hit 
										// it is also the score multiplier

};