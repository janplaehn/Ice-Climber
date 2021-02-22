#include "AudioSource.h"
#include "Audio.h"
#include <SDL_mixer.h>

void AudioSource::Play()
{
	if (_clip == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Cannot play clip because it is nullptr");
		return;
	}
	Mix_VolumeChunk(_clip, _volume);
	if (_isLooping) {
		if (IsPlaying()) {
			return;
		}
		if (IsPaused()) {
			UnPause();
			return;
		}
	}
	_channel = Audio::PlayAndGetChannel(_clip, _isLooping);
}

void AudioSource::Pause()
{
	if (Mix_GetChunk(_channel) == _clip) {
		Mix_Pause(_channel);
	}
}

void AudioSource::UnPause()
{
	if (Mix_GetChunk(_channel) == _clip) {
		Mix_Resume(_channel);
	}
}

void AudioSource::Stop()
{
	if (Mix_GetChunk(_channel) == _clip) {
		Mix_HaltChannel(_channel);
		_channel = -1;
	}
}

float AudioSource::GetVolume()
{
	return _volume;
}

void AudioSource::SetVolume(float value)
{
	_volume = value;
	Mix_VolumeChunk(_clip, _volume);
}

bool AudioSource::IsPaused()
{
	bool isPaused = false;
	if (_channel >= 0) {
		if (Mix_GetChunk(_channel) == _clip) {
			isPaused = Mix_Paused(_channel) > 0;
		}
	}
	return isPaused;
}

bool AudioSource::IsPlaying()
{
	bool isPlaying = false;
	if (_channel >= 0) {
		if (Mix_GetChunk(_channel) == _clip) {
			isPlaying = Mix_Playing(_channel) > 0 && !IsPaused();
		}
	}
	return isPlaying;
}

AudioSource::~AudioSource()
{
	if (_clip != nullptr) {
		Mix_FreeChunk(_clip);
	}
}