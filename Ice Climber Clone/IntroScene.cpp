#include "IntroScene.h"
#include "IntroCamera.h"
#include "BonusTimer.h"

void IntroScene::Load()
{
	//Setup Background
	GameObject* background = new GameObject();
	SpriteRenderer* background_render = background->AddComponent<SpriteRenderer>();
	background_render->_sprite = Sprite::Create("Assets/Sprites/Backgrounds/default.png");
	background_render->_order = -100;
	background->_transform->_position = Vector2D(Screen::_width / 2, background_render->_sprite->GetHeight() / 2);

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
			AABBCollider* tileCol = tile->AddComponent<AABBCollider>();
			tileCol->_width = 8;
			tileCol->_height = 7;
		}
	}


	//1st timer
	GameObject* timerGo = new GameObject();
	timerGo->_transform->_pivot = Vector2D(0, 1);
	timerGo->_transform->_position = Vector2D(24, 608);
	BonusTimer* timer = timerGo->AddComponent<BonusTimer>();
	timer->_text = timerGo->AddComponent<Text>();
	timer->_text->_text = "40.0";
	timer->_text->_fontName = "Ice Climber";
	timer->_text->_tint = Color::IceClimberOrange();
	timer->_enabled = false;

	//Setup Condor
	GameObject* condorGo = new GameObject();
	condorGo->_tag = "Condor";
	condorGo->_transform->_pivot = Vector2D(0.5, 0.5);
	condorGo->_transform->_position = Vector2D(Screen::_width / 2, Screen::_height/2);
	condorGo->_transform->_isInScreenSpace = true;
	Animation* condorAnim = condorGo->AddComponent<Animation>();
	condorAnim->_spriteSheet = Sprite::Create("Assets/Sprites/Characters/Condor/fly.png");
	condorAnim->_spriteWidth = 32;
	condorAnim->_frameRate = 8;
	condorAnim->_order = 100;
	condorGo->AddComponent<IntroCamera>();

	GameObject* eggplantGo = new GameObject();
	eggplantGo->_transform->_pivot = Vector2D(0.5, 0.5);
	eggplantGo->_transform->_position = Vector2D(Screen::_width / 2, Screen::_height / 2 - 16);
	eggplantGo->_transform->_isInScreenSpace = true;
	SpriteRenderer* eggplantSprite = eggplantGo->AddComponent<SpriteRenderer>();
	eggplantSprite->_sprite = Sprite::Create("Assets/Sprites/Fruits/eggplant.png");
	eggplantSprite->_order = 100;

	//2nd timer
	timerGo = new GameObject();
	timerGo->_transform->_pivot = Vector2D(0, 1);
	timerGo->_transform->_position = Vector2D(24, 848);
	timer = timerGo->AddComponent<BonusTimer>();
	timer->_text = timerGo->AddComponent<Text>();
	timer->_text->_text = "40.0";
	timer->_text->_fontName = "Ice Climber";
	timer->_text->_tint = Color::IceClimberOrange();
	timer->_enabled = false;
}
