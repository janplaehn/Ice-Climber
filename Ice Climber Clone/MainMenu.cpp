#include "MainMenu.h"
#include "MainMenuController.h"
#include "ComponentEssentials.h"
#include "IceClimberButton.h"
#include <UINavigator.h>

void MainMenu::Load()
{
	//Setup Background
	GameObject* background = new GameObject();
	SpriteRenderer* background_render = background->AddComponent<SpriteRenderer>();
	background_render->_sprite = Sprite::Create("Assets/Sprites/UI/mainMenu.png");
	background_render->_order = -100;
	background->_transform->_position = Vector2D(Screen::_width / 2, background_render->_sprite->GetHeight() / 2);

	GameObject* menuControllerGo = new GameObject();
	MainMenuController* menuController =  menuControllerGo->AddComponent<MainMenuController>();

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
	button->_onPressedFunction = &(MainMenuController::LoadSinglePlayer);
	Text* text = button->_text;
	text->_text = "1 PLAYER GAME";
	text->_fontName = "Ice Climber";

	navigator->_buttons.push_back(button);

	textHolder = new GameObject();
	textHolder->_transform->_position = Vector2D(Screen::_width / 2 + 3, Screen::_height / 2 - 32);
	textHolder->_transform->_pivot = Vector2D(0.5, 0);
	textHolder->_transform->_isInScreenSpace = true;
	button = textHolder->AddComponent<IceClimberButton>();
	text = button->_text;
	text->_text = "2 PLAYER GAME";
	text->_fontName = "Ice Climber";

	navigator->_buttons.push_back(button);
}
