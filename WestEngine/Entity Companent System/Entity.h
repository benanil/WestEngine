#pragma once
#include "Common.h"
#include "Behaviour.h"
#include "Transform.h"
#include "Component.h"

namespace WestEngine
{
	class Transform;

	class Entity : public Behaviour
	{
		Companent* companents[12];
		unsigned char companentCount;
	public:
		Transform* transform;
		/// <summary> if anything referancing this companent
		/// must avare of ve are deleting it, we don't want to deal with dangling pointers</summary>
		Event OnRemoved;
		/// <summary> entitys id in the scene's entity stack </summary>
		unsigned short globalIndex;
	public:
		~Entity();
		Entity();
		Entity(const char* _name);

		void Update(const float& dt);
		void Start() override;
		void OnValidate() override;
		void OnImgui() override;
		void Save() override ;
		void Load() override;

		template<typename Companent> 
		Companent* GetCompanent();
		Companent* GetCompanent(unsigned char& index);
		
		void AddCompanent(Companent* companent);
		
		void RemoveCompanent(int index);
		template<typename Companent> void RemoveCompanent();
	};
}

