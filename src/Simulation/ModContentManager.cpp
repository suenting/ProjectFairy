#include "ModContentManager.h"
#include "Game.h"
#include "..\Core\ResourceManager.h"

namespace
{

	// Effects
	static void LoadEffectData(std::map<std::string,EffectData*> &effectDB)
	{
		// spell ring
		EffectData* pData = new EffectData("effect_ring_outer",EFT_Rotate,1.f);
		pData->SetCenter(true);
		pData->LoadSprite("effect_ring_outer");
		effectDB.insert(std::pair<std::string,EffectData*>("effect_ring_outer",pData));

		pData = new EffectData("effect_ring_spiral_inner",EFT_Rotate,-1.f);
		pData->SetCenter(true);
		pData->LoadSprite("effect_ring_spiral_inner");
		effectDB.insert(std::pair<std::string,EffectData*>("effect_ring_spiral_inner",pData));

		// explosion
		pData = new EffectData("explosion",EFT_Animate,0.5f);
		pData->SetCenter(true);
		pData->LoadAnimatedSprite("explosion%d.png",1,7);
		pData->SetTimeToLive(14);
		effectDB.insert(std::pair<std::string,EffectData*>("explosion",pData));
	}

	// Actors

	// FairyA
	static void FairyAInitCallback(Actor* pActor)
	{
		pActor->SetPosition(Math::Vector2f(800.f,250.f));
		pActor->SetNextPosition(Math::Vector2f(800.f,250.f));
		pActor->AddEffect("effect_ring_outer");
		pActor->AddEffect("effect_ring_spiral_inner");
		pActor->SetEffectTint(255,180,115);
	}
	static void FairyAUpdateCallback(Actor* pActor)
	{
		int tick = pActor->GetTick();
		int state = pActor->GetState();

		float health = pActor->GetHealth();
		if( (health+10)<pActor->GetHealthState())
		{
			// update position
			pActor->SetHealthState(pActor->GetHealthState()-10);
			int randValue = Game::Instance().GetRandom()%6;
			switch(randValue)
			{
			case 0:
				pActor->SetNextPosition(Math::Vector2f(800.f,250.f));
				break;
			case 1:
				pActor->SetNextPosition(Math::Vector2f(800.f,100.f));
				break;
			case 2:
				pActor->SetNextPosition(Math::Vector2f(800.f,400.f));
				break;
			case 3:
				pActor->SetNextPosition(Math::Vector2f(750.f,250.f));
				break;
			case 4:
				pActor->SetNextPosition(Math::Vector2f(700.f,100.f));
				break;
			case 5:
				pActor->SetNextPosition(Math::Vector2f(700.f,400.f));
				break;
			}
			// update attack pattern
			randValue = Game::Instance().GetRandom()%3;
			switch(randValue)
			{
			case 0:
				pActor->SetEffectTint(255,180,115);
				break;
			case 1:
				pActor->SetEffectTint(255,0,0);
				break;
			case 2:
				pActor->SetEffectTint(175,255,255);
				break;
			}
			pActor->SetState(randValue);
			// spawn some minions
			float xPos = static_cast<float>((Game::Instance().GetRandom()%400)+500);
			int minonType = Game::Instance().GetRandom()%4;
			for(int iter = 0;iter<2;++iter)
			{
				Actor * pActor;
				switch(minonType)
				{
				case 0:
					pActor = ModContentManager::Instance().SpawnActor("cat");
					break;
				case 1:
					pActor = ModContentManager::Instance().SpawnActor("rabbit");
					break;
				case 2:
					pActor = ModContentManager::Instance().SpawnActor("dog");
					break;
				case 3:
					pActor = ModContentManager::Instance().SpawnActor("snake");
					break;
				}
				 
				float yPos = static_cast<float>((Game::Instance().GetRandom()%500));
				float yDir = 0.f;
				if(yPos>250){yDir = 540;}
				pActor->SetPosition(Math::Vector2f(xPos,yPos));
				pActor->SetNextPosition(Math::Vector2f(xPos,yDir));
				pActor->Init();
				Game::Instance().QueueActor(pActor);
			}
		}

		if(0==state)
		{
			if(0 == tick%10)
			{
				for(int it = 0; it<6;++it)
				{
					tick = pActor->GetTick()%170;
					Projectile *pProjectile = ModContentManager::Instance().SpawnProjectile("orange_bullet");
					Math::Vector2f refPosition = pActor->GetPosition();
					float vec = 0;
					if(it%2==0)
					{
						vec = 100.f+tick+15.f*it;
					}
					else if(it%2==1)
					{
						tick = tick%170;
						vec = 260.f-tick-15.f*it;
					}
					refPosition += Math::Vector2f::GetVectorFromDeg(vec)*64.f;
					pProjectile->SetPosition(refPosition);
					pProjectile->SetVector(vec);
					Game::Instance().QueueProjectile(pProjectile);
				}
			}
		}
		else if(1==state)
		{
			if(0 == tick%10)
			{
				for(int it = 0; it<5;++it)
				{
					tick = pActor->GetTick()%340;
					Projectile *pProjectile = ModContentManager::Instance().SpawnProjectile("red_bullet");
					Math::Vector2f refPosition = pActor->GetPosition();
					if(tick<=170)
					{
						refPosition += Math::Vector2f::GetVectorFromDeg(100.f+tick+15.f*it)*64.f;
						pProjectile->SetPosition(refPosition);
						pProjectile->SetVector(100.f+tick);
					}
					else
					{
						tick = tick%170;
						refPosition += Math::Vector2f::GetVectorFromDeg(260.f-tick-15.f*it)*64.f;
						pProjectile->SetPosition(refPosition);
						pProjectile->SetVector(260.f-tick);
					}
					Game::Instance().QueueProjectile(pProjectile);
				}
			}
		}
		if(2==state)
		{
			if(0 == tick%30)
			{
				for(int it = 0; it<2;++it)
				{
					Projectile *pProjectile = ModContentManager::Instance().SpawnProjectile("teal_orb");
					Math::Vector2f refPosition = pActor->GetPosition();
					float vec = 0;
					if(0==it)
					{
						vec = 130.f+15.f*(tick%180)/30;
					}
					else if (1==it)
					{
						vec = 230.f-15.f*(tick%180)/30;
					}
					refPosition += Math::Vector2f::GetVectorFromDeg(vec)*64.f;
					pProjectile->SetPosition(refPosition);
					pProjectile->SetVector(vec);
					Game::Instance().QueueProjectile(pProjectile);
				}
			}
		}
	}
	static void LoadActorFairyA(std::map<std::string, ActorData*> &actorDB)
	{
		ActorData* pData = new ActorData("FairyA");
		pData->SetInitCallback(FairyAInitCallback);
		pData->SetUpdateCallback(FairyAUpdateCallback);
		actorDB.insert(std::pair<std::string,ActorData*>("FairyA",pData));
	}


