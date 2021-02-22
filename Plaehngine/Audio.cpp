#include "Audio.h"
#include <SDL_log.h>
#include <SDL_mixer.h>

void Audio::Init()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    Mix_AllocateChannels(10000);
}

Mix_Music* Audio::LoadMusic(std::string path)
{
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (music == NULL)
    {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    }
    return music;
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
    int loops = shouldLoop ? -1 : 0;
    return Mix_PlayChannel(-1, sound, loops);
}

void Audio::Quit()
{
    Mix_Quit();
}
