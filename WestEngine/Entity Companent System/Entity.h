#pragma once
#include "Common.h"
#include "Companent.h"
#include "Behaviour.h"
#include "Transform.h"
#include <list>

namespace WestEngine
{
	class Entity : public Behaviour
	{
		std::list<std::shared_ptr<Companent>> companents;
	public:
		~Entity();
		Entity();
		Entity(const std::string& _name);

		std::string name;
		Transform* transform;

		void Update(const float& dt);
		void Start();
		void OnValidate();
		void OnImgui();
		void AddCompanent(Companent* companent);
		void AddCompanent(std::shared_ptr<Companent> companent);
		template<typename T>
		void RemoveCompanent();
	};
}

