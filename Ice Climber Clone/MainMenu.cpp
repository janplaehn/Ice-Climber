#include "MainMenu.h"
#include "ComponentEssentials.h"
#include "IceClimberButton.h"
#include "UINavigator.h"
#include "Scores.h"
#include "ScoreScene.h"
#include "Scenes.h"
#include "IntroScene.h"

void MainMenu::Load()
{
	//Setup Background
	GameObject* background = new GameObject();
	SpriteRenderer* background_render = background->AddComponent<SpriteRenderer>();
	background_render->_sprite = Sprite::Create("Assets/Sprites/UI/mainMenu.png");
	background_render->_order = -100;
	background->_transform->_position = Vector2D(Screen::_width / 2, background_render->_sprite->GetHeight() / 2);

	//Setup background Music
	GameObject* music = new GameObject();
	AudioSource* musicSrc = music->AddComponent<AudioSource>();
	musicSrc->_clip = Audio::LoadSound("Assets/Music/bonus.wav");
	musicSrc->_isLooping = true;
	musicSrc->Play();

	GameObject* navigatorGo = new GameObject();
	UINavigator* navigator =  navigatorGo->AddComponent<UINavigator>();

	GameObject* textHolder = new GameObject();
	textHolder->_transform->_position = Vector2D(Screen::_width / 2 + 3, Screen::_height / 2 - 16);
	textHolder->_transform->_pivot = Vector2D(0.5, 0);
	textHolder->_transform->_isInScreenSpace = true;
	Button* button = textHolder->AddComponent<IceClimberButton>();
	button->_onPressedFunction = &(Scenes::LoadScene<IntroScene>);
	Text* text = button->_text;
	text->_text = "1 PLAYER GAME";
	text->_fontName = "Ice Climber";
	textHolder->AddComponent<AudioSource>()->_clip = Audio::LoadSound("Assets/Sounds/ui.wav");

	navigator->_buttons.push_back(button);

	textHolder = new GameObject();
	textHolder->_transform->_position = Vector2D(Screen::_width / 2 + 3, Screen::_height / 2 - 32);
	textHolder->_transform->_pivot = Vector2D(0.5, 0);
	textHolder->_transform->_isInScreenSpace = true;
	button = textHolder->AddComponent<IceClimberButton>();
	text = button->_text;
	text->_text = "2 PLAYER GAME";
	text->_fontName = "Ice Climber";
	textHolder->AddComponent<AudioSource>()->_clip = Audio::LoadSound("Assets/Sounds/ui.wav");

	navigator->_buttons.push_back(button);

	GameObject* totalCounterGo = new GameObject();
	totalCounterGo->_transform->_position = Vector2D(127, 73);
	Text* totalCounter = totalCounterGo->AddComponent<Text>();
	totalCounter->_fontName = "Ice Climber";
	totalCounter->_text = ToString(Scores::CalculateTotal(), 6);
	totalCounter->_tint = Color::IceClimberPink();

	GameObject* totalCounterGo1 = new GameObject();
	totalCounterGo1->_transform->_position = Vector2D(71, 57);
	Text* totalCounter1 = totalCounterGo1->AddComponent<Text>();
	totalCounter1->_fontName = "Ice Climber";
	totalCounter1->_text = ToString(Scores::CalculateTotal(), 6);
	totalCounter1->_tint = Color::IceClimberOrange();

	GameObject* totalCounterGo2 = new GameObject();
	totalCounterGo2->_transform->_position = Vector2D(183, 57);
	Text* totalCounter2 = totalCounterGo2->AddComponent<Text>();
	totalCounter2->_fontName = "Ice Climber";
	totalCounter2->_text = ToString(0, 6);
	totalCounter2->_tint = Color::IceClimberOrange();

	GameObject* mountainCounterGo = new GameObject();
	mountainCounterGo->_transform->_position = Vector2D(Screen::_width / 2 + 31, 73);
	Text* mountainCounter = mountainCounterGo->AddComponent<Text>();
	mountainCounter->_fontName = "Ice Climber";
	mountainCounter->_text = ToString(ScoreScene::_mountainIndex, 2);
	mountainCounter->_tint = Color::IceClimberBlue();
}

std::string MainMenu::ToString(int number, int digitCount)
{
	std::string string = std::to_string(number);
	int length = string.size();
	for (int i = 0; i < digitCount - length; i++)
	{
		string = '0' + string;
	}
	return string;
}
