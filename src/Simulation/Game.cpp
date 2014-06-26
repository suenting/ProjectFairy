#include "Game.h"
#include "../UI/ScreenDefs.h"
#include "../Core/ResourceManager.h"
#include "ModContentManager.h"
#include "../Core/InputManager.h"
#include "Projectile.h"

namespace
{
	static bool ProjectileIsDead(Projectile * pProjectile)
	{
		if(pProjectile->GetIsDead())
		{
			delete pProjectile;
			return true;
		}
		return false;
	}
	static bool ActorIsDead(Actor * pActor)
	{
		if(pActor->GetIsDead())
		{
			delete pActor;
			return true;
		}
		return false;
	}
	static bool EffectIsDead(Effect * pEffect)
	{
		if(0!=pEffect->GetTimeToLive())
		{
			if(pEffect->GetTick()>pEffect->GetTimeToLive())
			{
				delete pEffect;
				return true;
			}
		}
		return false;
	}

	template<typename T>
	static void UpdateVector(T vec)
	{
		for(typename T::iterator it = vec.begin(); it != vec.end();++it)
		{
			(*it)->Update();
		}
	}

	template<typename T>
	static void RenderVector(T vec)
	{
		for(typename T::const_iterator it = vec.begin(); it != vec.end();++it)
		{
			(*it)->Render();
		}
	}

	template<typename T>
	static void ClearVector(T vec)
	{
		for(typename T::iterator it = vec.begin(); it != vec.end();++it)
		{
			delete (*it);
		}
		vec.clear();
	}

}

Game::Game()
{
	srand(time(NULL));
	ModContentManager::Instance().LoadGameData();
	LoadScreens();
	mbGameScreenActive = false;
}

Game::~Game()
{
	for(std::map<std::string,Screen*>::iterator it = mScreens.begin(); it != mScreens.end();++it)
	{
		delete (it->second);
	}
}

void Game::Render() const
{

	if(mbGameScreenActive)
	{
		SDL_SetRenderDrawColor(ResourceManager::Instance().GetRenderer(), 0x00, 0x00, 0x00, 0xFF);
	}
	else
	{
		SDL_SetRenderDrawColor(ResourceManager::Instance().GetRenderer(), 0x00, 0x00, 0x00, 0xFF);
	}
	SDL_RenderClear(ResourceManager::Instance().GetRenderer());

	if(mbGameScreenActive)
	{
		// draw player
		mPlayer.Render();

		// draw effects
		RenderVector< std::vector<Effect*> >(mEffectList);

		// draw projectiles
		RenderVector< std::vector<Projectile*> >(mPlayerProjectiles);
		RenderVector< std::vector<Projectile*> >(mProjectileList);

		// draw enemy
		RenderVector< std::vector<Actor*> >(mActorList);
	}

	// draw screens / UI
	for(std::vector<Screen*>::const_iterator it = mActiveScreens.begin(); it != mActiveScreens.end();++it)
	{
		(*it)->Render();
	}	
}

