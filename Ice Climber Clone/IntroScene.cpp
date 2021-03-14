#include "IntroScene.h"
#include "IntroCamera.h"
#include "BonusTimer.h"

void IntroScene::Load()
{
	LoadBackground();
	LoadMainStage();
	LoadTopis();
	LoadNitpickers();
	LoadCloud(Vector2D(128, 480), true);
	LoadCloud(Vector2D(128, 608), false);
	LoadStaticTimer(Vector2D(24, 608));
	LoadStaticTimer(Vector2D(24, 848));
	LoadIntroCondor();
}

void IntroScene::LoadIntroCondor()
{
	GameObject* condorGo = new GameObject();
	condorGo->_tag = "Condor";
	condorGo->_transform->_pivot = Vector2D(0.5, 0.5);
	condorGo->_transform->_position = Vector2D(Screen::_width / 2, Screen::_height / 2);
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
}

void IntroScene::LoadStaticTimer(Vector2D position)
{
	GameObject* timerGo = new GameObject();
	timerGo->_transform->_pivot = Vector2D(0, 1);
	timerGo->_transform->_position = position;
	BonusTimer* timer = timerGo->AddComponent<BonusTimer>();
	Text* text = timerGo->AddComponent<Text>();
	text->_text = "40.0";
	text->_fontName = "Ice Climber";
	text->_tint = Color::IceClimberOrange();
	timer->_enabled = false;
}
