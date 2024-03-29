#include "Audio.h"
#include "Game.h"
#include <SDL_log.h>
#include <SDL_mixer.h>
#include "ApplicationState.h"

void Audio::Init(Game* game)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    Mix_AllocateChannels(10000);
}

Mix_Chunk* Audio::LoadSound(std::string path)
{
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (sound == NULL)
    {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    return sound;
}

int Audio::PlayAndGetChannel(Mix_Chunk* sound, bool shouldLoop)
{
    if (!ApplicationState::IsRunning()) {
        printf("Must not play sound effects in awake!");
        return -1;
    }
    int loops = shouldLoop ? -1 : 0;
    return Mix_PlayChannel(-1, sound, loops);
}

void Audio::Quit()
{
    Mix_Quit();
}
