#pragma once
#include "Component.h"
#include "Audio.h"


class AudioSource : public Component
{
public:
	AudioSource(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

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

	bool _isLooping = false;
	Mix_Chunk* _clip;

private:
	float _volume = MIX_MAX_VOLUME / 2;
	int _channel = -1;

	~AudioSource();
};

