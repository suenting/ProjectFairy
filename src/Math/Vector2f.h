#ifndef Vector2f_H
#define Vector2f_H

namespace Math
{
	class Vector2f
	{
	public:
		Vector2f();
		Vector2f(float nx, float ny);
		Vector2f(const Vector2f& ref);
		~Vector2f();
		Vector2f operator + (const Vector2f& rhs)const;
		Vector2f operator - (const Vector2f& rhs)const;
		Vector2f operator * (const Vector2f& rhs)const;
		Vector2f operator * (const float& rhs)const;
		const Vector2f& operator = (const Vector2f& rhs);
		const Vector2f& operator += (const Vector2f& rhs);
		const Vector2f& operator -= (const Vector2f& rhs);
		const Vector2f& operator *= (const Vector2f& rhs);
		const Vector2f& operator *= (const float& rhs);
		float SquaredDistance(const Vector2f& rhs)const;
		float SquaredLength()const;
		float Length()const;
		const Vector2f& NormalizeSelf();
		Vector2f Scale(float scaler);
		const Vector2f& ScaleSelf(float scaler);

		static Vector2f GetVectorFromRad(float rad);
		static Vector2f GetVectorFromDeg(float deg);

		float x;
		float y;
	private:

	};
}

#endif
