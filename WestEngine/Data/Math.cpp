#include "Math.h"
#include <algorithm>

namespace WestEngine
{
	// static void DecomposeMtx(const Math::mat4& m, Math::vec3& pos, Math::quat& rot, Math::vec3& scale);
	// 
	// static void DecomposeMtx(const Math::mat4& m, Math::vec3& pos, Math::quat& rot, Math::vec3& scale)
	// {
	// 	pos = m[3];
	// 	for (int i = 0; i < 3; i++)
	// 		scale[i] = Math::length(Math::vec3(m[i]));
	// 	const Math::mat3 rotMtx(
	// 		Math::vec3(m[0]) / scale[0],
	// 		Math::vec3(m[1]) / scale[1],
	// 		Math::vec3(m[2]) / scale[2]);
	// 	rot = Math::quat_cast(rotMtx);
	// }
	// 
	// void Math::DecomposeMtx(const Math::mat4& m, Math::vec3& pos, Math::quat& rot)
	// {
	// 	pos = m[3];
	// 	rot = Math::quat_cast(m);
	// }
}