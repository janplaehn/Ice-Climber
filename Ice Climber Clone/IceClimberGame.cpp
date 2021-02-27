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
#include <Camera.h>
#include "TopiBehaviour.h"
#include <Animation.h>
#include "GameOverUIBehaviour.h"
#include "LifeUI.h"

void IceClimberGame::Create(class Plaehngine* engine)
{
	this->_engine = engine;


	//Setup Background
	_background = new GameObject();
	SpriteRenderer* background_render = _background->AddComponent<SpriteRenderer>();
	background_render->_sprite = Sprite::Create("Assets/Sprites/Backgrounds/default.png");
	background_render->_order = -100;
	_background->_transform->_position = Vector2D(Screen::WIDTH / 2, background_render->_sprite->GetHeight() / 2);


	//Setup background Music
	GameObject* music = new GameObject();
	AudioSource* musicSrc = music->AddComponent<AudioSource>();
	musicSrc->_clip = Audio::LoadSound("Assets/Music/stage.wav");
	musicSrc->_isLooping = true;
	musicSrc->Play();


	//Setup Player
	player = new GameObject();
	player->_transform->_pivot = Vector2D(0.5f, 0.75f);
	player->_transform->_position.x = Screen::WIDTH / 2;
	player->_transform->_position.y = 36;
	PlayerBehaviour* playerBehaviour = player->AddComponent<PlayerBehaviour>();
	Animation* playerWalkAnim = player->AddComponent<Animation>();
	playerWalkAnim->_order = 10;
	playerWalkAnim->_spriteWidth = 32;
	playerBehaviour->_walkSprite = Sprite::Create("Assets/Sprites/Characters/Popo/walk.png");
	playerBehaviour->_jumpSprite = Sprite::Create("Assets/Sprites/Characters/Popo/jump1.png");
	playerWalkAnim->_spriteSheet = playerBehaviour->_walkSprite;
	AABBCollider* player_collider = player->AddComponent<AABBCollider>();
	player_collider->_width = 16;
	player_collider->_height = 24;
	player_collider->_offset = Vector2D(0, 4);
	playerBehaviour->_jumpSource = player->AddComponent<AudioSource>();
	playerBehaviour->_jumpSource->_clip = Audio::LoadSound("Assets/Sounds/jump.wav");
	playerBehaviour->_deathSource = player->AddComponent<AudioSource>();
	playerBehaviour->_deathSource->_clip = Audio::LoadSound("Assets/Sounds/death.wav");
	playerBehaviour->_gameOverSource = player->AddComponent<AudioSource>();
	playerBehaviour->_gameOverSource->_clip = Audio::LoadSound("Assets/Sounds/gameOver.wav");
	playerBehaviour->_tileBreakSource = player->AddComponent<AudioSource>();
	playerBehaviour->_tileBreakSource->_clip = Audio::LoadSound("Assets/Sounds/tileBreak.wav");
	Rigidbody* playerRb = player->AddComponent<Rigidbody>();
	playerRb->_linearDrag = 5.0f;
	playerRb->_gravityScale = 0.5f;

	//Setup Topis
	for (int i = 0; i < 3; i++)
	{
		GameObject* topi = new GameObject();
		topi->_tag = "Topi";
		topi->_transform->_pivot = Vector2D(0.5f, 1);
		topi->_transform->_position.x = 0 + i * 40;
		topi->_transform->_position.y = 24 + i * 96;
		topi->AddComponent<TopiBehaviour>();
		Animation* topiRender = topi->AddComponent<Animation>();
		topiRender->_order = -101;
		topiRender->_spriteSheet = Sprite::Create("Assets/Sprites/Characters/Topi/walk.png");
		topiRender->_spriteWidth = 16;
		topi->AddComponent<AABBCollider>()->_isTrigger = true;
	}

	//Setup Ground Collider
	GameObject* floor = new GameObject();
	floor->_transform->_pivot = Vector2D(0, 1);
	AABBCollider* floorCollider = floor->AddComponent<AABBCollider>();
	floorCollider->_width = Screen::WIDTH;
	floorCollider->_height = 20;


	//Setup Stage Colliders
	for (int i = 0; i < 7; i++)
	{
		float height = 64 + i * 48;
		float width = 40;
		if (i == 0) width = 32;
		if ((i == 4) || (i == 5) || (i == 6)) width = 48;

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
			tile->_tag = "Tile";
			tile->_transform->_pivot = Vector2D(0, 1);
			tile->_transform->_position = Vector2D(width + x * 8, height);
			SpriteRenderer* tileSprite = tile->AddComponent<SpriteRenderer>();
			tileSprite->_sprite = Sprite::Create("Assets/Sprites/Environment/tile_blue.png");
			tile->AddComponent<AABBCollider>();
		}


	}

	//Setup UI

	//GameOver UI
	GameObject* gameOver = new GameObject();
	gameOver->_transform->_position = Vector2D(128, 0);
	SpriteRenderer* gameOverRenderer = gameOver->AddComponent<SpriteRenderer>();
	gameOver->_transform->_isInScreenSpace = true;
	gameOverRenderer->_sprite = Sprite::Create("Assets/Sprites/UI/gameOver.png");
	gameOver->AddComponent<GameOverUIBehaviour>();
	gameOver->_enabled = false;
	playerBehaviour->_gameOverUI = gameOver;

	//Lives UI
	GameObject* lifeUI = new GameObject();
	LifeUI* lifeUIComponent = lifeUI->AddComponent<LifeUI>();
	playerBehaviour->_lifeUI = lifeUIComponent;

	for (int i = 0; i < playerBehaviour->_lives; i++)
	{
		GameObject* lifeUIelement = new GameObject();
		lifeUIelement->_transform->_pivot = Vector2D(0, 0);
		lifeUIelement->_transform->_position = Vector2D(2 + i * 10, Screen::HEIGHT - 2);
		lifeUIelement->_transform->_isInScreenSpace = true;
		SpriteRenderer* lifeUIelementRenderer = lifeUIelement->AddComponent<SpriteRenderer>();
		lifeUIelementRenderer->_sprite = Sprite::Create("Assets/Sprites/UI/life.png");
		lifeUIComponent->_lifeRenderers.push_back(lifeUIelementRenderer);
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

	const float MAX_CAMERA_DISTANCE = 100;
	if (player->_transform->_position.y > (Camera::_position.y + MAX_CAMERA_DISTANCE)) {

		Camera::_position.y += dt * 10;

		if ((Camera::_position.y + MAX_CAMERA_DISTANCE) > player->_transform->_position.y) {
			Camera::_position.y = player->_transform->_position.y - MAX_CAMERA_DISTANCE;
		}
	}
}

void IceClimberGame::Destroy()
{
}
