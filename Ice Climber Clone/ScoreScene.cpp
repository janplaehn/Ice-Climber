#include "ScoreScene.h"
#include "Scores.h"
#include "ScoreScreenController.h"
#include "Counter.h"
#include "AudioSource.h"

void ScoreScene::Load()
{
	//Setup Background
	GameObject* background = new GameObject();
	SpriteRenderer* background_render = background->AddComponent<SpriteRenderer>();
	background_render->_sprite = Sprite::Create("Assets/Sprites/UI/scoreScreen.png");
	background_render->_order = -100;
	background->_transform->_position = Vector2D(Screen::_width / 2, background_render->_sprite->GetHeight() / 2);

	GameObject* mountainCounterGo = new GameObject();
	mountainCounterGo->_transform->_position = Vector2D(Screen::_width / 2 + 32, Screen::_height - 31);
	Text* mountainCounter =  mountainCounterGo->AddComponent<Text>();
	mountainCounter->SetFont("Ice Climber");
	mountainCounter->_text = ToString(_mountainIndex, 2);

	if (Scores::_hasBonus) {
		GameObject* bonusGo = new GameObject();
		bonusGo->_transform->_position = Vector2D(88, 156);
		SpriteRenderer* bonusSprite = bonusGo->AddComponent<SpriteRenderer>();
		bonusSprite->_sprite = Sprite::Create("Assets/Sprites/UI/winnerBonus.png");
		bonusSprite->_order = -99;

		GameObject* winGo = new GameObject();
		winGo->_transform->_position = Vector2D(48, 156);
		Animation* winAnim = winGo->AddComponent<Animation>();
		winAnim->_spriteSheet = Sprite::Create("Assets/Sprites/Characters/Popo/win.png");
		winAnim->_spriteWidth = 24;
		winAnim->_frameRate = 3;
	}
	else {
		GameObject* loseGo = new GameObject();
		loseGo->_transform->_position = Vector2D(48, 156);
		Animation* loseAnim = loseGo->AddComponent<Animation>();
		loseAnim->_spriteSheet = Sprite::Create("Assets/Sprites/Characters/Popo/lose.png");
		loseAnim->_spriteWidth = 16;
		loseAnim->_frameRate = 5;
	}

	GameObject* go = new GameObject();
	go->AddComponent<ScoreScreenController>();

	GameObject* eggplantCounterGo = new GameObject();
	Counter* eggplantCounterCounter = eggplantCounterGo->AddComponent<Counter>();
	eggplantCounterGo->_transform->_position = Vector2D(104, 129);
	Text* eggplantCounter = eggplantCounterGo->AddComponent<Text>();
	eggplantCounter->SetFont("Ice Climber");
	eggplantCounterCounter->SetDigitCount(2);
	eggplantCounterCounter->SetDelay(0.5f);
	eggplantCounterCounter->SetTargetNumber(Scores::_eggplants);
	AudioSource* source = eggplantCounterGo->AddComponent<AudioSource>();
	source->_isLooping = true;
	source->_clip = Audio::LoadSound("Assets/Sounds/ui.wav");

	GameObject* iceCounterGo = new GameObject();
	Counter* iceCounterCounter = iceCounterGo->AddComponent<Counter>();
	iceCounterGo->_transform->_position = Vector2D(104, 113);
	Text* iceCounter = iceCounterGo->AddComponent<Text>();
	iceCounter->SetFont("Ice Climber");
	iceCounterCounter->SetDigitCount(2);
	iceCounterCounter->SetDelay(1.0f);
	iceCounterCounter->SetTargetNumber(Scores::_ice);
	source = iceCounterGo->AddComponent<AudioSource>();
	source->_isLooping = true;
	source->_clip = Audio::LoadSound("Assets/Sounds/ui.wav");

	GameObject* nitpickerCounterGo = new GameObject();
	nitpickerCounterGo->_transform->_position = Vector2D(104, 97);
	Counter* nitCounterCounter = nitpickerCounterGo->AddComponent<Counter>();
	Text* nitpickerCounter = nitpickerCounterGo->AddComponent<Text>();
	nitpickerCounter->SetFont("Ice Climber");
	nitCounterCounter->SetDigitCount(2);
	nitCounterCounter->SetDelay(1.5f);
	nitCounterCounter->SetTargetNumber(Scores::_nitpickers);
	source = nitpickerCounterGo->AddComponent<AudioSource>();
	source->_isLooping = true;
	source->_clip = Audio::LoadSound("Assets/Sounds/ui.wav");

	GameObject* tileCounterGo = new GameObject();
	tileCounterGo->_transform->_position = Vector2D(104, 81);
	Counter* tileCounterCounter = tileCounterGo->AddComponent<Counter>();
	Text* tileCounter = tileCounterGo->AddComponent<Text>();
	tileCounter->SetFont("Ice Climber");
	tileCounterCounter->SetDigitCount(2);
	tileCounterCounter->SetDelay(2.0f);
	tileCounterCounter->SetTargetNumber(Scores::_tiles);
	source = tileCounterGo->AddComponent<AudioSource>();
	source->_isLooping = true;
	source->_clip = Audio::LoadSound("Assets/Sounds/ui.wav");

	GameObject* totalCounterGo = new GameObject();
	totalCounterGo->_transform->_position = Vector2D(72, 57);
	Counter* totalCounterCounter =  totalCounterGo->AddComponent<Counter>();
	Text* totalCounter = totalCounterGo->AddComponent<Text>();
	totalCounter->SetFont("Ice Climber");
	totalCounterCounter->SetDigitCount(6);
	totalCounterCounter->SetDelay(2.5f);
	totalCounterCounter->SetTargetNumber(Scores::CalculateTotal());
	totalCounterCounter->SetSpeed(1.5f);
	source = totalCounterGo->AddComponent<AudioSource>();
	source->_isLooping = true;
	source->_clip = Audio::LoadSound("Assets/Sounds/ui.wav");
	_mountainIndex++;
}

std::string ScoreScene::ToString(int number, int digitCount)
{
	std::string string = std::to_string(number);
	int length = string.size();
	for (int i = 0; i < digitCount - length; i++)
	{
		string = '0' + string;
	}
	return string;
}

int ScoreScene::_mountainIndex = 1;
