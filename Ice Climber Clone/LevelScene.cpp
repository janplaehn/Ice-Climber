#include "LevelScene.h"
#include "PlayerBehaviour.h"
#include "Topi.h"
#include "GameOverUI.h"
#include "LifeUI.h"
#include "Nitpicker.h"
#include "Cloud.h"
#include "Hammer.h"
#include "LevelCamera.h"
#include <Random.h>
#include "BonusTimer.h"
#include "Scores.h"
#include "ObjectPool.h"
#include "Debris.h"

void LevelScene::Load()
{
	Scores::Reset();

	std::shared_ptr<PlayerBehaviour> player = LoadPlayer();
	LoadBackground();
	LoadMusic();
	LoadTopis();
	LoadNitpickers();
	LoadMainStage();
	LoadBonusStage(player);
	LoadUI(player);

	std::shared_ptr<GameObject> camera = GameObject::Create();
	camera->AddComponent<LevelCamera>()->SetPlayerTransform(player->_transform);	
}

void LevelScene::LoadBackground()
{
	std::shared_ptr<GameObject> gameObject = GameObject::Create();
	std::shared_ptr<SpriteRenderer> renderer = gameObject->AddComponent<SpriteRenderer>();
	renderer->_sprite = Sprite::Create("Assets/Sprites/Backgrounds/default.png");
	renderer->_order = -100;
	gameObject->_transform->_position = Vector2D(Screen::_width / 2, renderer->_sprite->GetHeight() / 2);
}

void LevelScene::LoadMusic()
{
	std::shared_ptr<GameObject> music = GameObject::Create();
	std::shared_ptr<AudioSource> musicSrc = music->AddComponent<AudioSource>();
	musicSrc->_clip = Audio::LoadSound("Assets/Music/stage.wav");
	musicSrc->_isLooping = true;
	musicSrc->Play();
}

std::shared_ptr<PlayerBehaviour> LevelScene::LoadPlayer()
{
	std::shared_ptr<GameObject> player = GameObject::Create();
	player->_transform->_pivot = Vector2D(0.5f, 0.75f);
	player->_transform->_position.x = Screen::_width / 2;
	player->_transform->_position.y = 32;
	std::shared_ptr<PlayerBehaviour> playerBehaviour = player->AddComponent<PlayerBehaviour>();
	playerBehaviour->_animation = player->AddComponent<Animation>();
	playerBehaviour->_animation->_order = 10;
	playerBehaviour->_animation->_spriteWidth = 32;
	playerBehaviour->_walkSprite = Sprite::Create("Assets/Sprites/Characters/Popo/walk.png");
	playerBehaviour->_jumpSprite = Sprite::Create("Assets/Sprites/Characters/Popo/jump1.png");
	playerBehaviour->_attackSprite = Sprite::Create("Assets/Sprites/Characters/Popo/attack.png");
	playerBehaviour->_animation->_spriteSheet = playerBehaviour->_walkSprite;
	playerBehaviour->_collider = player->AddComponent<AABBCollider>();
	playerBehaviour->_collider->SetScale(Vector2D(8, 20));
	playerBehaviour->_collider->SetOffset(Vector2D(0, 4));
	playerBehaviour->_jumpSource = player->AddComponent<AudioSource>();
	playerBehaviour->_jumpSource->_clip = Audio::LoadSound("Assets/Sounds/jump.wav");
	playerBehaviour->_deathSource = player->AddComponent<AudioSource>();
	playerBehaviour->_deathSource->_clip = Audio::LoadSound("Assets/Sounds/death.wav");
	playerBehaviour->_gameOverSource = player->AddComponent<AudioSource>();
	playerBehaviour->_gameOverSource->_clip = Audio::LoadSound("Assets/Sounds/gameOver.wav");
	playerBehaviour->_rigidbody = player->AddComponent<Rigidbody>();
	playerBehaviour->_rigidbody->_linearDrag = 4.5f;
	playerBehaviour->_rigidbody->_gravityScale = 0.5f;
	playerBehaviour->_goalSource = player->AddComponent<AudioSource>();
	playerBehaviour->_goalSource->_clip = Audio::LoadSound("Assets/Music/goal.wav");

	playerBehaviour->_hammer = GameObject::Create();
	playerBehaviour->_hammer->_tag = "Hammer";
	std::shared_ptr<Hammer> hammer = playerBehaviour->_hammer->AddComponent<Hammer>();
	std::shared_ptr<AABBCollider> hammerCol = playerBehaviour->_hammer->AddComponent<AABBCollider>();
	playerBehaviour->_hammer->AddComponent<Rigidbody>()->_isKinematic = true;
	hammerCol->SetTrigger(true);
	playerBehaviour->_hammer->_transform->_position = player->_transform->_position;
	hammerCol->SetScale(Vector2D(8, 8));
	std::shared_ptr<AudioSource> tileBreakSource = playerBehaviour->_hammer->AddComponent<AudioSource>();
	tileBreakSource->_clip = Audio::LoadSound("Assets/Sounds/tileBreak.wav");
	hammer->SetTileBreakAudioSource(tileBreakSource);

	const int DEBRISCOUNT = 5;
	ObjectPool* debrisPool = new ObjectPool();
	hammer->SetDebrisPool(debrisPool);
	for (size_t i = 0; i < DEBRISCOUNT; i++)
	{
		std::shared_ptr<GameObject> debrisGo = GameObject::Create();
		std::shared_ptr<SpriteRenderer> debrisRenderer = debrisGo->AddComponent<SpriteRenderer>();
		debrisRenderer->_sprite = Sprite::Create("Assets/Sprites/Environment/debris_blue.png");
		debrisRenderer->_order = 100;
		debrisGo->AddComponent<Rigidbody>();
		debrisGo->AddComponent<Debris>();

		debrisPool->Add(debrisGo);
	}

	return playerBehaviour;
}

