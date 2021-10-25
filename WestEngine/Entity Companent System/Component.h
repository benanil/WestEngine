#pragma once
#include "Common.h"
#include "Behaviour.h"

namespace WestEngine
{
	class Entity;

	class Companent abstract : public Behaviour
	{
	public:
		/// <summary> correspanding entity</summary>
		const Entity* entity;
		/// <summary> if anything referancing this companent
		/// must avare of ve are deleting it, we don't want to deal with dangling pointers</summary>
		Event OnRemoved;
	public:
		Companent(const Entity* entity, const char* name);// inside of entity.cpp
		virtual void Update(const float& dt) override = 0;
		virtual void Start() override = 0;
		virtual void OnValidate() override = 0;
		virtual void OnImgui() override = 0;
	};
	
}