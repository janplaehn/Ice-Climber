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
	Text* text = textHolder->AddComponent<Text>();
	text->_text = "This is a test text";
	text->_fontName = "Retro";
}
