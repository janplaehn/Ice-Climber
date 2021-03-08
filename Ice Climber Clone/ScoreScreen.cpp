#include "ScoreScreen.h"
#include "Scores.h"
#include "ScoreScreenController.h"

void ScoreScreen::Load()
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
	mountainCounter->_fontName = "Ice Climber";
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
	eggplantCounterGo->_transform->_position = Vector2D(104, 129);
	Text* eggplantCounter = eggplantCounterGo->AddComponent<Text>();
	eggplantCounter->_fontName = "Ice Climber";
	eggplantCounter->_text = ToString(Scores::_eggplants,2);

	GameObject* iceCounterGo = new GameObject();
	iceCounterGo->_transform->_position = Vector2D(104, 113);
	Text* iceCounter = iceCounterGo->AddComponent<Text>();
	iceCounter->_fontName = "Ice Climber";
	iceCounter->_text = ToString(Scores::_ice, 2);

	GameObject* nitpickerCounterGo = new GameObject();
	nitpickerCounterGo->_transform->_position = Vector2D(104, 97);
	Text* nitpickerCounter = nitpickerCounterGo->AddComponent<Text>();
	nitpickerCounter->_fontName = "Ice Climber";
	nitpickerCounter->_text = ToString(Scores::_nitpickers, 2);

	GameObject* tileCounterGo = new GameObject();
	tileCounterGo->_transform->_position = Vector2D(104, 81);
	Text* tileCounter = tileCounterGo->AddComponent<Text>();
	tileCounter->_fontName = "Ice Climber";
	tileCounter->_text = ToString(Scores::_tiles, 2);

	GameObject* totalCounterGo = new GameObject();
	totalCounterGo->_transform->_position = Vector2D(72, 57);
	Text* totalCounter = totalCounterGo->AddComponent<Text>();
	totalCounter->_fontName = "Ice Climber";
	totalCounter->_text = ToString(Scores::CalculateTotal(), 6);
	_mountainIndex++;
}

std::string ScoreScreen::ToString(int number, int digitCount)
{
	std::string string = std::to_string(number);
	int length = string.size();
	for (int i = 0; i < digitCount - length; i++)
	{
		string = '0' + string;
	}
	return string;
}

int ScoreScreen::_mountainIndex = 1;
