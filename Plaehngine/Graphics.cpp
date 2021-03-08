#include "Graphics.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Vector2D.h"
#include "Camera.h"
#include "Screen.h"
#include "Renderer.h"
#include "SDL_image.h"
#include <iomanip>
#include <sstream>
#include "Physics.h"
#include "Game.h"
#include "Font.h"

void Graphics::Init(Game* game)
{
	Screen::_windowWidth = game->GetWindowSize().x;
	Screen::_windowHeight = game->GetWindowSize().y;
	Screen::_width = game->GetResolution().x;
	Screen::_height = game->GetResolution().y;

	//Create window
	_window = SDL_CreateWindow(game->GetName().c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Screen::_windowWidth, Screen::_windowHeight, SDL_WINDOW_SHOWN);
	if (_window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}
	SDL_Surface* surf = IMG_Load(game->GetIconPath().c_str());
	if (surf != NULL) {
		SDL_SetWindowIcon(_window, surf);
	}

	//Create renderer for window
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}

	SDL_RenderSetLogicalSize(_renderer, Screen::_width, Screen::_height);

	TTF_Init();
	IMG_Init(IMG_INIT_PNG);

	//Initialize renderer color
	//Still: Set this in Camera!
	SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Clear screen
	SDL_RenderClear(_renderer);
}

void Graphics::Run()
{
	//Drawing
	for (Renderer* renderer : Renderer::_renderers) {
		if (renderer->_enabled && renderer->_gameObject->_enabled)
			renderer->Draw();
	}

	//Debug Drawing
	Physics::DrawCollisions();

	//FPS Counter:
	/*if (dt != 0) {
		int fps = 1.0f / dt;
		std::string fpsText = "FPS: " + std::to_string(fps);
		DrawText(Vector2D(0, 0), fpsText.c_str());
	}*/

	SwapBuffers();
	ClearWindow();
}

void Graphics::Quit()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	IMG_Quit();
	Font::UnloadAllFonts();
	TTF_Quit();
}

void Graphics::SwapBuffers() {
	//Update screen
	SDL_RenderPresent(_renderer);
}

void Graphics::ClearWindow() {
	//Clear screen
	//Todo: Have this color in the Camera Settings
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);
}

void Graphics::RenderPoint(Vector2D point, Color tint)
{
	SDL_Rect rect;

	//Apply Position
	rect.x = point.x - Camera::_position.x;
	rect.y = point.y + -Camera::_position.y * -1.0f + Screen::_height;
	rect.w = 1;
	rect.h = 1;

	SDL_SetRenderDrawColor(_renderer, tint.r, tint.g, tint.b, tint.a);
	SDL_RenderDrawRect(_renderer, &rect);
}

void Graphics::DrawText(TTF_Font* font, Vector2D position, const char* msg, Color tint)
{
	SDL_Color sdlColor = { tint.r,tint.g,tint.b};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surf = TTF_RenderText_Solid(font, msg, sdlColor); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* msg_texture = SDL_CreateTextureFromSurface(_renderer, surf); //now you can convert it into a texture

	int w = 0;
	int h = 0;
	SDL_QueryTexture(msg_texture, NULL, NULL, &w, &h);
	SDL_Rect dst_rect = { position.x, position.y, w, h };

	SDL_RenderCopy(_renderer, msg_texture, NULL, &dst_rect);

	SDL_DestroyTexture(msg_texture);
	SDL_FreeSurface(surf);
}

void Graphics::RenderTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect, float angle, SDL_RendererFlip flip, Color tint)
{
	SDL_SetTextureColorMod(texture, tint.r, tint.g, tint.b);
	SDL_RenderCopyEx(_renderer, texture, srcRect, dstRect, angle, NULL /*center*/, flip);
}

SDL_Texture* Graphics::CreateTexture(const char* path)
{
	SDL_Surface* surf = IMG_Load(path);
	if (surf == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load image %s! SDL_image Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	//Create texture from surface pixels
	SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surf);
	if (texture == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(surf);
	return texture;
}

void Graphics::DrawRect(SDL_Rect* rect, Color tint)
{
	SDL_SetRenderDrawColor(_renderer, tint.r, tint.g, tint.b, tint.a);
	SDL_RenderDrawRect(_renderer, rect);
}

SDL_Window* Graphics::_window;
SDL_Renderer* Graphics::_renderer;