void LevelScene::LoadTopis()
{
	for (int i = 0; i < 4; i++)
	{
		std::shared_ptr<GameObject> topi = GameObject::Create();
		topi->_tag = "Enemy";
		topi->_transform->_pivot = Vector2D(0.5f, 1);
		topi->_transform->_position.x = 0 + i * 40;
		topi->_transform->_position.y = 24 + i * 96;
		std::shared_ptr<Topi> topiBehaviour = topi->AddComponent<Topi>();
		topiBehaviour->_animation = topi->AddComponent<Animation>();
		topiBehaviour->_animation->_order = -101;
		topiBehaviour->_animation->_spriteSheet = Sprite::Create("Assets/Sprites/Characters/Topi/walk.png");
		topiBehaviour->_deathSprite = Sprite::Create("Assets/Sprites/Characters/Topi/death.png");
		topiBehaviour->_animation->_spriteWidth = 16;
		topi->AddComponent<AABBCollider>()->SetTrigger(true);

		topiBehaviour->_deathSource = topi->AddComponent<AudioSource>();
		topiBehaviour->_deathSource->_clip = Audio::LoadSound("Assets/Sounds/topiDeath.wav");
		topiBehaviour->_fallSource = topi->AddComponent<AudioSource>();
		topiBehaviour->_fallSource->_clip = Audio::LoadSound("Assets/Sounds/topiFall.wav");

		topiBehaviour->_ice = GameObject::Create();
		topiBehaviour->_ice->_tag = "Enemy";
		topiBehaviour->_ice->_transform->_pivot = Vector2D(0.5f, 1);
		topiBehaviour->_ice->_transform->_position = topi->_transform->_position + Vector2D::Left() * 16;
		std::shared_ptr<SpriteRenderer> iceRenderer = topiBehaviour->_ice->AddComponent<SpriteRenderer>();
		iceRenderer->_sprite = Sprite::Create("Assets/Sprites/Characters/Topi/ice.png");
		iceRenderer->_order = topiBehaviour->_animation->_order;
		topiBehaviour->_ice->AddComponent<AABBCollider>()->SetTrigger(true);

	}
}

void LevelScene::LoadNitpickers()
{
	for (int i = 0; i < 2; i++)
	{
		std::shared_ptr<GameObject> nitpicker = GameObject::Create();
		nitpicker->_tag = "Enemy";
		nitpicker->_transform->_position.y = 200 + i * 248;
		nitpicker->_transform->_position.x = 0;
		std::shared_ptr<Animation> nitAnimation = nitpicker->AddComponent<Animation>();
		nitAnimation->_spriteSheet = Sprite::Create("Assets/Sprites/Characters/Nitpicker/fly.png");
		nitAnimation->_spriteWidth = 16;
		nitAnimation->_frameRate = 8;
		nitAnimation->_order = 1;
		nitpicker->AddComponent<AABBCollider>()->SetTrigger(true);
		std::shared_ptr<Nitpicker> nitBehaviour = nitpicker->AddComponent<Nitpicker>();
		Sprite* deathSprite = Sprite::Create("Assets/Sprites/Characters/Nitpicker/death.png");;
		nitBehaviour->SetDeathSprite(deathSprite);
		std::shared_ptr<AudioSource> deathAudioSource = nitpicker->AddComponent<AudioSource>();
		deathAudioSource->_clip = Audio::LoadSound("Assets/Sounds/nitpickerDeath.wav");
		nitBehaviour->SetDeathAudioSource(deathAudioSource);
	}
}

