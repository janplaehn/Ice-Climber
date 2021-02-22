#include "game.h"
#include "player.h"
#include "rocket.h"
#include "Plaehngine.h"
#include "sprite.h"
#include "alien.h"
#include "AlienBehaviourComponent.h"
#include "RocketBehaviourComponent.h"
#include "collideComponent.h"
#include "gameSettings.h"
#include <string>
#include <iomanip>
#include <sstream>
#include "Screen.h"
#include "Vector2D.h"
#include "Audio.h"
#include "AudioSource.h"
#include "Transform.h"

void Game::Create(class Plaehngine* engine)
{
	this->_engine = engine;

	player = new Player();
	PlayerBehaviourComponent* player_behaviour = player->AddComponent<PlayerBehaviourComponent>();
	player_behaviour->rockets_pool = &rockets_pool;
	RenderComponent* player_render = player->AddComponent<RenderComponent>();
	player_render->_sprite = Sprite::Create("data/player.bmp");
	CollideComponent* player_collider = player->AddComponent<CollideComponent>();
	player_collider->_collisionObjects = bullets_pool.ToGameobjectPool();
	AudioSource* player_audio = player->AddComponent<AudioSource>();
	player_audio->_clip = Audio::LoadSound("Assets/Sounds/sound.wav");

	player->Create(true);
	player->AddReceiver(this);
	_gameObjects.insert(player);

	aliens.Create(GameSettings::ALIEN_COLUMNS * GameSettings::ALIEN_ROWS);
	for (Alien* alien : aliens.pool)
	{
		AlienBehaviourComponent* alien_behaviour = alien->AddComponent<AlienBehaviourComponent>();
		alien_behaviour->Create(&bullets_pool);
		RenderComponent* alien_render = alien->AddComponent<RenderComponent>();
		alien_render->_sprite = Sprite::Create("data/enemy_0.bmp");
		CollideComponent* alien_collider = alien->AddComponent<CollideComponent>();
		alien_collider->_collisionObjects = rockets_pool.ToGameobjectPool();
		alien->Create(true);
		alien->AddReceiver(this);
		player->AddReceiver(alien);
		_gameObjects.insert(alien);
	}

	for (Alien* alien : aliens.pool)
	{
		for (Alien* otherAlien : aliens.pool)
		{
			alien->AddReceiver(otherAlien);
		}
	}


	rockets_pool.Create(GameSettings::MAX_NUM_ROCKETS);
	for (Rocket* rocket : rockets_pool.pool)
	{
		RocketBehaviourComponent* behaviour = rocket->AddComponent<RocketBehaviourComponent>();
		behaviour->bMoveUp = true;
		RenderComponent* render = rocket->AddComponent<RenderComponent>();
		render->_sprite = Sprite::Create("data/rocket.bmp");
		rocket->Create(true);
	}

	bullets_pool.Create(10);
	for (Rocket* bullet : bullets_pool.pool)
	{
		RocketBehaviourComponent* behaviour = bullet->AddComponent<RocketBehaviourComponent>();
		behaviour->bMoveUp = false;
		RenderComponent* render = bullet->AddComponent<RenderComponent>();
		render->_sprite = Sprite::Create("data/bomb.bmp");

		bullet->Create(true);
	}


	life_sprite = Sprite::Create("data/player.bmp");
}

void Game::Init()
{
	player->Init();
	SpawnAliens();

	_enabled = true;
}

void Game::Update(float dt)
{
	if (!bIsRunning) return;

	Plaehngine::KeyStatus keys;
	_engine->GetKeyStatus(keys);
	if (keys._escape) {
		Destroy();
		_engine->Quit();
	}

	if (aliens.AllAvailable()) {
		Send(LEVEL_WIN);
		SpawnAliens();
		GameSettings::time_multiplier *= GameSettings::TIME_ACCELERATOR;
	}

	for (auto go = _gameObjects.begin(); go != _gameObjects.end(); go++)
		(*go)->Update(dt);
}

void Game::Draw()
{
	std::string livesText = "Lives: " + std::to_string(player->lives);
	_engine->DrawText(Vector2D::Zero(), livesText.c_str());

	std::string scoreText = "Score: " + std::to_string(score);
	_engine->DrawText(Vector2D(Screen::WIDTH/2.0f - 20, 0), scoreText.c_str());

	std::stringstream bonusNumber;
	bonusNumber << std::fixed << std::setprecision(1) << GameSettings::time_multiplier;
	std::string bonusText = "Bonus: " + bonusNumber.str() + "x";
	_engine->DrawText(Vector2D(Screen::WIDTH - 80, 0), bonusText.c_str());

	_engine->SwapBuffers();
	_engine->ClearWindow();
}

void Game::Receive(Message m)
{
	if (m == GAME_OVER)
	{
		bIsRunning = false;
	}

	if (m == ALIEN_HIT)
	{
		score += (int)(10 * GameSettings::time_multiplier);
	}

}

void Game::Destroy()
{

	for (auto go = _gameObjects.begin(); go != _gameObjects.end(); go++)
		(*go)->Destroy();

	life_sprite->Destroy();

	rockets_pool.Destroy();
	delete player;
}

void Game::SpawnAliens()
{
	for (int alienX = 0; alienX < GameSettings::ALIEN_COLUMNS; alienX++)
	{
		for (int alienY = 0; alienY < GameSettings::ALIEN_ROWS; alienY++)
		{
			int index = alienX + alienY * GameSettings::ALIEN_COLUMNS;
			if (index >= aliens.pool.size()) return;
			Alien* alien = aliens.pool[index];
			alien->_transform->_position.x = alienX * Alien::WIDTH;
			alien->_transform->_position.y = alienY * Alien::WIDTH + Alien::WIDTH;
			alien->Init();
		}
	}
}
