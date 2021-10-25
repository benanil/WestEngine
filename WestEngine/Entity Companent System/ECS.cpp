#include "Behaviour.h"
#include "Component.h"
#include "Entity.h"
#include "Scene.h"
#include "Transform.h"

namespace WestEngine
{
	Behaviour::Behaviour(const char* _name) : name(_name){}
	Companent::Companent(const Entity* _entity, const char* name) 
		: Behaviour(name), entity(_entity){ }

	Entity::~Entity() {
		if (disposed) return;
		for (unsigned char i = 0; i < companentCount; i++)
		{
			companents[i]->OnRemoved();
			delete companents[i];
		}
		transform->~Transform();
		delete(transform);
		this->OnRemoved();
	}

	Entity::Entity() : Behaviour("entity"), transform(new Transform(this)) {

	}

	Entity::Entity(const char* Name)
		: Behaviour(Name) , transform(new Transform(this)){
		SceneManager::GetActiveScene()->AddEntity(this);
	}

	void Entity::Update(const float& dt) {
		for (unsigned char i = 0; i < companentCount; i++) {
			companents[i]->Update(dt);
		}
	}

	void Entity::Start() {
		for (unsigned char i = 0; i < companentCount; i++) {
			companents[i]->Start();
		}
	}

	void Entity::OnValidate() {
		for (unsigned char i = 0; i < companentCount; i++) {
			companents[i]->OnValidate();
		}
	}

	void Entity::OnImgui()
	{
		transform->OnImgui();
		for (unsigned char i = 0; i < companentCount; i++) {
			companents[i]->OnImgui();
		}
	}
	
	void Entity::Save() {
		
	}

	void Entity::Load() {

	}

	Companent* Entity::GetCompanent(unsigned char& index)
	{
		return companents[index];
	}

	template<typename Companent> Companent* Entity::GetCompanent()
	{
		for (unsigned char i = 0; i < companentCount; i++)
		{
			if (typeid(Companent).hash_code() == typeid(companents[i]).hash_code())
			{
				return GetCompanent(i);
			}
		}
		return nullptr;
	}
	
	void Entity::AddCompanent(Companent* companent) {
		companents[companentCount++] = companent;
	}

	void Entity::RemoveCompanent(int index)
	{
		RETURNIF(companentCount == 0);
		companents[index]->OnRemoved();
		delete companents[index];
		
		companentCount--;
		companents[index] = companents[companentCount];
	}

	template<typename T> void Entity::RemoveCompanent() {
		for (unsigned char i = 0; i < companentCount; i++)
		{
			if (typeid(T).hash_code() == typeid(companents[i]).hash_code())
			{
				RemoveCompanent(i);
				break;
			}
		}
	}
}

