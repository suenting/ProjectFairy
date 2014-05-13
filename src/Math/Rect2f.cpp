#include "Rect2f.h"

namespace Math
{


	Rect2f::Rect2f()
	{

	}

	Rect2f::Rect2f( float x,float y, float w, float h )
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	bool Rect2f::Intersect( Math::Vector2f vec2f )const
	{
		return Intersect(vec2f.x,vec2f.y);
	}
	bool Rect2f::Intersect( float px, float py )const
	{
		if( (px>=x) && (px < (x+w)) && (py>=y) && (py < (y+h)) )
		{
			return true;
		}
		return false;
	}

	Rect2f::~Rect2f()
	{

	}

}