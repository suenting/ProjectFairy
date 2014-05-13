#include "../pch.h"
#include "Vector2f.h"

# define PI 3.141592653589793238462643383279502884

namespace Math
{
	Vector2f::Vector2f(float nx, float ny)
	{
		x = nx;
		y = ny;
		return;
	}

	Vector2f::Vector2f()
	{

	}

	Vector2f::Vector2f( const Vector2f& ref )
	{
		x = ref.x;
		y = ref.y;
	}

	Vector2f::~Vector2f()
	{
	}

	Vector2f Vector2f::operator+(const Vector2f& rhs)const
	{
		return Vector2f(x+rhs.x,y+rhs.y);
	}

	Vector2f Vector2f::operator-(const Vector2f& rhs)const
	{
		return Vector2f(x-rhs.x,y-rhs.y);
	}

	Vector2f Vector2f::operator*(const Vector2f& rhs)const
	{
		return Vector2f(x*rhs.x,y*rhs.y);
	}
	Vector2f Vector2f::operator*(const float& rhs)const
	{
		return Vector2f(x*rhs,y*rhs);
	}
	const Vector2f& Vector2f::operator+=(const Vector2f& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	const Vector2f& Vector2f::operator-=(const Vector2f& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	const Vector2f& Vector2f::operator*=(const Vector2f& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}
	const Vector2f& Vector2f::operator*=(const float& rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}
	const Vector2f& Vector2f::operator=( const Vector2f& rhs )
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	float Vector2f::SquaredDistance(const Vector2f& rhs)const
	{
		return ((x-rhs.x)*(x-rhs.x))+((y-rhs.y)*(y-rhs.y));
	}
	float Vector2f::SquaredLength()const
	{
		return ((x*x)+(y*y));
	}
	float Vector2f::Length()const
	{
		return std::sqrt(SquaredLength());
	}
	Vector2f Vector2f::Scale(float scaler)
	{
		return Vector2f(x*scaler,y*scaler);
	}
	const Vector2f& Vector2f::ScaleSelf(float scaler)
	{
		x *= scaler;
		y *= scaler;
		return *this;
	}
	const Vector2f& Vector2f::NormalizeSelf()
	{
		float len = Length();
		if(0==len){return *this;}
		x = x/len;
		y = y/len;
		return *this;
	}

	Math::Vector2f Vector2f::GetVectorFromRad(float rad)
	{
		float y = -1 * (float) sin(rad);
		float x = (float) cos(rad);
		Math::Vector2f out = Math::Vector2f(x,y);
		return out;
	}

	Math::Vector2f Vector2f::GetVectorFromDeg(float deg)
	{
		float rad = deg * (PI/180);
		return GetVectorFromRad(rad);
	}


}

