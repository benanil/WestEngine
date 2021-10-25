#pragma once

#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
// #define GLM_FORCE_SIMD_AVX2
#define GLM_FORCE_SSE2

#include "Time.h"
#include "Event.h"
#include "glad.h"
#include <Input.h>
#include <Device.h>
#include "glm/glm.hpp"
#include "Event.h"
#include "Helper.h"
#include <iostream>
#include <string>


#define RETURNIF(cond) if(cond) return;


#define WPROPERTY(type, var) \
    type _##var; \
    const type& Get##var() const { return _##var; }\
    void Set##var(type val) { _##var = val; }