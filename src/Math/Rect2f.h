#ifndef RECT2F_H
#define RECT2F_H

#include "Vector2f.h"
namespace Math
{
	class Rect2f
	{
	public:
		Rect2f();
		~Rect2f();
		Rect2f(float x,float y, float w, float h);
		bool Intersect(Math::Vector2f vec2f)const;
		bool Intersect(float px, float py)const;
		float x;
		float y;
		float h;
		float w;
	};
}
#endif