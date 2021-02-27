#include "Plaehngine.h"
#include "sprite.h"
#include "Random.h"
#include "Vector2D.h"
#include "Audio.h"
#include "Input.h"
#include "GameTime.h"
#include "Game.h"
#include "Screen.h"
#include "SDL_image.h"
#include "SpriteRenderer.h"
#include <iomanip>
#include <sstream>
#include "Physics.h"
#include "Renderer.h"


//Todo: Add A Config to initialize this
//Todo: Add Scene Hierarchies to set up
//Todo: Add More Window Options stuffs
//Todo: Add Player Settings (Name, etc.)
//Todo: Initialize Fonts somewhere else (Make AssetDatabase or something)

// Creates the main window. Returns true on success.
bool Plaehngine::Init(Game* game)
{
	SDL_Log("Initializing the engine...\n");

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL failed the initialization: %s\n", SDL_GetError());
		return false;
	}

	//Create window
	_window = SDL_CreateWindow("TODO: SET GAME NAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Screen::WINDOWWIDTH, Screen::WINDOWHEIGHT, SDL_WINDOW_SHOWN);
	if (_window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	
	//Create renderer for window
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_RenderSetLogicalSize(_renderer, Screen::WIDTH, Screen::HEIGHT);

	Sprite::_renderer = _renderer;

	TTF_Init();
	_font = TTF_OpenFont("data/space_invaders.ttf", 10); //this opens a font style and sets a size
	if (_font == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "font cannot be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	IMG_Init(IMG_INIT_PNG);

	

	//Initialize renderer color
	SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Clear screen
	SDL_RenderClear(_renderer);

	Input::Init();
	Audio::Init();
	Random::Init();


	SDL_Log("Engine up and running...\n");

	_game = game;
	_game->Create(this);
	_game->Init();

	return true;
}


// Destroys the Plaehngine instance (move this maybe?)
void Plaehngine::Destroy()
{
	// clean up
	_game->Destroy();

	for (int i = GameObject::_gameObjects.size() - 1; i >= 0; i--)
	{
		if (GameObject::_gameObjects[i] != nullptr) {
			GameObject::_gameObjects[i]->Destroy();
		}
	}

	SDL_Log("Shutting down the engine\n");

	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);

	TTF_CloseFont(_font);

	Audio::Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void Plaehngine::Quit() {
	Destroy();
	exit(0);
}

void Plaehngine::SwapBuffers() {
	//Update screen
	SDL_RenderPresent(_renderer);
}

void Plaehngine::ClearWindow() {
	//Clear screen
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);
}

void Plaehngine::Run()
{
	//Todo: Move all of this to Engine::Run
	float lastTime = GameTime::GetElapsedTime();
	while (true)
	{
		float newTime = GameTime::GetElapsedTime();
		float dt = newTime - lastTime;
		dt = dt * GameTime::_timeScale;
		lastTime = newTime;

		Input::ProcessInput();
		_game->Update(dt);

		for (auto go = GameObject::_gameObjects.begin(); go != GameObject::_gameObjects.end(); go++)
			(*go)->Update(dt);

		Physics::Run();

		//Drawing
		for (Renderer* renderer : Renderer::_renderers) {
			renderer->Draw();
		}

		//Debug Drawing
		//Physics::DrawCollisions();

		//FPS Counter:
		/*if (dt != 0) {
			int fps = 1.0f / dt;
			std::string fpsText = "FPS: " + std::to_string(fps);
			DrawText(Vector2D(0, 0), fpsText.c_str());
		}*/


		SwapBuffers();
		ClearWindow();

		if (dt < (1.0f / 60.0f)) {
			int delay = (int)((1.0f / 60.0f - dt) * 1000.0f);
			SDL_Delay(delay);
		}
	}
}

void Plaehngine::DrawText(Vector2D position, const char * msg)
{
	SDL_Color white = {255,255,255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surf = TTF_RenderText_Solid(_font, msg, white); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* msg_texture = SDL_CreateTextureFromSurface(_renderer, surf); //now you can convert it into a texture

	int w = 0;
	int h = 0;
	SDL_QueryTexture(msg_texture, NULL, NULL, &w, &h);
	SDL_Rect dst_rect = {position.x, position.y, w, h };

	SDL_RenderCopy(_renderer, msg_texture, NULL, &dst_rect);

	SDL_DestroyTexture(msg_texture);
	SDL_FreeSurface(surf);
}

