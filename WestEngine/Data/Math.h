#pragma once
#ifndef INL_FRND 
#	define INL_FRND inline friend
#endif
#include "vec2.h"
#include "vec3.h"
#include "Data/SSE2_Math/ivec4.h"
#include "Data/SSE2_Math/vec4.h"
#include "Data/SSE2_Math/mat4.h"

namespace WestEngine
{
	// static void DecomposeMtx(const Math::mat& m, Math::vec3& pos, Math::quat& rot, Math::vec3& scale);
	// static void DecomposeMtx(const Math::mat4& m, Math::vec3& pos, Math::quat& rot);
}