	// minions
	static void CatUpdateCallback(Actor* pActor)
	{
		int tick = pActor->GetTick();
		int state = pActor->GetState();
		// movement
		Math::Vector2f position = pActor->GetPosition();
		if(pActor->GetPosition().y<40)
		{
			position.y = 540;
			pActor->SetNextPosition(position);
		}
		if(pActor->GetPosition().y>500)
		{
			position.y = 0;
			pActor->SetNextPosition(position);
		}

		// attack
		if(0 == tick%50)
		{
			for(int it = 0; it<6;++it)
			{
				Projectile *pProjectile = ModContentManager::Instance().SpawnProjectile("red_bullet");
				Math::Vector2f refPosition = pActor->GetPosition();
				float vec = 130.f+15.f*it;
				refPosition += Math::Vector2f::GetVectorFromDeg(vec)*25.f;
				pProjectile->SetPosition(refPosition);
				pProjectile->SetVector(vec);
				Game::Instance().QueueProjectile(pProjectile);
			}
		}
		if(pActor->GetHealth()<=0)
		{
			pActor->kill();
		}
	}
	static void LoadActorCat(std::map<std::string, ActorData*> &actorDB)
	{
		ActorData* pData = new ActorData("cat");
		pData->SetUpdateCallback(CatUpdateCallback);
		pData->SetMaxHealth(2);
		actorDB.insert(std::pair<std::string,ActorData*>("cat",pData));
	}
	static void RabbitUpdateCallback(Actor* pActor)
	{
		int tick = pActor->GetTick();
		int state = pActor->GetState();
		// movement
		Math::Vector2f position = pActor->GetPosition();
		if(pActor->GetPosition().y<40)
		{
			position.y = 540;
			pActor->SetNextPosition(position);
		}
		if(pActor->GetPosition().y>500)
		{
			position.y = 0;
			pActor->SetNextPosition(position);
		}

		// attack
		if(0 == tick%100)
		{
			Projectile *pProjectile = ModContentManager::Instance().SpawnProjectile("teal_orb");
			Math::Vector2f refPosition = pActor->GetPosition();
			float vec = 180.f;
			refPosition += Math::Vector2f::GetVectorFromDeg(vec)*25.f;
			pProjectile->SetPosition(refPosition);
			pProjectile->SetVector(vec);
			Game::Instance().QueueProjectile(pProjectile);
		}
		if(pActor->GetHealth()<=0)
		{
			pActor->kill();
		}
	}
	static void LoadActorRabbit(std::map<std::string, ActorData*> &actorDB)
	{
		ActorData* pData = new ActorData("rabbit");
		pData->SetUpdateCallback(RabbitUpdateCallback);
		pData->SetMaxHealth(2);
		actorDB.insert(std::pair<std::string,ActorData*>("rabbit",pData));
	}
	static void SnakeUpdateCallback(Actor* pActor)
	{
		int tick = pActor->GetTick();
		int state = pActor->GetState();
		// movement
		Math::Vector2f position = pActor->GetPosition();
		if(pActor->GetPosition().y<40)
		{
			position.y = 540;
			pActor->SetNextPosition(position);
		}
		if(pActor->GetPosition().y>500)
		{
			position.y = 0;
			pActor->SetNextPosition(position);
		}

		// attack
		if(0 == tick%100)
		{
			Projectile *pProjectile = ModContentManager::Instance().SpawnProjectile("green_orb");
			Math::Vector2f refPosition = pActor->GetPosition();
			float vec = 180.f;
			refPosition += Math::Vector2f::GetVectorFromDeg(vec)*25.f;
			pProjectile->SetPosition(refPosition);
			pProjectile->SetVector(vec);
			Game::Instance().QueueProjectile(pProjectile);
		}
		if(pActor->GetHealth()<=0)
		{
			pActor->kill();
		}
	}
	static void LoadActorSnake(std::map<std::string, ActorData*> &actorDB)
	{
		ActorData* pData = new ActorData("snake");
		pData->SetUpdateCallback(SnakeUpdateCallback);
		pData->SetMaxHealth(2);
		actorDB.insert(std::pair<std::string,ActorData*>("snake",pData));
	}
	static void DogUpdateCallback(Actor* pActor)
	{
		int tick = pActor->GetTick();
		int state = pActor->GetState();
		// movement
		Math::Vector2f position = pActor->GetPosition();
		if(pActor->GetPosition().y<40)
		{
			position.y = 540;
			pActor->SetNextPosition(position);
		}
		if(pActor->GetPosition().y>500)
		{
			position.y = 0;
			pActor->SetNextPosition(position);
		}

		// attack
		if(0 == tick%75)
		{
			for(int it = 0; it<3;++it)
			{
				Projectile *pProjectile = ModContentManager::Instance().SpawnProjectile("orange_bullet");
				Math::Vector2f refPosition = pActor->GetPosition();
				refPosition.y-=50;
				refPosition.y+=(it*50);
				float vec = 180.f;
				refPosition += Math::Vector2f::GetVectorFromDeg(vec)*25.f;
				pProjectile->SetPosition(refPosition);
				pProjectile->SetVector(vec);
				Game::Instance().QueueProjectile(pProjectile);
			}
		}
		if(pActor->GetHealth()<=0)
		{
			pActor->kill();
		}
	}
	static void LoadActorDog(std::map<std::string, ActorData*> &actorDB)
	{
		ActorData* pData = new ActorData("dog");
		pData->SetUpdateCallback(DogUpdateCallback);
		pData->SetMaxHealth(2);
		actorDB.insert(std::pair<std::string,ActorData*>("dog",pData));
	}
	static void LoadActorData(std::map<std::string, ActorData*> &actorDB)
	{
		LoadActorFairyA(actorDB);
		LoadActorCat(actorDB);
		LoadActorRabbit(actorDB);
		LoadActorDog(actorDB);
		LoadActorSnake(actorDB);
	}

