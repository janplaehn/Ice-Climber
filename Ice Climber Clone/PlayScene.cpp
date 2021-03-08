#include "PlayScene.h"
#include "PlayerBehaviour.h"
#include "Topi.h"
#include "GameOverUIBehaviour.h"
#include "LifeUI.h"
#include "Nitpicker.h"
#include "Cloud.h"
#include "HammerTrigger.h"
#include "CameraManager.h"
#include <Random.h>
#include "BonusTimer.h"
#include "Scores.h"

void PlayScene::Load()
{
	Scores::Reset();

	//Setup Background
	GameObject* background = new GameObject();
	SpriteRenderer* background_render = background->AddComponent<SpriteRenderer>();
	background_render->_sprite = Sprite::Create("Assets/Sprites/Backgrounds/default.png");
	background_render->_order = -100;
	background->_transform->_position = Vector2D(Screen::_width / 2, background_render->_sprite->GetHeight() / 2);


	//Setup background Music
	GameObject* music = new GameObject();
	AudioSource* musicSrc = music->AddComponent<AudioSource>();
	musicSrc->_clip = Audio::LoadSound("Assets/Music/stage.wav");
	musicSrc->_isLooping = true;
	musicSrc->Play();

	//Setup Player
	GameObject* player = new GameObject();
	player->_transform->_pivot = Vector2D(0.5f, 0.75f);
	player->_transform->_position.x = Screen::_width / 2;
	player->_transform->_position.y = 32;
	PlayerBehaviour* playerBehaviour = player->AddComponent<PlayerBehaviour>();
	playerBehaviour->_animation = player->AddComponent<Animation>();
	playerBehaviour->_animation->_order = 10;
	playerBehaviour->_animation->_spriteWidth = 32;
	playerBehaviour->_walkSprite = Sprite::Create("Assets/Sprites/Characters/Popo/walk.png");
	playerBehaviour->_jumpSprite = Sprite::Create("Assets/Sprites/Characters/Popo/jump1.png");
	playerBehaviour->_attackSprite = Sprite::Create("Assets/Sprites/Characters/Popo/attack.png");
	playerBehaviour->_animation->_spriteSheet = playerBehaviour->_walkSprite;
	playerBehaviour->_collider = player->AddComponent<AABBCollider>();
	playerBehaviour->_collider->_width = 8;
	playerBehaviour->_collider->_height = 20;
	playerBehaviour->_collider->_offset = Vector2D(0, 4);
	playerBehaviour->_jumpSource = player->AddComponent<AudioSource>();
	playerBehaviour->_jumpSource->_clip = Audio::LoadSound("Assets/Sounds/jump.wav");
	playerBehaviour->_deathSource = player->AddComponent<AudioSource>();
	playerBehaviour->_deathSource->_clip = Audio::LoadSound("Assets/Sounds/death.wav");
	playerBehaviour->_gameOverSource = player->AddComponent<AudioSource>();
	playerBehaviour->_gameOverSource->_clip = Audio::LoadSound("Assets/Sounds/gameOver.wav");
	playerBehaviour->_rigidbody = player->AddComponent<Rigidbody>();
	playerBehaviour->_rigidbody->_linearDrag = 4.5f;
	playerBehaviour->_rigidbody->_gravityScale = 0.5f;

	playerBehaviour->_hammer = new GameObject();
	playerBehaviour->_hammer->_tag = "Hammer";
	HammerTrigger* hammerTrigger = playerBehaviour->_hammer->AddComponent<HammerTrigger>();
	AABBCollider* hammerCol = playerBehaviour->_hammer->AddComponent<AABBCollider>();
	playerBehaviour->_hammer->AddComponent<Rigidbody>()->_isKinematic = true;
	hammerCol->_isTrigger = true;
	playerBehaviour->_hammer->_transform->_position = player->_transform->_position;
	hammerCol->_width = 8;
	hammerCol->_height = 8;
	hammerTrigger->_tileBreakSource = playerBehaviour->_hammer->AddComponent<AudioSource>();
	hammerTrigger->_tileBreakSource->_clip = Audio::LoadSound("Assets/Sounds/tileBreak.wav");


	//Setup Topis
	for (int i = 0; i < 4; i++)
	{
		GameObject* topi = new GameObject();
		topi->_tag = "Topi";
		topi->_transform->_pivot = Vector2D(0.5f, 1);
		topi->_transform->_position.x = 0 + i * 40;
		topi->_transform->_position.y = 24 + i * 96;
		Topi* topiBehaviour = topi->AddComponent<Topi>();
		topiBehaviour->_animation = topi->AddComponent<Animation>();
		topiBehaviour->_animation->_order = -101;
		topiBehaviour->_animation->_spriteSheet = Sprite::Create("Assets/Sprites/Characters/Topi/walk.png");
		topiBehaviour->_deathSprite = Sprite::Create("Assets/Sprites/Characters/Topi/death.png");
		topiBehaviour->_animation->_spriteWidth = 16;
		topi->AddComponent<AABBCollider>()->_isTrigger = true;

		topiBehaviour->_deathSource = topi->AddComponent<AudioSource>();
		topiBehaviour->_deathSource->_clip = Audio::LoadSound("Assets/Sounds/topiDeath.wav");
		topiBehaviour->_fallSource = topi->AddComponent<AudioSource>();
		topiBehaviour->_fallSource->_clip = Audio::LoadSound("Assets/Sounds/topiFall.wav");

		topiBehaviour->_ice = new GameObject();
		topiBehaviour->_ice->_tag = "Topi";
		topiBehaviour->_ice->_transform->_pivot = Vector2D(0.5f, 1);
		topiBehaviour->_ice->_transform->_position = topi->_transform->_position + Vector2D::Left() * 16;
		SpriteRenderer* iceRenderer = topiBehaviour->_ice->AddComponent<SpriteRenderer>();
		iceRenderer->_sprite = Sprite::Create("Assets/Sprites/Characters/Topi/ice.png");
		iceRenderer->_order = topiBehaviour->_animation->_order;
		topiBehaviour->_ice->AddComponent<AABBCollider>()->_isTrigger = true;

	}
	for (int i = 0; i < 2; i++)
	{
		//Setup Nitpicker
		GameObject* nitpicker = new GameObject();
		nitpicker->_tag = "Topi";
		nitpicker->_transform->_position.y = 200 + i * 248;
		nitpicker->_transform->_position.x = 0;
		Animation* nitAnimation = nitpicker->AddComponent<Animation>();
		nitAnimation->_spriteSheet = Sprite::Create("Assets/Sprites/Characters/Nitpicker/fly.png");
		nitAnimation->_spriteWidth = 16;
		nitAnimation->_frameRate = 8;
		nitAnimation->_order = 1;
		nitpicker->AddComponent<AABBCollider>()->_isTrigger = true;
		Nitpicker* nitBehaviour = nitpicker->AddComponent<Nitpicker>();
		nitBehaviour->_deathSprite = Sprite::Create("Assets/Sprites/Characters/Nitpicker/death.png");
		nitBehaviour->_deathSource = nitpicker->AddComponent<AudioSource>();
		nitBehaviour->_deathSource->_clip = Audio::LoadSound("Assets/Sounds/nitpickerDeath.wav");
	}

	//Setup Ground Collider
	GameObject* floor = new GameObject();
	floor->_transform->_pivot = Vector2D(0, 1);
	AABBCollider* floorCollider = floor->AddComponent<AABBCollider>();
	floorCollider->_width = Screen::_width;
	floorCollider->_height = 20;


	//Setup Stage Colliders
	int COUNT = 7;
	for (int i = 0; i < COUNT; i++)
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
		stageRight->_transform->_position = Vector2D(Screen::_width, height);
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
			AABBCollider* tileCol =  tile->AddComponent<AABBCollider>();
			tileCol->_width = 8;
			tileCol->_height = 7;
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
		lifeUIelement->_transform->_position = Vector2D(2 + i * 10, Screen::_height - 2);
		lifeUIelement->_transform->_isInScreenSpace = true;
		SpriteRenderer* lifeUIelementRenderer = lifeUIelement->AddComponent<SpriteRenderer>();
		lifeUIelementRenderer->_sprite = Sprite::Create("Assets/Sprites/UI/life.png");
		lifeUIComponent->_lifeRenderers.push_back(lifeUIelementRenderer);
	}

	GameObject* camera = new GameObject();
	camera->AddComponent<CameraManager>()->_player = player->_transform;

	//Setup Bonus Stage Colldiders :(
	{

		//1st timer
		GameObject* timerGo = new GameObject();
		timerGo->_transform->_pivot = Vector2D(0, 1);
		timerGo->_transform->_position = Vector2D(24, 608);
		BonusTimer* timer = timerGo->AddComponent<BonusTimer>();
		timer->_text = timerGo->AddComponent<Text>();
		timer->_text->_text = "40.0";
		timer->_text->_fontName = "Ice Climber";
		timerGo->_enabled = false;
		playerBehaviour->_timers.push_back(timer);

		//1st floor

		GameObject* stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0, 1);
		stage->_transform->_position = Vector2D(0, 400);
		AABBCollider* stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 56;
		stageCollider->_height = 7;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(1, 1);
		stage->_transform->_position = Vector2D(Screen::_width, 400);
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
		stage->_transform->_position = Vector2D(Screen::_width - 72, 400);
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

		GameObject* eggplant = new GameObject();
		eggplant->_transform->_pivot = Vector2D(0, 1);
		eggplant->_transform->_position = Vector2D(56, 440);
		eggplant->_tag = "Eggplant";
		eggplant->AddComponent<SpriteRenderer>()->_sprite = Sprite::Create("Assets/Sprites/Fruits/eggplant.png");
		eggplant->AddComponent<AABBCollider>()->_isTrigger = true;

		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(1, 1);
		stage->_transform->_position = Vector2D(Screen::_width - 48, 432);
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
		stage->AddComponent<Cloud>()->_moveRight = true;


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

		eggplant = new GameObject();
		eggplant->_transform->_pivot = Vector2D(0, 1);
		eggplant->_transform->_position = Vector2D(152, 528);
		eggplant->_tag = "Eggplant";
		eggplant->AddComponent<SpriteRenderer>()->_sprite = Sprite::Create("Assets/Sprites/Fruits/eggplant.png");
		eggplant->AddComponent<AABBCollider>()->_isTrigger = true;

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

		eggplant = new GameObject();
		eggplant->_transform->_pivot = Vector2D(0, 1);
		eggplant->_transform->_position = Vector2D(102, 576);
		eggplant->_tag = "Eggplant";
		eggplant->AddComponent<SpriteRenderer>()->_sprite = Sprite::Create("Assets/Sprites/Fruits/eggplant.png");
		eggplant->AddComponent<AABBCollider>()->_isTrigger = true;

		//Second Cloud
		stage = new GameObject();
		stage->_transform->_pivot = Vector2D(0.5, 1);
		stage->_transform->_position = Vector2D(128, 608);
		stage->AddComponent<SpriteRenderer>()->_sprite = Sprite::Create("Assets/Sprites/Environment/cloud.png");
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 48;
		stageCollider->_height = 7;
		stage->AddComponent<Cloud>()->_moveRight = false;

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
		stage->_transform->_position = Vector2D(Screen::_width - 48, 760);
		stageCollider = stage->AddComponent<AABBCollider>();
		stageCollider->_width = 48;
		stageCollider->_height = 7;
	}

	//Setup Condor
	GameObject* condorGo = new GameObject();
	condorGo->_tag = "Condor";
	condorGo->_transform->_pivot = Vector2D(0.5, 1);
	condorGo->_transform->_position = Vector2D(Screen::_width / 2, 832);
	Animation*  condorAnim = condorGo->AddComponent<Animation>();
	condorAnim->_spriteSheet = Sprite::Create("Assets/Sprites/Characters/Condor/fly.png");
	condorAnim->_spriteWidth = 32;
	condorAnim->_frameRate = 8;
	condorAnim->_order = 100;
	AABBCollider* condorCol = condorGo->AddComponent<AABBCollider>();
	condorCol->_isTrigger = true;
	condorCol->_width = 32;
	condorCol->_height = 16;
	Cloud* cloud = condorGo->AddComponent<Cloud>();
	cloud->_moveRight = false;
	cloud->_speed = 40;

	//2nt timer
	GameObject* timerGo = new GameObject();
	timerGo->_transform->_pivot = Vector2D(0, 1);
	timerGo->_transform->_position = Vector2D(24, 848);
	BonusTimer* timer = timerGo->AddComponent<BonusTimer>();
	timer->_text = timerGo->AddComponent<Text>();
	timer->_text->_text = "40.0";
	timer->_text->_fontName = "Ice Climber";
	timerGo->_enabled = false;
	playerBehaviour->_timers.push_back(timer);
}
