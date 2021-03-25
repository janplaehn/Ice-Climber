#include "IntroScene.h"
#include "IntroCamera.h"
#include "BonusTimer.h"

void IntroScene::Load()
{
	LoadBackground();

	std::shared_ptr<GameObject> music = GameObject::Create();
	std::shared_ptr<AudioSource> musicSrc = music->AddComponent<AudioSource>();
	musicSrc->_clip = Audio::LoadSound("Assets/Music/intro.wav");
	musicSrc->_isLooping = false;
	musicSrc->Play();

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
	std::shared_ptr<GameObject> condorGo = GameObject::Create();
	condorGo->_tag = "Condor";
	condorGo->_transform->_pivot = Vector2D(0.5, 0.5);
	condorGo->_transform->_position = Vector2D(Screen::_width / 2, Screen::_height / 2);
	condorGo->_transform->_isInScreenSpace = true;
	std::shared_ptr<Animation> condorAnim = condorGo->AddComponent<Animation>();
	condorAnim->_spriteSheet = Sprite::Create("Assets/Sprites/Characters/Condor/fly.png");
	condorAnim->_spriteWidth = 32;
	condorAnim->_frameRate = 8;
	condorAnim->_order = 100;
	condorGo->AddComponent<IntroCamera>();

	std::shared_ptr<GameObject> eggplantGo = GameObject::Create();
	eggplantGo->_transform->_pivot = Vector2D(0.5, 0.5);
	eggplantGo->_transform->_position = Vector2D(Screen::_width / 2, Screen::_height / 2 - 16);
	eggplantGo->_transform->_isInScreenSpace = true;
	std::shared_ptr<SpriteRenderer> eggplantSprite = eggplantGo->AddComponent<SpriteRenderer>();
	eggplantSprite->_sprite = Sprite::Create("Assets/Sprites/Fruits/eggplant.png");
	eggplantSprite->_order = 100;
}

void IntroScene::LoadStaticTimer(Vector2D position)
{
	std::shared_ptr<GameObject> timerGo = GameObject::Create();
	timerGo->_transform->_pivot = Vector2D(0, 1);
	timerGo->_transform->_position = position;
	std::shared_ptr<BonusTimer> timer = timerGo->AddComponent<BonusTimer>();
	std::shared_ptr<Text> text = timerGo->AddComponent<Text>();
	text->_text = "40.0";
	text->_fontName = "Ice Climber";
	text->_tint = Color::IceClimberOrange();
	timer->_enabled = false;
}