	// Projectiles
	static void LoadPlayerBullet(std::map<std::string, ProjectileData*> &projectileDB)
	{
		ProjectileData * pData = new ProjectileData("player_bullet");
		pData->SetRadius(ResourceManager::Instance().ScaleTextureWidth(4));
		pData->SetSpeed(16.f);
		//pData->SetDamage(0.075f);
		pData->SetDamage(0.5f);
		pData->SetType(PT_Vector);
		projectileDB.insert(std::pair<std::string,ProjectileData*>("player_bullet",pData));
	}

	static void LoadRedBullet(std::map<std::string, ProjectileData*> &projectileDB)
	{
		ProjectileData * pData = new ProjectileData("red_bullet");
		pData->SetRadius(4.f);
		pData->SetSpeed(2.f);
		pData->SetDamage(1.f);
		pData->SetType(PT_Vector);
		projectileDB.insert(std::pair<std::string,ProjectileData*>("red_bullet",pData));
	}
	static void LoadGreenBullet(std::map<std::string, ProjectileData*> &projectileDB)
	{
		ProjectileData * pData = new ProjectileData("green_bullet");
		pData->SetRadius(4.f);
		pData->SetSpeed(2.f);
		pData->SetDamage(1.f);
		pData->SetType(PT_Vector);
		projectileDB.insert(std::pair<std::string,ProjectileData*>("green_bullet",pData));
	}
	static void LoadTealBullet(std::map<std::string, ProjectileData*> &projectileDB)
	{
		ProjectileData * pData = new ProjectileData("teal_bullet");
		pData->SetRadius(4.f);
		pData->SetSpeed(2.f);
		pData->SetDamage(1.f);
		pData->SetType(PT_Vector);
		projectileDB.insert(std::pair<std::string,ProjectileData*>("teal_bullet",pData));
	}
	static void LoadWhiteBullet(std::map<std::string, ProjectileData*> &projectileDB)
	{
		ProjectileData * pData = new ProjectileData("white_bullet");
		pData->SetRadius(4.f);
		pData->SetSpeed(2.f);
		pData->SetDamage(1.f);
		pData->SetType(PT_Vector);
		projectileDB.insert(std::pair<std::string,ProjectileData*>("white_bullet",pData));
	}
	static void LoadOrangeBullet(std::map<std::string, ProjectileData*> &projectileDB)
	{
		ProjectileData * pData = new ProjectileData("orange_bullet");
		pData->SetRadius(4.f);
		pData->SetSpeed(2.f);
		pData->SetDamage(1.f);
		pData->SetType(PT_Vector);
		projectileDB.insert(std::pair<std::string,ProjectileData*>("orange_bullet",pData));
	}
	static void LoadTealOrb(std::map<std::string, ProjectileData*> &projectileDB)
	{
		ProjectileData * pData = new ProjectileData("teal_orb");
		pData->SetRadius(4.f);
		pData->SetSpeed(2.f);
		pData->SetDamage(1.f);
		pData->SetType(PT_VectorGrenade);
		pData->SetFuse(100);
		pData->SetShrapnelName("teal_bullet");
		projectileDB.insert(std::pair<std::string,ProjectileData*>("teal_orb",pData));
	}
	static void LoadGreenOrb(std::map<std::string, ProjectileData*> &projectileDB)
	{
		ProjectileData * pData = new ProjectileData("green_orb");
		pData->SetRadius(4.f);
		pData->SetSpeed(2.f);
		pData->SetDamage(1.f);
		pData->SetType(PT_VectorGrenade);
		pData->SetFuse(100);
		pData->SetShrapnelName("green_bullet");
		projectileDB.insert(std::pair<std::string,ProjectileData*>("green_orb",pData));
	}
	static void LoadProjectileData(std::map<std::string, ProjectileData*> &projectileDB)
	{
		LoadPlayerBullet(projectileDB);
		LoadRedBullet(projectileDB);
		LoadGreenBullet(projectileDB);
		LoadTealBullet(projectileDB);
		LoadWhiteBullet(projectileDB);
		LoadOrangeBullet(projectileDB);
		LoadTealOrb(projectileDB);
		LoadGreenOrb(projectileDB);
	}
}

