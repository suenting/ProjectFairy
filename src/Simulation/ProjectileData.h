#ifndef PROJECTILEDATA_H
#define PROJECTILEDATA_H
#include "..\Core\Sprite.h"
#include "..\pch.h"
#include "..\Math\Vector2f.h"

enum ProjectileType
{
	PT_Vector,
	PT_VectorGrenade,
	PT_Custom
};

class Projectile;
class ProjectileData
{
public:
	ProjectileData(std::string name);
	~ProjectileData();
	void Render(Math::Vector2f pos, float angle = 0)const;
	void Update(Projectile *pProjectile);

	float GetSpeed() const { return mSpeed; }
	void SetSpeed(float val) { mSpeed = val; }
	float GetRadius() const { return mRadius; }
	void SetRadius(float val) { mRadius = val; }
	ProjectileType GetType() const { return mType; }
	void SetType(ProjectileType val) { mType = val; }
	float GetDamage()const{return mDamage;}
	void SetDamage(float val){mDamage = val;}
	int GetFuse() const { return mFuse; }
	void SetFuse(int val) { mFuse = val; }
	std::string GetShrapnelName() const { return mShrapnelName; }
	void SetShrapnelName(std::string val) { mShrapnelName = val; }
protected:
private:
	std::string mName;
	Sprite *mpSprite;
	float mSpeed;
	float mRadius;
	float mDamage;
	ProjectileType mType;

	// for PT_VECTORGRENADE
	std::string mShrapnelName;
	int mFuse;

};

#endif