// game.cpp
//
// 
// Written by Jake Millhiser
//
// Created to better abstract SDL initialization, and thus allow me to reuse this code.
#include "game.hpp"


SDLGame::SDLGame(const char* aWindowName) {
	// constructor
	gameWindow = nullptr;
	gameRenderer = nullptr;
	strcpy(windowName, aWindowName);
}

SDLGame::SDLGame(const SDLGame &aCopy) {
	// copy constructor
	gameWindow = aCopy.gameWindow;
	gameRenderer = aCopy.gameRenderer;
	strcpy(windowName,aCopy.windowName);
}

SDLGame& SDLGame::operator=(const SDLGame &aCopy) {
	// assignment operator
	gameWindow = aCopy.gameWindow;
	gameRenderer = aCopy.gameRenderer;
	strcpy(windowName,aCopy.windowName);
	return *this;
}

SDLGame::~SDLGame() {
	// Need to destroy allocated memory if it was created.
	if (gameWindow) {
		SDL_DestroyWindow(gameWindow);
	}
	if (gameRenderer) {
		SDL_DestroyRenderer(gameRenderer);
	}
	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
	std::cout << GAME_PROMPT <<" Game has been closed." << std::endl;
}

bool SDLGame::checkQuit(SDL_Event& e) {
	// passing by reference, so no need to give pointer argument.
	if(e.type == SDL_QUIT) return true;
	else return false;
}

void SDLGame::presentRenderer() {
	SDL_RenderPresent(gameRenderer);
	return;
}

bool SDLGame::beginSDL() {
	// standard steps to create SDL window and renderer.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << ERROR_PROMPT << " SDL_Init: " << SDL_GetError() << std::endl;
		return false;
	}
	else {
		// NOTE: not flexable to what settings a person may want.
		gameWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
	}
	if(!gameWindow) {
		std::cerr << ERROR_PROMPT << " SDL_CreateWindow: " << SDL_GetError() << std::endl;
		return false;
	}
	else {
		// NOTE: not flexable to what settings a person may want.
		gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	}
	if(!gameRenderer) {
		std::cerr << ERROR_PROMPT << " SDL_CreateRenderer: " << SDL_GetError() << std::endl;
		return false;
	}
	else {
		return true;
	}
}

bool SDLGame::beginSDL_image() {
	if (!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) {
		std::cerr << ERROR_PROMPT << " SDL_image: " << IMG_GetError() << std::endl;
		return false;
	}
	return true;
}

bool SDLGame::beginSDL_mixer() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)) {
		std::cerr << ERROR_PROMPT << " SDL_mixer: " << Mix_GetError() << std::endl;
		return false;
	}
	return true;
}

bool SDLGame::beginSDL_ttf() {
	if (TTF_Init() == -1) {
		std::cerr << ERROR_PROMPT << " SDL_ttf: " << TTF_GetError() << std::endl;
		return false;
	}
	return true;
}

bool SDLGame::beginSDL_all() {
	if (!beginSDL() || !beginSDL_image() || !beginSDL_mixer() || !beginSDL_ttf()) {
		return false;
	}
	return true;
}

void SDLGame::debug() {
	// Print out the private variables of the game.
	std::cout << CGREEN << "Window Name:\t\t" << CEND << windowName << std::endl;
	std::cout << CGREEN << "SDL_Window Address:\t" << CEND << gameWindow << std::endl;
	std::cout << CGREEN << "SDL_Renderer Address:\t" << CEND << gameRenderer << std::endl;
}
