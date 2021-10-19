#pragma once

#include "Time.h"
#include "Event.h"
#include "glm/glm.hpp"
#include <Device.h>
#include <Texture.h>
#include "Event.h"
#include "Mesh.h"
#include <Shader.h>
#include <Mesh.h>
#include "Editor.h"
#include "Camera.h"
#include <Input.h>
#include "Helper.h"

typedef unsigned char byte;
typedef unsigned int uint;


#define WPROPERTY(type, var) \
    type _##var; \
    const type& Get##var() const { return _##var; }\
    void Set##var(type val) { _##var = val; }