#pragma once
#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/detail/type_quat.hpp"
namespace WestEngine
{
	class Math
	{
	public:
		static void DecomposeMtx(const glm::mat4& m, glm::vec3& pos, glm::quat& rot, glm::vec3& scale);
		static void DecomposeMtx(const glm::mat4& m, glm::vec3& pos, glm::quat& rot);
	};
}