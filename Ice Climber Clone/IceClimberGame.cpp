#include "IceClimbergame.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "AABBCollider.h"
#include "Audio.h"
#include "AudioSource.h"
#include "PlayerBehaviour.h"
#include "Input.h"
#include "Transform.h"
#include <Rigidbody.h>

void IceClimberGame::Create(class Plaehngine* engine)
{
	this->_engine = engine;


	//Setup Background
	_background = new GameObject();
	SpriteRenderer* background_render = _background->AddComponent<SpriteRenderer>();
	background_render->_sprite = Sprite::Create("Assets/Sprites/Backgrounds/default.png");
	background_render->order = -100;
	_background->_transform->_position = Vector2D(Screen::WIDTH / 2, background_render->_sprite->GetHeight() / 2);


	//Setup background Music
	GameObject* music = new GameObject(false);
	AudioSource* musicSrc = music->AddComponent<AudioSource>();
	musicSrc->_clip = Audio::LoadSound("Assets/Music/stage.wav");
	musicSrc->_isLooping = true;
	musicSrc->Play();


	//Setup Player
	player = new GameObject();
	player->_transform->_pivot = Vector2D(0.5f, 1);
	player->_transform->_position.x = Screen::WIDTH / 2;
	player->_transform->_position.y = 36;
	PlayerBehaviour* player_behaviour = player->AddComponent<PlayerBehaviour>();
	SpriteRenderer* player_render = player->AddComponent<SpriteRenderer>();
	player_render->order = 10;
	player_behaviour->_walkSprite = Sprite::Create("Assets/Sprites/Characters/Popo/walk1.png");
	player_behaviour->_jumpSprite = Sprite::Create("Assets/Sprites/Characters/Popo/jump1.png");
	player_render->_sprite = player_behaviour->_walkSprite;
	AABBCollider* player_collider = player->AddComponent<AABBCollider>();
	AudioSource* player_audio = player->AddComponent<AudioSource>();
	player_audio->_clip = Audio::LoadSound("Assets/Sounds/sound.wav");
	Rigidbody* playerRb = player->AddComponent<Rigidbody>();
	playerRb->_linearDrag = 5.0f;
	playerRb->_gravityScale = 0.5f;


	//Setup Ground Collider
	GameObject* floor = new GameObject();
	floor->_transform->_pivot = Vector2D(0, 1);
	AABBCollider* floorCollider = floor->AddComponent<AABBCollider>();
	floorCollider->_width = Screen::WIDTH;
	floorCollider->_height = 23;


	//Setup Stage Colliders
	for (int i = 0; i < 6; i++)
	{
		float height = 64 + i * 48;
		float width = (i == 0) ? 32 : 40;

		GameObject* stageLeft = new GameObject();
		stageLeft->_transform->_pivot = Vector2D(0, 1);
		stageLeft->_transform->_position = Vector2D(0, height);
		AABBCollider* stageColliderLeft = stageLeft->AddComponent<AABBCollider>();
		stageColliderLeft->_width = width;
		stageColliderLeft->_height = 7;

		GameObject* stageRight = new GameObject();
		stageRight->_transform->_pivot = Vector2D(1, 1);
		stageRight->_transform->_position = Vector2D(Screen::WIDTH, height);
		AABBCollider* stageColliderRight = stageRight->AddComponent<AABBCollider>();
		stageColliderRight->_width = width;
		stageColliderRight->_height = 7;


		float tileCount = (i == 0) ? 24 : 22;
		for (int x = 0; x < tileCount; x++)
		{
			GameObject* tile = new GameObject();
			tile->_transform->_pivot = Vector2D(0, 1);
			tile->_transform->_position = Vector2D(width + x * 8, height);
			SpriteRenderer* tileSprite = tile->AddComponent<SpriteRenderer>();
			tileSprite->_sprite = Sprite::Create("Assets/Sprites/Environment/tile_blue.png");
			tile->AddComponent<AABBCollider>();
		}


	}

	SpriteRenderer::SortRenderers();
}

void IceClimberGame::Init()
{
	_background->Init();
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
}

void IceClimberGame::Destroy()
{
}
