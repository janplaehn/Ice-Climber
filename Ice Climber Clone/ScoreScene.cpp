#include "ScoreScene.h"
#include "Scores.h"
#include "ScoreScreenController.h"
#include "Counter.h"
#include "AudioSource.h"

void ScoreScene::Load()
{
	//Setup Background
	std::shared_ptr<GameObject> background = GameObject::Create();
	std::shared_ptr<SpriteRenderer> background_render = background->AddComponent<SpriteRenderer>();
	background_render->_sprite = Sprite::Create("Assets/Sprites/UI/scoreScreen.png");
	background_render->_order = -100;
	background->_transform->_position = Vector2D(Screen::_width / 2, background_render->_sprite->GetHeight() / 2);

	std::shared_ptr<GameObject> mountainCounterGo = GameObject::Create();
	mountainCounterGo->_transform->_position = Vector2D(Screen::_width / 2 + 32, Screen::_height - 31);
	std::shared_ptr<Text> mountainCounter =  mountainCounterGo->AddComponent<Text>();
	mountainCounter->_fontName = "Ice Climber";
	mountainCounter->_text = ToString(_mountainIndex, 2);

	if (Scores::_hasBonus) {
		std::shared_ptr<GameObject> bonusGo = GameObject::Create();
		bonusGo->_transform->_position = Vector2D(88, 156);
		std::shared_ptr<SpriteRenderer> bonusSprite = bonusGo->AddComponent<SpriteRenderer>();
		bonusSprite->_sprite = Sprite::Create("Assets/Sprites/UI/winnerBonus.png");
		bonusSprite->_order = -99;

		std::shared_ptr<GameObject> winGo = GameObject::Create();
		winGo->_transform->_position = Vector2D(48, 156);
		std::shared_ptr<Animation> winAnim = winGo->AddComponent<Animation>();
		winAnim->_spriteSheet = Sprite::Create("Assets/Sprites/Characters/Popo/win.png");
		winAnim->_spriteWidth = 24;
		winAnim->_frameRate = 3;
	}
	else {
		std::shared_ptr<GameObject> loseGo = GameObject::Create();
		loseGo->_transform->_position = Vector2D(48, 156);
		std::shared_ptr<Animation> loseAnim = loseGo->AddComponent<Animation>();
		loseAnim->_spriteSheet = Sprite::Create("Assets/Sprites/Characters/Popo/lose.png");
		loseAnim->_spriteWidth = 16;
		loseAnim->_frameRate = 5;
	}

	std::shared_ptr<GameObject> go = GameObject::Create();
	go->AddComponent<ScoreScreenController>();

	std::shared_ptr<GameObject> eggplantCounterGo = GameObject::Create();
	std::shared_ptr<Counter> eggplantCounterCounter = eggplantCounterGo->AddComponent<Counter>();
	eggplantCounterGo->_transform->_position = Vector2D(104, 129);
	std::shared_ptr<Text> eggplantCounter = eggplantCounterGo->AddComponent<Text>();
	eggplantCounter->_fontName = "Ice Climber";
	eggplantCounterCounter->SetDigitCount(2);
	eggplantCounterCounter->SetDelay(0.5f);
	eggplantCounterCounter->SetTargetNumber(Scores::_eggplants);
	std::shared_ptr<AudioSource> source = eggplantCounterGo->AddComponent<AudioSource>();
	source->_isLooping = true;
	source->_clip = Audio::LoadSound("Assets/Sounds/ui.wav");

	std::shared_ptr<GameObject> iceCounterGo = GameObject::Create();
	std::shared_ptr<Counter> iceCounterCounter = iceCounterGo->AddComponent<Counter>();
	iceCounterGo->_transform->_position = Vector2D(104, 113);
	std::shared_ptr<Text> iceCounter = iceCounterGo->AddComponent<Text>();
	iceCounter->_fontName = "Ice Climber";
	iceCounterCounter->SetDigitCount(2);
	iceCounterCounter->SetDelay(1.0f);
	iceCounterCounter->SetTargetNumber(Scores::_ice);
	source = iceCounterGo->AddComponent<AudioSource>();
	source->_isLooping = true;
	source->_clip = Audio::LoadSound("Assets/Sounds/ui.wav");

	std::shared_ptr<GameObject> nitpickerCounterGo = GameObject::Create();
	nitpickerCounterGo->_transform->_position = Vector2D(104, 97);
	std::shared_ptr<Counter> nitCounterCounter = nitpickerCounterGo->AddComponent<Counter>();
	std::shared_ptr<Text> nitpickerCounter = nitpickerCounterGo->AddComponent<Text>();
	nitpickerCounter->_fontName = "Ice Climber";
	nitCounterCounter->SetDigitCount(2);
	nitCounterCounter->SetDelay(1.5f);
	nitCounterCounter->SetTargetNumber(Scores::_nitpickers);
	source = nitpickerCounterGo->AddComponent<AudioSource>();
	source->_isLooping = true;
	source->_clip = Audio::LoadSound("Assets/Sounds/ui.wav");

	std::shared_ptr<GameObject> tileCounterGo = GameObject::Create();
	tileCounterGo->_transform->_position = Vector2D(104, 81);
	std::shared_ptr<Counter> tileCounterCounter = tileCounterGo->AddComponent<Counter>();
	std::shared_ptr<Text> tileCounter = tileCounterGo->AddComponent<Text>();
	tileCounter->_fontName = "Ice Climber";
	tileCounterCounter->SetDigitCount(2);
	tileCounterCounter->SetDelay(2.0f);
	tileCounterCounter->SetTargetNumber(Scores::_tiles);
	source = tileCounterGo->AddComponent<AudioSource>();
	source->_isLooping = true;
	source->_clip = Audio::LoadSound("Assets/Sounds/ui.wav");

	std::shared_ptr<GameObject> totalCounterGo = GameObject::Create();
	totalCounterGo->_transform->_position = Vector2D(72, 57);
	std::shared_ptr<Counter> totalCounterCounter =  totalCounterGo->AddComponent<Counter>();
	std::shared_ptr<Text> totalCounter = totalCounterGo->AddComponent<Text>();
	totalCounter->_fontName = "Ice Climber";
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