void LevelScene::LoadMainStage()
{
	LoadStageCollider(Vector2D::Zero(), Vector2D(0, 1), Vector2D(Screen::_width, 24));

	int FLOORCOUNT = 7;
	for (int i = 0; i < FLOORCOUNT; i++)
	{
		float height = 64 + i * 48;
		float width = 40;
		if (i == 0) width = 32;
		if ((i == 4) || (i == 5) || (i == 6)) width = 48;

		LoadStageCollider(Vector2D(0, height), Vector2D(0, 1), Vector2D(width, 7));
		LoadStageCollider(Vector2D(Screen::_width, height), Vector2D(1, 1), Vector2D(width, 7));

		float tileCount = (i == 0) ? 24 : 22;
		for (int x = 0; x < tileCount; x++)
		{
			std::shared_ptr<GameObject> tile = GameObject::Create();
			tile->_tag = "Tile";
			tile->_transform->_pivot = Vector2D(0, 1);
			tile->_transform->_position = Vector2D(width + x * 8, height);
			std::shared_ptr<SpriteRenderer> tileSprite = tile->AddComponent<SpriteRenderer>();
			tileSprite->_sprite = Sprite::Create("Assets/Sprites/Environment/tile_blue.png");
			std::shared_ptr<AABBCollider> tileCol = tile->AddComponent<AABBCollider>();
			tileCol->SetScale(Vector2D(8, 7));
		}
	}
}

void LevelScene::LoadBonusStage(std::shared_ptr<PlayerBehaviour> player)
{
	LoadTimer(player, Vector2D(24, 608));
	//1st floor
	LoadStageCollider(Vector2D(0, 400), Vector2D(0, 1), Vector2D(56, 7));
	LoadStageCollider(Vector2D(Screen::_width, 400), Vector2D(1, 1), Vector2D(56, 7));
	LoadStageCollider(Vector2D(72, 400), Vector2D(0, 1), Vector2D(48, 7));
	LoadStageCollider(Vector2D(Screen::_width - 72, 400), Vector2D(1, 1), Vector2D(48, 7));
	//2nd floor
	LoadStageCollider(Vector2D(48, 432), Vector2D(0, 1), Vector2D(32, 7));
	LoadEggplant(Vector2D(56, 440));
	LoadStageCollider(Vector2D(Screen::_width - 48, 432), Vector2D(1, 1), Vector2D(32, 7));
	LoadStageCollider(Vector2D(104, 432), Vector2D(0, 1), Vector2D(48, 7));
	LoadCloud(Vector2D(128, 480), true);
	//> 3rd Floor
	LoadStageCollider(Vector2D(40, 528), Vector2D(0, 1), Vector2D(56, 7));
	LoadStageCollider(Vector2D(144, 520), Vector2D(0, 1), Vector2D(32, 7));
	LoadEggplant(Vector2D(152, 528));
	LoadStageCollider(Vector2D(168, 560), Vector2D(0, 1), Vector2D(24, 7));
	LoadStageCollider(Vector2D(96, 568), Vector2D(0, 1), Vector2D(48, 7));
	LoadEggplant(Vector2D(102, 576));
	LoadCloud(Vector2D(128, 608), false);
	LoadStageCollider(Vector2D(128, 648), Vector2D(0, 1), Vector2D(32, 7));
	LoadStageCollider(Vector2D(64, 656), Vector2D(0, 1), Vector2D(24, 7));
	LoadStageCollider(Vector2D(152, 680), Vector2D(0, 1), Vector2D(24, 7));
	LoadStageCollider(Vector2D(96, 696), Vector2D(0, 1), Vector2D(24, 7));
	LoadStageCollider(Vector2D(112, 720), Vector2D(0, 1), Vector2D(32, 7));
	LoadStageCollider(Vector2D(48, 760), Vector2D(0, 1), Vector2D(56, 7));
	LoadStageCollider(Vector2D(Screen::_width - 48, 760), Vector2D(1, 1), Vector2D(48, 7));
	if (player)	LoadCondor();
	LoadTimer(player, Vector2D(24, 848));
}

void LevelScene::LoadStageCollider(Vector2D position, Vector2D pivot, Vector2D scale)
{
	std::shared_ptr<GameObject> gameObject = GameObject::Create();
	gameObject->_transform->_pivot = pivot;
	gameObject->_transform->_position = Vector2D(position);
	std::shared_ptr<AABBCollider> collider = gameObject->AddComponent<AABBCollider>();
	collider->SetScale(scale);
}

