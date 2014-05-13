#ifndef CIRCLE_H
#define CIRCLE_H
#include "Vector2f.h"

namespace Math
{
	class Circle
	{
	public:
		Circle();
		~Circle();
		Circle(Circle &rhs);
		Circle(Math::Vector2f pos, float rad);
		bool Collide(const Circle &rhs )const;
		bool Collide(const Math::Vector2f &rhs)const;

		Math::Vector2f GetPos() const { return mPos; }
		void SetPos(Math::Vector2f val) { mPos = val; }
		float GetRad() const { return mRad; }
		void SetRad(float val) { mRad = val; }
	protected:
	private:
		Math::Vector2f mPos;
		float mRad;
	};
}

#endif