ModContentManager::ModContentManager()
{

}

ModContentManager::~ModContentManager()
{
	for(std::map<std::string,EffectData*>::iterator it = mEffectData.begin(); it != mEffectData.end();++it)
	{
		delete it->second;
	}
	for(std::map<std::string,ActorData*>::iterator it = mActorData.begin(); it != mActorData.end();++it)
	{
		delete it->second;
	}
	for(std::map<std::string,ProjectileData*>::iterator it = mProjectileData.begin(); it != mProjectileData.end();++it)
	{
		delete it->second;
	}
}

void ModContentManager::LoadGameData()
{
	// Note: load order dependencies

	// Load Effect
	LoadEffectData(mEffectData);

	// Load Actor
	LoadActorData(mActorData);

	// Load Projectiles
	LoadProjectileData(mProjectileData);

}

Actor* ModContentManager::SpawnActor( std::string name )
{
	ActorData *pData = mActorData[name];
	Actor* pActor = new Actor(pData);
	return pActor;
}

Effect* ModContentManager::SpawnEffect( std::string name )
{
	EffectData *pData = mEffectData[name];
	Effect *pEffect = new Effect(pData);
	return pEffect;
}

Projectile* ModContentManager::SpawnProjectile( std::string name )
{
	ProjectileData *pData = mProjectileData[name];
	Projectile* pProjectile = new Projectile(pData);
	return pProjectile;
}
