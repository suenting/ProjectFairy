#include "ScreenDefs.h"
#include "../Core/FontManager.h"
#include "Label.h"
#include "Button.h"
#include "../Simulation/Game.h"
#include "Menu.h"
#include "ThumbStick.h"
#include "ManaBar.h"
#include "PlayerHealth.h"

// navigation
namespace
{
	static void GoToMainMenu()
	{
		Game::Instance().ClearScreen();
		Game::Instance().EnableScreen("main");
		Game::Instance().EndGame();
	}
	static void GoToGameScreen()
	{
		Game::Instance().ClearScreen();
		Game::Instance().EnableScreen("game");
		Game::Instance().InitGame();
	}
	static void GoToWinScreen()
	{
		Game::Instance().ClearScreen();
		Game::Instance().EnableScreen("win");
		Game::Instance().EndGame();
	}
	static void GoToLoseScreen()
	{
		Game::Instance().ClearScreen();
		Game::Instance().EnableScreen("lose");
		Game::Instance().EndGame();
	}
	static void ExitGame()
	{
		exit(0);
	}
}

Screen* SplashScreen()
{
	Screen * screen = new Screen();

	Button* pButton = new Button();
	SDL_Color white = {255,255,255};
	pButton->SetText(FontManager::Instance().GetFont("script"),"Project Fairy",white);
	pButton->SetPosition(Math::Vector2f(300.f,180.f));
	pButton->SetCallback(&GoToMainMenu);
	screen->AddWidget(pButton);

	return screen;
}
Screen* WinScreen()
{
	Screen * screen = new Screen();

	Button* pButton = new Button();
	SDL_Color white = {255,255,255};
	pButton->SetText(FontManager::Instance().GetFont("airstrike"),"YOU WIN",white);
	pButton->SetPosition(Math::Vector2f(350.f,180.f));
	pButton->SetCallback(&GoToMainMenu);
	screen->AddWidget(pButton);

	return screen;
}
Screen* LoseScreen()
{
	Screen * screen = new Screen();

	Button* pButton = new Button();
	SDL_Color white = {255,255,255};
	pButton->SetText(FontManager::Instance().GetFont("airstrike"),"YOU DIED",white);
	pButton->SetPosition(Math::Vector2f(350.f,180.f));
	pButton->SetCallback(&GoToMainMenu);
	screen->AddWidget(pButton);

	return screen;
}

Screen* MainMenu()
{
	Screen * screen = new Screen();
	SDL_Color white = {255,255,255};
	Button* pButton = new Button();
	pButton->SetText(FontManager::Instance().GetFont("airstrike"),"Start Game",white);
	pButton->SetPosition(Math::Vector2f(50.f,200.f));
	pButton->SetCallback(&GoToGameScreen);
	screen->AddWidget(pButton);

	Button* pExit = new Button();
	pExit->SetText(FontManager::Instance().GetFont("airstrike"),"Exit",white);
	pExit->SetPosition(Math::Vector2f(50.f,350.f));
	pExit->SetCallback(&ExitGame);
	screen->AddWidget(pExit);
	return screen;
}

Screen* GameScreen()
{
	Screen * screen = new Screen();

	ThumbStick * pStick = new ThumbStick(Math::Vector2f(84.f,444.f));
	screen->AddWidget(pStick);

	ManaBar * pManaBar = new ManaBar();
	pManaBar->SetPosition(Math::Vector2f(100,10));
	screen->AddWidget(pManaBar);

	PlayerHealth* pPlayerHealth = new PlayerHealth();
	pPlayerHealth->SetPosition(Math::Vector2f(800,480));
	screen->AddWidget(pPlayerHealth);

	Button * pBack = new Button();
	pBack->SetImage("back.png");
	pBack->SetPosition(Math::Vector2f(850,10));
	pBack->SetCallback(&GoToMainMenu);
	screen->AddWidget(pBack);
	return screen;
}