#pragma once
#include "Common.h"
#include "Behaviour.h"
#include "Transform.h"
#include <list>

namespace WestEngine
{
	class Companent abstract : virtual Behaviour
	{
	protected:
		const Entity* entity;
	public:
		Companent(const Entity* entity);// inside of entity.cpp
		/// <summary> correspanding entity</summary>
		virtual void Update(const float& dt) override = 0;
		virtual void Start() override = 0;
		virtual void OnValidate() override = 0;
		virtual void OnImgui() override = 0;
	};

	class Entity : virtual Behaviour
	{
		std::list<std::shared_ptr<Companent>> companents;
	public:
		~Entity();
		Entity();
		Entity(const std::string& _name);

		std::string name;
		Transform* transform;

		void Update(const float& dt);
		void Start() override;
		void OnValidate() override;
		void OnImgui() override;
		void Save() override ;
		void Load() override;
		void AddCompanent(Companent* companent);
		void AddCompanent(std::shared_ptr<Companent> companent);
		
		template<typename T> void RemoveCompanent();
	};
}

