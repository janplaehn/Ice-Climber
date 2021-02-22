#include "game.h"
#include "player.h"
#include "rocket.h"
#include "avancezlib.h"
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

void Game::Create(AvancezLib* engine)
{
	SDL_Log("Game::Create");

	this->engine = engine;

	player = new Player();
	PlayerBehaviourComponent* player_behaviour = new PlayerBehaviourComponent();
	player_behaviour->Create(engine, player, &game_objects, &rockets_pool);
	RenderComponent* player_render = new RenderComponent();
	player_render->Create(engine, player, &game_objects, "data/player.bmp");
	CollideComponent* player_collider = new CollideComponent();
	player_collider->Create(engine, player, &game_objects, bullets_pool.ToGameobjectPool());

	player->Create();
	player->AddComponent(player_behaviour);
	player->AddComponent(player_render);
	player->AddComponent(player_collider);
	player->AddReceiver(this);
	game_objects.insert(player);

	aliens.Create(GameSettings::ALIEN_COLUMNS * GameSettings::ALIEN_ROWS);
	for (Alien* alien : aliens.pool)
	{
		AlienBehaviourComponent* alien_behaviour = new AlienBehaviourComponent();
		alien_behaviour->Create(engine, alien, &game_objects, &bullets_pool);
		RenderComponent* alien_render = new RenderComponent();
		alien_render->Create(engine, alien, &game_objects, "data/enemy_0.bmp");
		CollideComponent* alien_collider = new CollideComponent();
		alien_collider->Create(engine, alien, &game_objects, rockets_pool.ToGameobjectPool());
		alien->Create();
		alien->AddComponent(alien_behaviour);
		alien->AddComponent(alien_render);
		alien->AddComponent(alien_collider);
		alien->AddReceiver(this);
		player->AddReceiver(alien);
		game_objects.insert(alien);
	}

	for (Alien* alien : aliens.pool)
	{
		for (Alien* otherAlien : aliens.pool)
		{
			alien->AddReceiver(otherAlien);
		}
	}


	rockets_pool.Create(GameSettings::MAX_NUM_ROCKETS);
	for (auto rocket = rockets_pool.pool.begin(); rocket != rockets_pool.pool.end(); rocket++)
	{
		bool moveUp = true;
		RocketBehaviourComponent* behaviour = new RocketBehaviourComponent(moveUp);
		behaviour->Create(engine, *rocket, &game_objects);
		RenderComponent* render = new RenderComponent();
		render->Create(engine, *rocket, &game_objects, "data/rocket.bmp");
		(*rocket)->Create();
		(*rocket)->AddComponent(behaviour);
		(*rocket)->AddComponent(render);
	}

	bullets_pool.Create(10);
	for (auto bullet = bullets_pool.pool.begin(); bullet != bullets_pool.pool.end(); bullet++)
	{
		bool moveUp = false;
		RocketBehaviourComponent* behaviour = new RocketBehaviourComponent(moveUp);
		behaviour->Create(engine, *bullet, &game_objects);
		RenderComponent* render = new RenderComponent();
		render->Create(engine, *bullet, &game_objects, "data/bomb.bmp");

		(*bullet)->Create();
		(*bullet)->AddComponent(behaviour);
		(*bullet)->AddComponent(render);
	}


	life_sprite = engine->createSprite("data/player.bmp");
}

void Game::Init()
{
	player->Init();
	SpawnAliens();

	enabled = true;
}

void Game::Update(float dt)
{
	if (!bIsRunning) return;

	AvancezLib::KeyStatus keys;
	engine->getKeyStatus(keys);
	if (keys.esc) {
		Destroy();
		engine->quit();
	}

	if (aliens.AllAvailable()) {
		Send(LEVEL_WIN);
		SpawnAliens();
		GameSettings::time_multiplier *= GameSettings::TIME_ACCELERATOR;
	}

	for (auto go = game_objects.begin(); go != game_objects.end(); go++)
		(*go)->Update(dt);
}

void Game::Draw()
{
	std::string livesText = "Lives: " + std::to_string(player->lives);
	engine->drawText(0, 0, livesText.c_str());

	std::string scoreText = "Score: " + std::to_string(score);
	engine->drawText((int)Screen::WIDTH/2.0f - 20, 0, scoreText.c_str());

	std::stringstream bonusNumber;
	bonusNumber << std::fixed << std::setprecision(1) << GameSettings::time_multiplier;
	std::string bonusText = "Bonus: " + bonusNumber.str() + "x";
	engine->drawText((int)Screen::WIDTH - 80, 0, bonusText.c_str());

	engine->swapBuffers();
	engine->clearWindow();
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
	SDL_Log("Game::Destroy");

	for (auto go = game_objects.begin(); go != game_objects.end(); go++)
		(*go)->Destroy();

	life_sprite->destroy();

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
			alien->horizontalPosition = alienX * Alien::WIDTH;
			alien->verticalPosition = alienY * Alien::WIDTH + Alien::WIDTH;
			alien->Init();
		}
	}
}
