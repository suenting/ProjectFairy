#ifndef GAME_H
#define GAME_H
#include "../pch.h"
#include "../UI/Screen.h"
#include "Player.h"
#include "Actor.h"
#include "../UI/ManaBar.h"

class Game
{
public:
	static Game& Instance()
	{
		static Game instance;
		return instance;
	}

	~Game();
	void Render()const;
	void Input(SDL_Event &rSDL_Event);
	void Update();

	// UI
	void EnableScreen(std::string screenname);
	void DisableScreen(std::string screenname);
	void FrontScreen(std::string screenname);
	void ClearScreen();

	int GetPlayerHealth()const;
	float GetHealthPercentage()const;

	// 
	void AddPlayerProjectile(Projectile* projectile) { mPlayerProjectiles.push_back(projectile); }
	void AddProjectile(Projectile* projectile) { mProjectileList.push_back(projectile); }
	void QueueProjectile(Projectile* projectile) {mProjectileQueue.push_back(projectile);}
	void QueueActor(Actor* actor){mActorQueue.push_back(actor);}

	//
	void QueueEffect(Effect* effect);

	// 
	void InitGame();
	void EndGame();
	int GetRandom(){return rand();}
private:
	Game();
	Game( const Game& other ){};
	Game& operator=( const Game& rhs ){};

	// UI
	void LoadScreens();
	bool mbGameScreenActive;
	std::vector<Screen*> mActiveScreens;
	std::map<std::string,Screen*> mScreens;

	// gameplay ui
	ManaBar *mpManaBar;// weak pointer to mana bar

	// simulation
	Player mPlayer; // single player
	std::vector<Projectile*> mPlayerProjectiles;

	// 
	std::vector<Actor*> mActorList;
	std::vector<Actor*> mActorQueue;
	std::vector<Projectile*> mProjectileList;
	std::vector<Projectile*> mProjectileQueue;
	
	std::vector<Effect*> mEffectQueue;
	std::vector<Effect*> mEffectList;
};

#endif
