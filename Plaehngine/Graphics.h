#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Vector2D.h"
#include "Color.h"

class Graphics
{
public:

	static void Init(class Game* game);

	static void Run();

	static void Quit();

	static void RenderPoint(Vector2D point, Color tint);

	static void DrawText(TTF_Font* font, Vector2D position, const char* msg, Color tint);

	static void RenderTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect, float angle, SDL_RendererFlip flip, Color tint);

	static SDL_Texture* CreateTexture(const char* path);

	static void DrawRect(SDL_Rect* rect, Color tint);

private:
	static void SwapBuffers();
	static void ClearWindow();

	static SDL_Window* _window;
	static SDL_Renderer* _renderer;
	static bool _isFullscreen;
};

