#include "MainMenu.h"
#include "MainMenuController.h"
#include "ComponentEssentials.h"

void MainMenu::Load()
{
	//Setup Background
	GameObject* background = new GameObject();
	SpriteRenderer* background_render = background->AddComponent<SpriteRenderer>();
	background_render->_sprite = Sprite::Create("Assets/Sprites/UI/mainMenu.png");
	background_render->_order = -100;
	background->_transform->_position = Vector2D(Screen::_width / 2, background_render->_sprite->GetHeight() / 2);

	GameObject* menuController = new GameObject();
	menuController->AddComponent<MainMenuController>();

	//Setup background Music
	GameObject* music = new GameObject();
	AudioSource* musicSrc = music->AddComponent<AudioSource>();
	musicSrc->_clip = Audio::LoadSound("Assets/Music/bonus.wav");
	musicSrc->_isLooping = true;
	musicSrc->Play();

	GameObject* textHolder = new GameObject();
	textHolder->_transform->_position = Vector2D(Screen::_width / 2, Screen::_height - 8);
	textHolder->_transform->_pivot = Vector2D(0.5, 0);
	textHolder->_transform->_isInScreenSpace = true;
	Text* text = textHolder->AddComponent<Text>();
	text->_text = "1 PLAYER GAME";
	text->_fontName = "Ice Climber";
	text->_tint = Color::Green();
}