void LevelScene::LoadUI(std::shared_ptr<PlayerBehaviour> player)
{
	//GameOver UI
	std::shared_ptr<GameObject> gameOver = GameObject::Create();
	gameOver->_transform->_position = Vector2D(128, 0);
	std::shared_ptr<SpriteRenderer> gameOverRenderer = gameOver->AddComponent<SpriteRenderer>();
	gameOver->_transform->_isInScreenSpace = true;
	gameOverRenderer->_sprite = Sprite::Create("Assets/Sprites/UI/gameOver.png");
	gameOver->AddComponent<GameOverUI>();
	gameOver->_enabled = false;
	player->_gameOverUI = gameOver;

	//Lives UI
	std::shared_ptr<GameObject> lifeUI = GameObject::Create();
	std::shared_ptr<LifeUI> lifeUIComponent = lifeUI->AddComponent<LifeUI>();
	player->_lifeUI = lifeUIComponent;

	for (int i = 0; i < player->_lives; i++)
	{
		std::shared_ptr<GameObject> lifeUIelement = GameObject::Create();
		lifeUIelement->_transform->_pivot = Vector2D(0, 0);
		lifeUIelement->_transform->_position = Vector2D(2 + i * 10, Screen::_height - 2);
		lifeUIelement->_transform->_isInScreenSpace = true;
		std::shared_ptr<SpriteRenderer> lifeUIelementRenderer = lifeUIelement->AddComponent<SpriteRenderer>();
		lifeUIelementRenderer->_sprite = Sprite::Create("Assets/Sprites/UI/life.png");
		lifeUIComponent->AddRenderer(lifeUIelementRenderer);
	}
}

void LevelScene::LoadEggplant(Vector2D position)
{
	std::shared_ptr<GameObject> gameObject = GameObject::Create();
	gameObject->_transform->_pivot = Vector2D(0, 1);
	gameObject->_transform->_position = position;
	gameObject->_tag = "Eggplant";
	gameObject->AddComponent<SpriteRenderer>()->_sprite = Sprite::Create("Assets/Sprites/Fruits/eggplant.png");
	gameObject->AddComponent<AABBCollider>()->SetTrigger(true);
}

void LevelScene::LoadCloud(Vector2D position, bool moveRight)
{
	std::shared_ptr<GameObject> gameObject = GameObject::Create();
	gameObject->_transform->_pivot = Vector2D(0.5, 1);
	gameObject->_transform->_position = position;
	gameObject->AddComponent<SpriteRenderer>()->_sprite = Sprite::Create("Assets/Sprites/Environment/cloud.png");
	std::shared_ptr<AABBCollider> stageCollider = gameObject->AddComponent<AABBCollider>();
	stageCollider->SetScale(Vector2D(48, 7));
	gameObject->AddComponent<Cloud>()->SetMoveRight(moveRight);
}

void LevelScene::LoadTimer(std::shared_ptr<PlayerBehaviour> player, Vector2D position)
{
	//1st timer
	std::shared_ptr<GameObject> timerGo = GameObject::Create();
	timerGo->_transform->_pivot = Vector2D(0, 1);
	timerGo->_transform->_position = position;
	std::shared_ptr<BonusTimer> timer = timerGo->AddComponent<BonusTimer>();
	std::shared_ptr<Text> timerText = timerGo->AddComponent<Text>();
	timerText->_text = "40.0";
	timerText->_fontName = "Ice Climber";
	timerText->_tint = Color::IceClimberOrange();
	timerGo->_enabled = false;
	if (player) {
		player->_timers.push_back(timer);
	}
}

void LevelScene::LoadCondor()
{
	std::shared_ptr<GameObject> condorGo = GameObject::Create();
	condorGo->_tag = "Condor";
	condorGo->_transform->_pivot = Vector2D(0.5, 1);
	condorGo->_transform->_position = Vector2D(Screen::_width / 2, 832);
	std::shared_ptr<Animation> condorAnim = condorGo->AddComponent<Animation>();
	condorAnim->_spriteSheet = Sprite::Create("Assets/Sprites/Characters/Condor/fly.png");
	condorAnim->_spriteWidth = 32;
	condorAnim->_frameRate = 8;
	condorAnim->_order = 100;
	std::shared_ptr<AABBCollider> condorCol = condorGo->AddComponent<AABBCollider>();
	condorCol->SetTrigger(true);
	condorCol->SetScale(Vector2D(32, 16));
	std::shared_ptr<Cloud> cloud = condorGo->AddComponent<Cloud>();
	cloud->SetMoveRight(false);
	cloud->SetSpeed(40);
}