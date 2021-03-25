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
	std::shared_ptr<GameObject> background = GameObject::Create();
	std::shared_ptr<SpriteRenderer> background_render = background->AddComponent<SpriteRenderer>();
	background_render->_sprite = Sprite::Create("Assets/Sprites/UI/mainMenu.png");
	background_render->_order = -100;
	background->_transform->_position = Vector2D(Screen::_width / 2, background_render->_sprite->GetHeight() / 2);

	//Setup background Music
	std::shared_ptr<GameObject> music = GameObject::Create();
	std::shared_ptr<AudioSource> musicSrc = music->AddComponent<AudioSource>();
	musicSrc->_clip = Audio::LoadSound("Assets/Music/bonus.wav");
	musicSrc->_isLooping = true;
	musicSrc->Play();

	std::shared_ptr<GameObject> navigatorGo = GameObject::Create();
	std::shared_ptr<UINavigator> navigator =  navigatorGo->AddComponent<UINavigator>();

	std::shared_ptr<GameObject> textHolder = GameObject::Create();
	textHolder->_transform->_position = Vector2D(Screen::_width / 2 + 3, Screen::_height / 2 - 16);
	textHolder->_transform->_pivot = Vector2D(0.5, 0);
	textHolder->_transform->_isInScreenSpace = true;
	std::shared_ptr<Button> button = textHolder->AddComponent<IceClimberButton>();
	button->_onPressedFunction = &(Scenes::LoadScene<IntroScene>);
	std::shared_ptr<Text> text = button->_text;
	text->_text = "1 PLAYER GAME";
	text->_fontName = "Ice Climber";
	textHolder->AddComponent<AudioSource>()->_clip = Audio::LoadSound("Assets/Sounds/ui.wav");

	navigator->_buttons.push_back(button);

	textHolder = GameObject::Create();
	textHolder->_transform->_position = Vector2D(Screen::_width / 2 + 3, Screen::_height / 2 - 32);
	textHolder->_transform->_pivot = Vector2D(0.5, 0);
	textHolder->_transform->_isInScreenSpace = true;
	button = textHolder->AddComponent<IceClimberButton>();
	text = button->_text;
	text->_text = "2 PLAYER GAME";
	text->_fontName = "Ice Climber";
	textHolder->AddComponent<AudioSource>()->_clip = Audio::LoadSound("Assets/Sounds/ui.wav");

	navigator->_buttons.push_back(button);

	std::shared_ptr<GameObject> totalCounterGo = GameObject::Create();
	totalCounterGo->_transform->_position = Vector2D(127, 73);
	std::shared_ptr<Text> totalCounter = totalCounterGo->AddComponent<Text>();
	totalCounter->_fontName = "Ice Climber";
	totalCounter->_text = ToString(Scores::CalculateTotal(), 6);
	totalCounter->_tint = Color::IceClimberPink();

	std::shared_ptr<GameObject> totalCounterGo1 = GameObject::Create();
	totalCounterGo1->_transform->_position = Vector2D(71, 57);
	std::shared_ptr<Text> totalCounter1 = totalCounterGo1->AddComponent<Text>();
	totalCounter1->_fontName = "Ice Climber";
	totalCounter1->_text = ToString(Scores::CalculateTotal(), 6);
	totalCounter1->_tint = Color::IceClimberOrange();

	std::shared_ptr<GameObject> totalCounterGo2 = GameObject::Create();
	totalCounterGo2->_transform->_position = Vector2D(183, 57);
	std::shared_ptr<Text> totalCounter2 = totalCounterGo2->AddComponent<Text>();
	totalCounter2->_fontName = "Ice Climber";
	totalCounter2->_text = ToString(0, 6);
	totalCounter2->_tint = Color::IceClimberOrange();

	std::shared_ptr<GameObject> mountainCounterGo = GameObject::Create();
	mountainCounterGo->_transform->_position = Vector2D(Screen::_width / 2 + 31, 73);
	std::shared_ptr<Text> mountainCounter = mountainCounterGo->AddComponent<Text>();
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
