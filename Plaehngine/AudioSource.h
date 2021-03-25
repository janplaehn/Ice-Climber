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
	virtual void Update() {};
	virtual void Destroy();

	bool _isLooping = false;
	Mix_Chunk* _clip;

private:
	float _volume = MIX_MAX_VOLUME / 2;
	int _channel = -1;

public:
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this));
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(AudioSource, "AudioSource")
CEREAL_REGISTER_POLYMORPHIC_RELATION(AudioSource, Component)