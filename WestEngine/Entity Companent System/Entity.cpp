#include "Entity.h"

namespace WestEngine
{
	Entity::~Entity() {
		companents.clear();
		free(transform);
	}

	Entity::Entity() : name("entity"), transform(new Transform(this)) {

	}

	Entity::Entity(const std::string& Name) : name(Name) ,
		transform(new Transform(this)){
	}

	void WestEngine::Entity::Update(const float& dt) {
		for (auto& companent : companents) {
			companent->Update(dt);
		}
	}

	void WestEngine::Entity::Start() {
		for (auto& companent : companents) {
			companent->Start();
		}
	}

	void WestEngine::Entity::OnValidate() {
		for (auto& companent : companents) {
			companent->OnValidate();
		}
	}

	void WestEngine::Entity::OnImgui()
	{
		for (auto& companent : companents) {
			companent->OnImgui();
		}
	}
	
	void Entity::AddCompanent(Companent* companent) {
		companents.push_back(std::make_shared<Companent>(companent));
	}

	void Entity::AddCompanent(std::shared_ptr<Companent> companent) {
		companents.push_back(companent);
	}

	template<typename T> void Entity::RemoveCompanent() {
		for (Companent* companent : companents) 
		{
			if (std::dynamic_pointer_cast<T>(companent)) 
			{
				companents.remove(companent);
			}
		}
	}
}

