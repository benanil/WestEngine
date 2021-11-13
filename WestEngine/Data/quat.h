#pragma once
#include "Math.h"
#include <iostream>
#include <numbers>
#include "vec3.h"

namespace Math
{
	struct quat
	{	
		float x, y, z, w;

		/// <summary> creates identity quaternion </summary>
		quat() : x(0), y(0), z(0), w(1) {}
		quat(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
		quat(vec3 xyz, float _w) : x(xyz.x), y(xyz.y), z(xyz.z), w(_w) {}

		quat(const quat& v) = default; // copy constructor
		quat(const quat&& v) = default; // move constructor

		inline vec3& xyz() const { vec3 _xyz(x,y,z); return _xyz; }

		inline float length() const
		{
			return std::sqrt((w * w) + (x * x) + (y * y) + (z * z));
		}

		inline float lengthSquared() const {
			return (w * w) + (x * x) + (y * y) + (z * z);
		}

	  	inline float Dot(const quat& a, const quat& b) const
		{
			return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
		}

		inline void Normalize()
		{
			const float mag = std::sqrt(Dot(*this, *this));
			
			if (mag < std::numeric_limits<float>::epsilon())
			{
				x = 0; y = 0; z = 0; w = 0;
				return;
			}
			x /= mag; y /= mag; z /= mag; w /= mag;
		}


		inline const quat& Normalized() const
		{
			quat result;
			const float mag = std::sqrt(Dot(*this, *this));

			if (mag < std::numeric_limits<float>::epsilon())
			{
				result.x = 0; result.y = 0; result.z = 0; result.w = 0;
				return;
			}
			result.x /= mag; result.y /= mag; result.z /= mag; result.w /= mag;
		}

		inline const quat& Inverted()
		{
			if (lengthSquared() != 0.0f)
			{
				const float i = 1 / lengthSquared();
				quat result(xyz() * -i, w * i);
				return result;
			}
			else
			{
				return *this;
			}
		}

		inline void Invert()
		{
			*this = (*this).Inverted();
		}
		
		// https://github.com/opentk/opentk/blob/master/src/OpenTK.Mathematics/Data/Quaternion.cs
		inline quat FromMatrix(const mat4& matrix)
		{
			quat result;
			float trace = matrix[0][0] + matrix[1][1] + matrix[2][2] + matrix[3][3];

			if (trace > 0)
			{
				float s = std::sqrt(trace + 1) * 2;
				float invS = 1.0f / s;

				result.w = s * 0.25f;
				result.x = (matrix[2][1] - matrix[1][2]) * invS;
				result.y = (matrix[0][2] - matrix[2][0]) * invS;
				result.z = (matrix[1][0] - matrix[0][1]) * invS;
			}
			else
			{
				float m00 = matrix[0][0], m11 = matrix[1][1], m22 = matrix[2][2];

				if (m00 > m11 && m00 > m22)
				{
					float s = std::sqrt(1 + m00 - m11 - m22) * 2;
					float invS = 1.0f / s;

					result.w = (matrix[2][1] - matrix[1][2]) * invS;
					result.x = s * 0.25f;
					result.y = (matrix[0][1] + matrix[1][0]) * invS;
					result.z = (matrix[0][2] + matrix[2][0]) * invS;
				}
				else if (m11 > m22)
				{
					float s = std::sqrt(1 + m11 - m00 - m22) * 2;
					float invS = 1.0f / s;

					result.w = (matrix[0][2] - matrix[2][0]) * invS;
					result.x = (matrix[0][1] + matrix[1][0]) * invS;
					result.y = s * 0.25f;
					result.z = (matrix[1][2] + matrix[2][1]) * invS;
				}
				else
				{
					float s = std::sqrt(1 + m22 - m00 - m11) * 2;
					float invS = 1.0f / s;

					result.w = (matrix[1][0] - matrix[0][1]) * invS;
					result.x = (matrix[0][2] + matrix[2][0]) * invS;
					result.y = (matrix[1][2] + matrix[2][1]) * invS;
					result.z = s * 0.25f;
				}
			}
		}


		quat& Slerp(quat& q1, quat& q2, const float& blend)
		{
			quat Identity;

			// if either input is zero, return the other.
			if (q1.lengthSquared() == 0.0f)
			{
				if (q2.lengthSquared() == 0.0f)
				{
					return Identity;
				}

				return q2;
			}

			if (q2.lengthSquared() == 0.0f)
			{
				return q1;
			}

			float cosHalfAngle = (q1.w * q2.w) + q1.xyz().Dot(q2.xyz());

			if (cosHalfAngle >= 1.0f || cosHalfAngle <= -1.0f)
			{
				// angle = 0.0f, so just return one input.
				return q1;
			}

			if (cosHalfAngle < 0.0f)
			{
				q2.x = -q2.x;
				q2.y = -q2.y;
				q2.z = -q2.z;
				q2.w = -q2.w;
				cosHalfAngle = -cosHalfAngle;
			}

			float blendA;
			float blendB;
			if (cosHalfAngle < 0.99f)
			{
				// do proper slerp for big angles
				float halfAngle = std::acos(cosHalfAngle);
				float sinHalfAngle = std::sin(halfAngle);
				float oneOverSinHalfAngle = 1.0f / sinHalfAngle;
				blendA = std::sin(halfAngle * (1.0f - blend)) * oneOverSinHalfAngle;
				blendB = std::sin(halfAngle * blend) * oneOverSinHalfAngle;
			}
			else
			{
				// do lerp if angle is really small.
				blendA = 1.0f - blend;
				blendB = blend;
			}

			quat result = quat((q1.xyz() * blendA ) + (q2.xyz() * blendB), (blendA * q1.w) + (blendB * q2.w));
			
			if (result.lengthSquared() > 0.0f)
			{
				result.Normalize();
				return result;
			}

			return Identity;
		}

		inline const vec3& ToEulerAngles() {
			vec3 angles;
			const quat& q = *this;
			// roll (x-axis rotation)
			const float sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
			const float cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
			angles.z = std::atan2(sinr_cosp, cosr_cosp);

			// pitch (y-axis rotation)
			const float sinp = 2 * (q.w * q.y - q.z * q.x);
			if (std::abs(sinp) >= 1)
				angles.y = std::copysign(std::numbers::pi / 2, sinp); // use 90 degrees if out of range
			else
				angles.y = std::asin(sinp);

			// yaw (z-axis rotation)
			const float siny_cosp = 2 * (q.w * q.z + q.x * q.y);
			const float cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
			angles.x = std::atan2(siny_cosp, cosy_cosp);

			return angles;
		}

#pragma region operators
		constexpr const float& operator[](int index) const {
			switch (index)
			{
				case 0: return x;
				case 1: return y;
				case 2: return z;
				case 3: return w;
				default: std::cout << "index bound out of array"; return x;
			}
		}

		constexpr float& operator[](int index) {
			switch (index)
			{
				case 0: return x;
				case 1: return y;
				case 2: return z;
				case 3: return w;
				default: std::cout << "index bound out of array"; return x;
			}
		}


		inline quat& operator = (const quat& b) { memcpy(this, &b.x, 16); return *this; }
		
		inline quat& operator * (const quat& rhs)
		{
			x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
            y = w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z;
            z = w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x;
            w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;		
		}

		INL_FRND quat& operator *= (quat& lhs, const quat& rhs)
		{
			quat a;
			a.x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y;
			a.y = lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z;
			a.z = lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x;
			a.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
			return a;
		}

#pragma endregion

	};
}
