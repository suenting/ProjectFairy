#ifndef ACTORDATA_H
#define ACTORDATA_H
#include "../Core/Sprite.h"
#include "../pch.h"
#include "../Math/Vector2f.h"

class Actor;
class ActorData
{
public:
	ActorData(std::string name);
	~ActorData();
	void Render(Math::Vector2f pos)const;
	void Init(Actor *pActor);
	void Update(Actor *pActor);

	void SetInitCallback( void(*callback)(Actor*)){mp_init=callback;};
	void SetUpdateCallback( void (*callback)(Actor*)){mp_update=callback;};
	float GetRadius() const { return mRadius; }
	void SetRadius(float val) { mRadius = val; }
	int GetMaxHealth() const { return maxHealth; }
	void SetMaxHealth(int val) { maxHealth = val; }
protected:
private:
	float mRadius;
	int maxHealth;
	std::string mName;
	Sprite *mpSprite;
	void (*mp_init)(Actor*);
	void (*mp_update)(Actor*);
};

#endif