#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

#define SCREEN_W 640 
#define SCREEN_H 480
#define TITLE_SIZE 100

// colors
#define CGREEN "\e[32m"
#define CBLUE  "\e[34m"
#define CRED "\e[31m"
#define CEND "\e[0m"
#define GAME_PROMPT "\e[33mPONG:\e[0m"
#define ERROR_PROMPT "\e[31m[ERROR]\e[0m"
#define CLEAR "\033c"


class SDLGame {
public:
	SDLGame(const char* aWindowName = "SDL2 Game");
	SDLGame(const SDLGame &aCopy);
	SDLGame& operator=(const SDLGame &aCopy);

	bool beginSDL();
	bool beginSDL_image();
	bool beginSDL_mixer();
	bool beginSDL_ttf();
	bool beginSDL_all();
	bool checkQuit(SDL_Event& e);
	void presentRenderer();
	void debug();

	~SDLGame();
protected:
	char windowName[TITLE_SIZE];
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
};


#endif
