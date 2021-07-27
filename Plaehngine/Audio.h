#pragma once
#include <string>
#include <SDL_mixer.h>

class Game;

class Audio
{
public:
	static void Init(Game* game);

	//Load WAVE, AIFF, RIFF, OGG, and VOC files and store them as Music or Chunks (i.e. Sounds)
	static Mix_Chunk* LoadSound(std::string path);

	//Returns the channel
	static int PlayAndGetChannel(Mix_Chunk* sound, bool shouldLoop);

	static void Quit();

private:
	static Game* _game;
};

