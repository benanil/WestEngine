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
		Entity* entities[2048];
		unsigned short entityCount;
		bool disposed;
		void InspectorWindow() const;
		void HierarchyWindow() const;
	public:
		std::string path;
		const char* name;
		unsigned char index;
	public:
		~Scene();
		Scene();
		Scene(const char* path);
		static Entity* CurrentEntity;
		static void SetCurrentEntity(Entity* entity);
		static Scene* Create(const char* name);
		void Start() const;
		void Update() const;
		void Save() const;
		void EditorUpdate() const;
		void Load();
		void Destroy();
		void AddEntity(Entity* entity);
		void RemoveEntity(Entity* entity);
	};

	class SceneManager {
		Scene* scenes[12];
		unsigned char sceneCount;
		Scene* CurrentScene;
		void _DeleteScene(const unsigned char& index);
		void _DeleteScene(const char* name);
		void _AddScene(Scene* scene);
		void _LoadScene(const unsigned char& index);
		void _LoadScene(std::string_view name);
		void _Update();
	public:
		static void Update()  { Get()._Update(); }
		static Scene* GetActiveScene();
		static void DeleteScene(const unsigned char& index);
		static void DeleteScene(const char* name);
		static void AddScene(Scene* scene);
		static void LoadScene(const unsigned char& index);
		static void LoadScene(std::string_view name);
		static const unsigned char SceneCount() { return Get().sceneCount; };
		
		static SceneManager& Get()
		{
			static SceneManager instance;
			return instance;
		}
	};

	// save scenes as binary
	class SceneSaver
	{
	public:
		static void Save(std::string_view path);
		static Scene Load(std::string_view path);
	};
}

