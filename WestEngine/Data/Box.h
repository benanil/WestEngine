#pragma once
#include "Math.h"
#include <limits>

#undef min
#undef max

namespace WestEngine
{
	static constexpr float minf = std::numeric_limits<float>::min();
	static constexpr float maxf = std::numeric_limits<float>::infinity();
	static constexpr int mini = std::numeric_limits<int>::min();
	static constexpr int maxi = std::numeric_limits<int>::infinity();

	struct Box2
	{
		Math::vec2 min, max;

		Box2() : min(Math::vec2(0, 0)), max(Math::vec2(0, 0)) {}
		Box2(Math::vec2 Min, Math::vec2 Max) : min(Min), max(Max) {}

		bool Contains(const Math::vec2& point) const {
			return point.x > min.x && point.y > min.y && 
				   point.x < max.x && point.y < max.y;
		}
	};

	struct Box3
	{
		Math::vec3 min, max;

		Box3() : min(Math::vec3(0, 0, 0)), max(Math::vec3(0, 0, 0)) {}
		Box3(const Math::vec3& Min, const Math::vec3& Max) : min(Min), max(Max) {}

		bool Contains(const Math::vec3& point) const {
			return point.x > min.x && point.y > min.y && point.z > min.z && 
				   point.x < max.x && point.y < max.y && point.z < max.z;
		}
	};
}

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))