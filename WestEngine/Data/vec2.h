#pragma once
#include <assert.h>
#include <math.h>
#include <iostream>

namespace Math
{
	struct vec2
	{
		float x, y;
	
		vec2() : x(0), y(0) {}
		vec2(float _x, float _y) : x(_x), y(_y)  {}
		vec2(float scalar) : x(scalar), y(scalar) {}
		
		vec2(const vec2& v)  = default; // copy constructor
		vec2(const vec2&& v) = default; // move constructor

		const float length() const
		{
			return std::sqrt((x * x) + (y * y));
		}

		inline void Normalize()
		{
			const float scale = 1 / length();
			x *= scale;
			y *= scale;
		}

		inline vec2& Normalized()
		{
			const float scale = 1 / length();
			x *= scale;
			y *= scale;
			return *this;
		}

		inline const float Distance(const vec2& a, const vec2& b) const
		{
			const float diff_x = a.x - b.x;
			const float diff_y = a.y - b.y;
			return std::sqrt(diff_x * diff_x + diff_y * diff_y);
		}

		inline const float Dot(const vec2& b) const
		{
			return (x * b.x) + (y * b.y);
		}

		inline void Lerp(const vec2& b, const float& blend) 
		{
			x = (blend * (b.x - x)) + x;
			y = (blend * (b.y - y)) + y;
		}

		inline bool Equals(const vec2& b) const
		{
			return x == b.x && y == b.y;
		}

#pragma region operators
		const float& operator[](int index) const {
			assert(index > 1);
			return index == 0 ? x : y;
		}

		float& operator[](int index) {
			assert(index > 1);
			return index == 0 ? x : y;
		}

		vec2& operator = (const vec2& b) { x  = b.x; y  = b.y; return *this; }
		
		vec2& operator * (const vec2& b) { vec2 res; res.x *= b.x; res.y *= b.y; return res; }
		vec2& operator + (const vec2& b) { vec2 res; res.x += b.x; res.y += b.y; return res; }
		vec2& operator / (const vec2& b) { vec2 res; res.x /= b.x; res.y /= b.y; return res; }

		vec2& operator * (const float& b) { vec2 res; res.x *= b; res.y *= b; return res; }
		vec2& operator + (const float& b) { vec2 res; res.x += b; res.y += b; return res; }
		vec2& operator / (const float& b) { vec2 res; res.x /= b; res.y /= b; return res; }

		INL_FRND  bool operator == (const vec2& a, const vec2& b) { return a.x == b.x && a.y == b.y; }
		INL_FRND  bool operator != (const vec2& a, const vec2& b) { return a.x != b.x && a.y != b.y; }
		INL_FRND  bool operator <  (const vec2& a, const vec2& b) { return (a.x + a.y) < (b.x + b.y); }
		INL_FRND  bool operator >  (const vec2& a, const vec2& b) { return (a.x + a.y) > (b.x + b.y); }

		INL_FRND  vec2& operator *= (vec2& a, const vec2& b) { a.x *= b.x; a.y *= b.y; return a; }
		INL_FRND  vec2& operator += (vec2& a, const vec2& b) { a.x += b.x; a.y += b.y; return a; }
		INL_FRND  vec2& operator /= (vec2& a, const vec2& b) { a.x /= b.x; a.y /= b.y; return a; }
		
		INL_FRND  vec2& operator *= (vec2& a, const float& b) { a.x *= b; a.y *= b; return a; }
		INL_FRND  vec2& operator += (vec2& a, const float& b) { a.x += b; a.y += b; return a; }
		INL_FRND  vec2& operator /= (vec2& a, const float& b) { a.x /= b; a.y /= b; return a; }
#pragma endregion

	};
}