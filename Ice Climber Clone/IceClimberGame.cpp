#include "IceClimbergame.h"
#include "player.h"
#include "Plaehngine.h"
#include "sprite.h"
#include "collideComponent.h"
#include <string>
#include <iomanip>
#include <sstream>
#include "Screen.h"
#include "Vector2D.h"
#include "Audio.h"
#include "AudioSource.h"
#include "Transform.h"
#include "Input.h"

void IceClimberGame::Create(class Plaehngine* engine)
{
	this->_engine = engine;

	player = new Player();
	PlayerBehaviourComponent* player_behaviour = player->AddComponent<PlayerBehaviourComponent>();
	RenderComponent* player_render = player->AddComponent<RenderComponent>();
	player_render->_sprite = Sprite::Create("Assets/Sprites/Characters/Popo/walk1.png");
	CollideComponent* player_collider = player->AddComponent<CollideComponent>();;
	AudioSource* player_audio = player->AddComponent<AudioSource>();
	player_audio->_clip = Audio::LoadSound("Assets/Sounds/sound.wav");

	player->Create(true);
	player->AddReceiver(this);
	_gameObjects.insert(player);

	life_sprite = Sprite::Create("data/player.bmp");
}

void IceClimberGame::Init()
{
	player->Init();

	_enabled = true;
}

void IceClimberGame::Update(float dt)
{
	if (!bIsRunning) return;

	Input::KeyStatus keys = Input::GetKeyStatus();
	if (keys._escape) {
		_engine->Quit();
	}

	for (auto go = _gameObjects.begin(); go != _gameObjects.end(); go++)
		(*go)->Update(dt);
}

void IceClimberGame::Draw()
{
	//Todo: UI->Draw();

	_engine->SwapBuffers();
	_engine->ClearWindow();
}

void IceClimberGame::Receive(Message m)
{
	if (m == GAME_OVER)
	{
		bIsRunning = false;
	}

}

void IceClimberGame::Destroy()
{
	for (auto go = _gameObjects.begin(); go != _gameObjects.end(); go++) {
		if ((*go) != nullptr) {
			(*go)->Destroy();
		}
	}

	life_sprite->Destroy();
	delete player;
}
