#pragma once
#include "Common.h"
#include <list>
#include <string>
#include <Entity.h>
#include <filesystem>

namespace WestEngine
{
	class Scene
	{
		std::list<std::shared_ptr<Entity>> entities;
		void InspectorWindow() const;
		void HierarchyWindow() const;
	public:
		std::string path;
		std::string name;
		int index;
	public:
		~Scene();
		Scene();
		Scene(std::string_view path);
		static Entity* CurrentEntity;
		static std::shared_ptr<Scene> Create(std::string name);
		void Start() const;
		void Update() const;
		void Save() const;
		void EditorUpdate() const;
		void Load();
		void Destroy();
		void AddEntity(const std::shared_ptr<Entity> entity);
		void AddEntity(const Entity* entity);
		void RemoveEntity(const Entity* entity);
	};

	class SceneManager {
		static std::list<std::shared_ptr<Scene>> scenes;
		static std::shared_ptr<Scene> CurrentScene;
	public:
		static void Update() 
		{
			if (CurrentScene) {
				CurrentScene->EditorUpdate();
				CurrentScene->Update();
			}
		}
		static std::shared_ptr<Scene> GetActiveScene();
		static void RemoveScene(int index);
		static void RemoveScene(const std::string& name);
		static void AddScene(std::shared_ptr<Scene> scene);
		static void AddScene(const Scene* scene);
		static void LoadScene(int index);
		static void LoadScene(std::string_view name);
		static const int SceneCount() { return scenes.size(); };
	};

	// save scenes as binary
	class SceneSaver
	{
	public:
		static void Save(std::string_view path);
		static Scene Load(std::string_view path);
	};

}

