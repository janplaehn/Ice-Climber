#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Vector2D.h"

class Graphics
{
public:

	static void Init(class Game* game);

	static void Run();

	static void Quit();

	static void RenderPoint(Vector2D point);

	static void DrawText(Vector2D position, const char* msg);

	static void RenderTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect, float angle, SDL_RendererFlip flip);

	static SDL_Texture* CreateTexture(const char* path);

	static void DrawRect(SDL_Rect* rect, int r, int g, int b, int a);

private:
	static void SwapBuffers();
	static void ClearWindow();

	static SDL_Window* _window;
	static TTF_Font* _font;
	static SDL_Renderer* _renderer;
};
