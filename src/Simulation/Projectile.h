
#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "ProjectileData.h"
#include "..\Math\Circle2f.h"

enum ProjectileOwner
{
	PO_Player,
	PO_Enemy
};

class Projectile
{
public:
	Projectile(ProjectileData * pData);
	~Projectile();
	void Render()const;
	void Update();

	
	Math::Circle GetHitCircle()const;
	void Kill(){mbIsDead = true;};
	Math::Vector2f GetPosition() const { return mPos; }
	void SetPosition(Math::Vector2f val) { mPos = val; }
	Math::Vector2f GetVector() const { return mVector; }
	void SetVector(Math::Vector2f val) { mVector = val; }
	void SetVector(float deg);
	bool GetIsDead() const { return mbIsDead; }
	ProjectileData* GetData()const{return mpData;}
	ProjectileOwner GetOwner() const { return owner; }
	void SetOwner(ProjectileOwner val) { owner = val; }
protected:
private:
	ProjectileData* mpData;
	Math::Vector2f mPos;
	Math::Vector2f mVector;
	int mTicks;
	bool mbIsDead;
	float mAngle;
	ProjectileOwner owner;

};

#endif