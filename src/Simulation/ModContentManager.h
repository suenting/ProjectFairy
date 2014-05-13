#ifndef MODCONTENTMANAGER_H
#define MODCONTENTMANAGER_H


#include "../pch.h"
#include "ActorData.h"
#include "EffectData.h"
#include "Actor.h"
#include "ActorData.h"
#include "Projectile.h"
#include "ProjectileData.h"

class ModContentManager
{
public:
	static ModContentManager& Instance()
	{
		static ModContentManager instance;
		return instance;
	}
	~ModContentManager();
	void LoadGameData();

	Actor* SpawnActor(std::string name);
	Effect* SpawnEffect(std::string name);
	Projectile* SpawnProjectile(std::string name);
protected:
private:
	ModContentManager();
	ModContentManager( const ModContentManager& other ){};
	ModContentManager& operator=( const ModContentManager& rhs ){};

	std::map<std::string,EffectData*> mEffectData;
	std::map<std::string,ActorData*> mActorData;
	std::map<std::string,ProjectileData*> mProjectileData;

};

#endif//MODCONTENTMANAGER_H