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
#include "Nitpicker.h"

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
	player_collider->_width = 8;
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
		TopiBehaviour* topiBehaviour = topi->AddComponent<TopiBehaviour>();
		topiBehaviour->_animation = topi->AddComponent<Animation>();
		topiBehaviour->_animation->_order = -101;
		topiBehaviour->_animation->_spriteSheet = Sprite::Create("Assets/Sprites/Characters/Topi/walk.png");
		topiBehaviour->_animation->_spriteWidth = 16;
		topi->AddComponent<AABBCollider>()->_isTrigger = true;

		topiBehaviour->_ice = new GameObject();
		topiBehaviour->_ice->_tag = "Topi";
		topiBehaviour->_ice->_transform->_pivot = Vector2D(0.5f, 1);
		topiBehaviour->_ice->_transform->_position = topi->_transform->_position + Vector2D::Left() * 16;
		SpriteRenderer* iceRenderer = topiBehaviour->_ice->AddComponent<SpriteRenderer>();
		iceRenderer->_sprite = Sprite::Create("Assets/Sprites/Characters/Topi/ice.png");
		iceRenderer->_order = topiBehaviour->_animation->_order;
		topiBehaviour->_ice->AddComponent<AABBCollider>()->_isTrigger = true;

	}

	//Setup Nitpicker
	GameObject* nitpicker = new GameObject();
	nitpicker->_tag = "Topi";
	nitpicker->_transform->_position.y = 200;
	nitpicker->_transform->_position.x = 0;
	Animation* nitAnimation =  nitpicker->AddComponent<Animation>();
	nitAnimation->_spriteSheet = Sprite::Create("Assets/Sprites/Characters/Nitpicker/fly.png");
	nitAnimation->_spriteWidth = 16;
	nitAnimation->_frameRate = 8;
	nitAnimation->_order = 1;
	nitpicker->AddComponent<AABBCollider>()->_isTrigger = true;
	nitpicker->AddComponent<Nitpicker>();

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

	//Setup Bonus Stage Colldiders :(
	{

		//1st floor
		GameObject* stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0, 1);
		stage->_transform->_position = Vector2D(0, 400);
		AABBCollider* stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 56;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(1, 1);
		stage->_transform->_position = Vector2D(Screen::WIDTH, 400);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 56;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0, 1);
		stage->_transform->_position = Vector2D(72, 400);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 48;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(1, 1);
		stage->_transform->_position = Vector2D(Screen::WIDTH - 72, 400);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 48;
		stageCollider->_height = 7;

		//2nd floor
		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0, 1);
		stage->_transform->_position = Vector2D(48, 432);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 32;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(1, 1);
		stage->_transform->_position = Vector2D(Screen::WIDTH - 48, 432);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 32;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0, 1);
		stage->_transform->_position = Vector2D(104, 432);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 48;
		stageCollider->_height = 7;

		//First Cloud
		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0.5, 1);
		stage->_transform->_position = Vector2D(128, 480);
		stage->AddComponent<SpriteRenderer>()->_sprite = Sprite::Create("Assets/Sprites/Environment/cloud.png");
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 48;
		stageCollider->_height = 7;


		//The Rest I guess
		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0, 1);
		stage->_transform->_position = Vector2D(40, 528);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 56;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0, 1);
		stage->_transform->_position = Vector2D(144, 520);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 32;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0, 1);
		stage->_transform->_position = Vector2D(168, 560);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 24;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0, 1);
		stage->_transform->_position = Vector2D(96, 568);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 48;
		stageCollider->_height = 7;

		//Second Cloud
		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0.5, 1);
		stage->_transform->_position = Vector2D(128, 608);
		stage->AddComponent<SpriteRenderer>()->_sprite = Sprite::Create("Assets/Sprites/Environment/cloud.png");
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 48;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0, 1);
		stage->_transform->_position = Vector2D(128, 648);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 32;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0, 1);
		stage->_transform->_position = Vector2D(64, 656);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 24;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0, 1);
		stage->_transform->_position = Vector2D(152, 680);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 24;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0, 1);
		stage->_transform->_position = Vector2D(96, 696);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 24;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0, 1);
		stage->_transform->_position = Vector2D(112, 720);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 32;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0, 1);
		stage->_transform->_position = Vector2D(48, 760);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 56;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(1, 1);
		stage->_transform->_position = Vector2D(Screen::WIDTH - 48, 760);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 48;
		stageCollider->_height = 7;
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
