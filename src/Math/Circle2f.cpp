#include "Circle2f.h"

Math::Circle::Circle()
{
	mPos = Math::Vector2f(0.f,0.f);
	mRad = 0;
}

Math::Circle::Circle( Math::Vector2f pos, float rad )
{
	mPos = pos;
	mRad = rad;
}

Math::Circle::Circle( Circle &rhs )
{
	mPos = rhs.GetPos();
	mRad=rhs.GetRad();
}

Math::Circle::~Circle()
{

}

bool Math::Circle::Collide( const Circle &rhs )const
{
	float squaredDist = mPos.SquaredDistance(rhs.GetPos());
	float squaredRad = mRad*mRad+rhs.GetRad()*rhs.GetRad();
	if(squaredRad>squaredDist)
	{
		return true;
	}
	return false;
}

bool Math::Circle::Collide( const Math::Vector2f &rhs )const
{
	float squaredDist = mPos.SquaredDistance(rhs);
	float squaredRad = mRad*mRad;
	if(squaredRad>squaredDist)
	{
		return true;
	}
	return false;
}