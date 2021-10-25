#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

#include <limits>
#undef min
#undef max

namespace WestEngine::Math
{
	static constexpr float minf = std::numeric_limits<float>::min();
	static constexpr float maxf = std::numeric_limits<float>::infinity();
	static constexpr int mini = std::numeric_limits<int>::min();
	static constexpr int maxi = std::numeric_limits<int>::infinity();

	struct Box2
	{
		glm::vec2 min, max;

		Box2() : min(glm::zero<glm::vec2>()), max(glm::zero<glm::vec2>()) {}
		Box2(glm::vec2 Min, glm::vec2 Max) : min(Min), max(Max) {}

		bool Contains(const glm::vec2& point) {
			return point.x > min.x && point.y > min.y && 
				   point.x < max.x && point.y < max.y;
		}
	};

	struct Box3
	{
		glm::vec3 min, max;

		Box3() : min(glm::zero<glm::vec3>()), max(glm::zero<glm::vec3>()) {}
		Box3(const glm::vec3& Min, const glm::vec3& Max) : min(Min), max(Max) {}

		bool Contains(const glm::vec3& point) {
			return point.x > min.x && point.y > min.y && point.z > min.z && 
				   point.x < max.x && point.y < max.y && point.z < max.z;
		}
	};
}

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))