void Game::Update()
{
	InputManager::Instance().UpdatePosition();

	// update UI
	
	for(std::vector<Screen*>::const_iterator it = mActiveScreens.begin(); it != mActiveScreens.end();++it)
	{
		(*it)->Update();
	}
	if(!mbGameScreenActive)
	{
		return;
	}
	mPlayer.Update();

	// update actor
	UpdateVector< std::vector<Actor*> >(mActorList);

	// process actor queue
	for(std::vector<Actor*>::iterator it = mActorQueue.begin(); it != mActorQueue.end();++it)
	{
		mActorList.push_back(*it);
	}
	mActorQueue.clear();

	// update effects
	UpdateVector< std::vector<Effect*> >(mEffectList);

	// process effect queue
	for(std::vector<Effect*>::iterator it = mEffectQueue.begin(); it != mEffectQueue.end();++it)
	{
		mEffectList.push_back(*it);
	}
	mEffectQueue.clear();

	// process projectile queue
	for(std::vector<Projectile*>::iterator it = mProjectileQueue.begin(); it != mProjectileQueue.end();++it)
	{
		if(PO_Player==(*it)->GetOwner())
		{
			AddPlayerProjectile(*it);
		}
		else if(PO_Enemy == (*it)->GetOwner())
		{
			AddProjectile(*it);
		}
	}
	mProjectileQueue.clear();

	// remove dead effects
	mEffectList.erase(std::remove_if(mEffectList.begin(),mEffectList.end(),EffectIsDead),mEffectList.end());

	// remove dead actors
	mActorList.erase(std::remove_if(mActorList.begin(),mActorList.end(),ActorIsDead),mActorList.end());

	// remove dead projectiles
	mPlayerProjectiles.erase(std::remove_if(mPlayerProjectiles.begin(),mPlayerProjectiles.end(),ProjectileIsDead),mPlayerProjectiles.end());
	mProjectileList.erase(std::remove_if(mProjectileList.begin(),mProjectileList.end(),ProjectileIsDead),mProjectileList.end());
	// update projectiles
	for(std::vector<Projectile*>::iterator it = mPlayerProjectiles.begin(); it != mPlayerProjectiles.end();++it)
	{
		(*it)->Update();
		for(std::vector<Actor*>::iterator iter = mActorList.begin(); iter != mActorList.end();++iter)
		{
			Actor * pActor = *iter;
			// collide test
			if( (*it)->GetHitCircle().Collide(pActor->GetHitCircle()))
			{
				(*it)->Kill();
				pActor->TakeHit(*it);
			}
		}
	}

	for(std::vector<Projectile*>::iterator it = mProjectileList.begin(); it != mProjectileList.end();++it)
	{
		(*it)->Update();

		// collide test
		if( (*it)->GetHitCircle().Collide(mPlayer.GetHitCircle()))
		{
			(*it)->Kill();
			mPlayer.TakeHit(*it);
		}
	}

	// victory condition
	if(mActorList[0]->GetHealth()<=0)
	{
		EndGame();
		ClearScreen();
		EnableScreen("win");
	}
	// losing condition
	if(mPlayer.GetHealth()<=0)
	{
		EndGame();
		ClearScreen();
		EnableScreen("lose");
	}


	// clear input buffer
	InputManager::Instance().ClearInput();
}

void Game::LoadScreens()
{
	mScreens["splash"]=SplashScreen();
	mScreens["main"]=MainMenu();
	mScreens["game"]=GameScreen();
	mScreens["win"]=WinScreen();
	mScreens["lose"]=LoseScreen();
	EnableScreen("splash");
}

void Game::EnableScreen( std::string screenname )
{
	mActiveScreens.push_back(mScreens[screenname]);
	if("game"==screenname)
	{
		mbGameScreenActive= true;
	}
}

void Game::DisableScreen( std::string screenname )
{
	std::vector<Screen*>::iterator position = std::find(mActiveScreens.begin(), mActiveScreens.end(), mScreens[screenname]);
	if (position != mActiveScreens.end())
	{
		mActiveScreens.erase(position);
	}
	if("game"==screenname){mbGameScreenActive= false;}
}

void Game::FrontScreen( std::string screenname )
{
	DisableScreen(screenname);
	EnableScreen(screenname);
}

void Game::ClearScreen()
{
	mActiveScreens.clear();
	mbGameScreenActive= false;
}

void Game::Input( SDL_Event &rSDL_Event )
{
	// poll controller input
	InputManager::Instance().ControllerInputEvent(rSDL_Event);

	// top level widgets first
	for(std::vector<Screen*>::const_iterator it = mActiveScreens.begin(); it != mActiveScreens.end();++it)
	{
		if((*it)->Input(rSDL_Event))
		{
			return;
		}
	}
}

void Game::InitGame()
{
	mPlayer.Init();
	Actor * pActor = ModContentManager::Instance().SpawnActor("FairyA");
	pActor->Init();
	mActorList.push_back(pActor);
}

void Game::EndGame()
{
	// remove all actors
	ClearVector< std::vector<Actor*> >(mActorList);
	ClearVector< std::vector<Actor*> >(mActorQueue);

	// remove all projectiles
	ClearVector< std::vector<Projectile*> >(mProjectileList);
	ClearVector< std::vector<Projectile*> >(mProjectileQueue);

	// remove all effects
	ClearVector< std::vector<Effect*> >(mEffectList);
	ClearVector< std::vector<Effect*> >(mEffectQueue);
}

int Game::GetPlayerHealth() const
{
	return mPlayer.GetHealth();
}

float Game::GetHealthPercentage() const
{
	if(0 != mActorList.size())
	{
		return (mActorList[0]->GetHealth()/100.f);
	}
	return 1.f;
}

void Game::QueueEffect( Effect* effect )
{
	mEffectQueue.push_back(effect);
}

