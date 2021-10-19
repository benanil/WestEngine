#pragma once
#include "Behaviour.h"

namespace WestEngine
{
	class Companent abstract : public Behaviour
	{
	public:
		virtual void Update(const float& dt) = 0;
		virtual void Start() = 0;
		virtual void OnValidate() = 0;
		virtual void OnImgui() = 0;
	};
}

