#pragma once
#include <math.h>
#include <iostream>
#include "quat.h"

namespace Math
{
	struct vec3
	{
		float x, y, z;

		vec3() : x(0), y(0), z(0){}
		vec3(float scalar) : x(scalar), y(scalar) , z(scalar) {}
		vec3(float _x, float _y) : x(_x), y(_y) , z(0) {}
		vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

		vec3(const vec3& v) = default; // copy constructor
		vec3(const vec3&& v) = default; // move constructor

		const float length() const
		{
			return std::sqrt((x * x) + (y * y) + (z * z));
		}

		const float lengthSquared() const
		{
			return (x * x) + (y * y) + (z * z);
		}

		inline void Normalize()
		{
			const float scale = 1 / length();
			x *= scale;
			y *= scale;
			z *= scale;
		}

		inline vec3& Normalized()
		{
			const float scale = 1 / length();
			x *= scale;
			y *= scale;
			z *= scale;
			return *this;
		}

		inline const float Distance(const vec3& a, const vec3& b) const
		{
			const float diff_x = a.x - b.x;
			const float diff_y = a.y - b.y;
			const float diff_z = a.z - b.z;
			return std::sqrt(diff_x * diff_x + diff_y * diff_y + diff_z * diff_z);
		}

		inline const float Distance(const vec3& b) const
		{
			return Distance(*this, b);
		}

		inline const float Dot(const vec3& b) const
		{
			return (x * b.x) + (y * b.y) + (z * b.z);
		}

		inline vec3& Cross(const vec3& b) const
		{
			vec3 result((x * b.z) - (z * b.y),
						(y * b.x) - (x * b.z),
						(z * b.y) - (y * b.x));
			return result;
		}

		inline void Lerp(const vec3& b, const float& blend)
		{
			x = (blend * (b.x - x)) + x;
			y = (blend * (b.y - y)) + y;
			z = (blend * (b.z - z)) + z;
		}

		inline bool Equals(const vec3& b) const { return x == b.x && y == b.y && z == b.z; }
		
		quat ToQuaternion(const vec3& euler) // yaw (Z), pitch (Y), roll (X)
		{
			// Abbreviations for the various angular functions
			const float cy = std::cos(euler.x * 0.5f);
			const float sy = std::sin(euler.x * 0.5f);
			const float cp = std::cos(euler.y * 0.5f);
			const float sp = std::sin(euler.y * 0.5f);
			const float cr = std::cos(euler.z * 0.5f);
			const float sr = std::sin(euler.z * 0.5f);

			quat q;
			q.w = cr * cp * cy + sr * sp * sy;
			q.x = sr * cp * cy - cr * sp * sy;
			q.y = cr * sp * cy + sr * cp * sy;
			q.z = cr * cp * sy - sr * sp * cy;

			return q;
		}

#pragma region operators
		constexpr const float& operator[](int index) const {
			switch (index)
			{
				case 0: return x;
				case 1: return y;
				case 2: return z;
				default: std::cout << "index bound out of array"; return x;
			}
		}

		constexpr float& operator[](int index) {
			switch (index)
			{
				case 0: return x;
				case 1: return y;
				case 2: return z;
				default: std::cout << "index bound out of array"; return x;
			}
		}

		vec3& operator = (const vec3& b) { memcpy(this, &b.x, 12); return *this; }

		vec3& operator * (const vec3& b) { vec3 res; res.x *= b.x; res.y *= b.y;  res.z *= b.z; return res; }
		vec3& operator + (const vec3& b) { vec3 res; res.x += b.x; res.y += b.y;  res.z += b.z; return res; }
		vec3& operator / (const vec3& b) { vec3 res; res.x /= b.x; res.y /= b.y;  res.z /= b.z; return res; }

		vec3& operator * (const float& b) { x *= b; y *= b; z *= b; return *this; }
		vec3& operator + (const float& b) { x += b; y += b; z += b; return *this; }
		vec3& operator / (const float& b) { x /= b; y /= b; z /= b; return *this; }

		INL_FRND  bool operator == (const vec3& a, const vec3& b) { return a.x == b.x && a.y == b.y && a.z == b.z;}
		INL_FRND  bool operator != (const vec3& a, const vec3& b) { return a.x != b.x && a.y != b.y && a.z == b.z;}
		INL_FRND  bool operator <  (const vec3& a, const vec3& b) { return (a.x + a.y + a.z) < (b.x + b.y + b.z); }
		INL_FRND  bool operator >  (const vec3& a, const vec3& b) { return (a.x + a.y + a.z) > (b.x + b.y + b.z); }

		INL_FRND  vec3& operator *= (vec3& a, const vec3& b) { a.x *= b.x; a.y *= b.y; a.z *= b.z; return a; }
		INL_FRND  vec3& operator += (vec3& a, const vec3& b) { a.x += b.x; a.y += b.y; a.z += b.z; return a; }
		INL_FRND  vec3& operator /= (vec3& a, const vec3& b) { a.x /= b.x; a.y /= b.y; a.z /= b.z; return a; }

		INL_FRND  vec3& operator *= (vec3& a, const float& b) { a.x *= b; a.y *= b; a.z *= b; return a; }
		INL_FRND  vec3& operator += (vec3& a, const float& b) { a.x += b; a.y += b; a.z += b; return a; }
		INL_FRND  vec3& operator /= (vec3& a, const float& b) { a.x /= b; a.y /= b; a.z /= b; return a; }
#pragma endregion

	};
}