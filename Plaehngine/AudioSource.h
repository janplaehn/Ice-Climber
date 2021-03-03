#pragma once
#include "Component.h"
#include "Audio.h"


class AudioSource : public Component
{
public:

	void Play();
	void Pause();
	void UnPause();
	void Stop();
	bool IsPaused();
	bool IsPlaying();
	float GetVolume();
	void SetVolume(float value);
	void OnFinishedPlaying(int channel);
	virtual void Update() {};
	virtual void Destroy();

	bool _isLooping = false;
	Mix_Chunk* _clip;

private:
	float _volume = MIX_MAX_VOLUME / 2;
	int _channel = -1;

	~AudioSource();
};

