#include "Plaehngine.h"
#include "sprite.h"
#include "Random.h"
#include "Vector2D.h"
#include "Audio.h"


//Todo: Split this properly into classes
//Todo: Add A Config to initialize this
//Todo: Add Scene Hierarchies to set up
//Todo: Add More Window Options stuffs
//Todo: Add Player Settings (Name, etc.)
//Todo: Initialize Fonts somewhere else (Make AssetDatabase or something)

// Creates the main window. Returns true on success.
bool Plaehngine::Init(int width, int height)
{
	SDL_Log("Initializing the engine...\n");

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL failed the initialization: %s\n", SDL_GetError());
		return false;
	}

	//Create window
	_window = SDL_CreateWindow("aVANCEZ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
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
	Sprite::_renderer = _renderer;

	TTF_Init();
	_font = TTF_OpenFont("data/space_invaders.ttf", 12); //this opens a font style and sets a size
	if (_font == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "font cannot be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// initialize the keys
	_key._fire = false;	_key._left = false;	_key._right = false, _key._escape = false;

	//Initialize renderer color
	SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Clear screen
	SDL_RenderClear(_renderer);

	Audio::Init();
	Random::Init();


	SDL_Log("Engine up and running...\n");
	return true;
}


// Destroys the Plaehngine instance
void Plaehngine::Destroy()
{
	SDL_Log("Shutting down the engine\n");

	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);

	TTF_CloseFont(_font);

	Audio::Quit();
	TTF_Quit();
	SDL_Quit();
}

void Plaehngine::Quit() {
	Destroy();
	exit(0);
}


void Plaehngine::ProcessInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
			case SDLK_q:
				_key._escape = true;
				break;
			case SDLK_SPACE:
				_key._fire = true;
				break;
			case SDLK_LEFT:
				_key._left = true;
				break;
			case SDLK_RIGHT:
				_key._right = true;
				break;
			}
		}

		if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				_key._fire = false;
				break;
			case SDLK_LEFT:
				_key._left = false;
				break;
			case SDLK_RIGHT:
				_key._right = false;
				break;
			}
		}

	}
}

void Plaehngine::SwapBuffers() {
	//Update screen
	SDL_RenderPresent(_renderer);
}

void Plaehngine::ClearWindow() {
	//Clear screen
	SDL_RenderClear(_renderer);
}

void Plaehngine::DrawText(Vector2D position, const char * msg)
{
	SDL_Color black = { 0, 0, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surf = TTF_RenderText_Solid(_font, msg, black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* msg_texture = SDL_CreateTextureFromSurface(_renderer, surf); //now you can convert it into a texture

	int w = 0;
	int h = 0;
	SDL_QueryTexture(msg_texture, NULL, NULL, &w, &h);
	SDL_Rect dst_rect = {position.x, position.y, w, h };

	SDL_RenderCopy(_renderer, msg_texture, NULL, &dst_rect);

	SDL_DestroyTexture(msg_texture);
	SDL_FreeSurface(surf);
}

float Plaehngine::GetElapsedTime()
{
	return SDL_GetTicks() / 1000.f;
}

void Plaehngine::GetKeyStatus(KeyStatus & keys)
{
	keys._fire = _key._fire;
	keys._left = _key._left;
	keys._right = _key._right;
	keys._escape = _key._escape;
}

