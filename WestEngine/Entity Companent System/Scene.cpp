#include "Scene.h"
#include "Behaviour.h"
#include "Entity.h"
#include "spdlog/spdlog.h"
#include "imgui/imgui.h"
#include "Renderer.h"
#include "Editor.h"

namespace WestEngine
{
	#pragma region Scene

	Scene::~Scene() {
		RETURNIF(disposed == true);
		disposed = true;
		spdlog::warn("scene removed from the memory");
		Destroy();
	}

	Scene::Scene() : path("Scenes/default.scene"), name("default") 
	{
		spdlog::info("scene added to scenes");
		SceneManager::Get().AddScene(this);
	}

	Scene* Scene::Create(const char* name) {
		auto scene = new Scene();
		scene->name = name;
		scene->index = SceneManager::Get().SceneCount();
		SceneManager::Get().AddScene(scene);
		return scene;
	}


	Scene::Scene(const char* path) {
		// to be continued
	}

	void Scene::Start() const {
		for (unsigned char i = 0; i < entityCount; i++) {
			entities[i]->Start();
		}
	}

	void Scene::Update() const {
		for (unsigned char i = 0; i < entityCount; i++) {
			entities[i]->Update(Time::deltaTime);
		}
	}

	// use json serialization after that we may change to binary
	void Scene::Save() const {  }

	// use json serialization after that we may change to binary
	void Scene::Load() {  }

	void Scene::Destroy() {

		for (unsigned char i = 0; i < entityCount; i++) {
			delete(entities[i]);
			entities[i] = nullptr;
		}
		
		entityCount = 0;
	}

	void Scene::EditorUpdate() const {
		InspectorWindow();
		HierarchyWindow();
	}

	Entity* Scene::CurrentEntity = NULL;

	void Scene::SetCurrentEntity(Entity* entity)
	{
		CurrentEntity = entity;
	}
	
	void Scene::InspectorWindow() const {
		ImGui::Begin("Properties");
		ImGui::Separator();
		if (ImGui::BeginTabBar("Theme"))
		{
			if (ImGui::TabItemButton("Half Life")) Editor::HalfLifeTheme();
			if (ImGui::TabItemButton("Dark")) Editor::DarkTheme();
		}
		ImGui::EndTabBar();
		if (CurrentEntity) { CurrentEntity->OnImgui(); }
		ImGui::End();
	}

	void Scene::HierarchyWindow() const
	{
		ImGui::Begin("Inspector");
		
		for (unsigned char i = 0; i < entityCount; i++) 
		{
			if (ImGui::TreeNode(entities[i]->name)) 
			{
				ImGui::TreePop();
			}
		}
		ImGui::End();
	}

	void Scene::AddEntity(Entity* entity) 
	{
		entities[entityCount++] = entity;
	}

	void Scene::RemoveEntity(Entity* entity) 
	{
		unsigned short oldIndex = entity->globalIndex;
		entities[oldIndex]->~Entity();
		delete entities[oldIndex];
		entities[oldIndex] = nullptr; // for dangling pointer
		
		entityCount--;
		// moves last entity ptr to removed entity's position
		entities[oldIndex] = entities[entityCount];
		entities[entityCount] = nullptr; 
	}

	#pragma endregion

	#pragma region SceneManager
	// SCENE MANAGER 
	
	void SceneManager::_Update()
	{
		if (CurrentScene) {
			CurrentScene->EditorUpdate();
			CurrentScene->Update();
		}
	}

	void SceneManager::_DeleteScene(const char* name) {
		unsigned char index = 0;
		for (; index < sceneCount; index++) {
			if (scenes[index]->name == name) break;
		}
		Renderer::Get().ClearRenderers(); // removes all of the meshes from renderer queue
		_DeleteScene(index);
	}
	
	void SceneManager::_DeleteScene(const unsigned char& index) {
		RETURNIF(sceneCount == 0); // we need at least 1 scene
		// delete scene
		scenes[index]->~Scene();
		delete scenes[index];
		sceneCount--; // decrement scene count
		
		scenes[index] = scenes[sceneCount]; // move last ptr to removed index
		scenes[index]->index = index;
		
		scenes[sceneCount] = nullptr;
	}

	void SceneManager::_AddScene(Scene* scene) {
		scene->index = sceneCount;
		scenes[sceneCount++] = scene;
	}
	
	void SceneManager::_LoadScene(const unsigned char& index) {
		if (CurrentScene)CurrentScene->Destroy();
		CurrentScene = scenes[index];
		scenes[index]->Load();
	}

	void SceneManager::_LoadScene(std::string_view name) {
		for (unsigned char i = 0; i < sceneCount; i++)
		{
			if (scenes[i]->name == name)
			{
				CurrentScene = scenes[i];
				scenes[i]->Load();
				break;
			}
		}
	}

	#pragma endregion

	// SAVE LOAD
	void SceneSaver::Save(std::string_view path) {
	
	}
	
	Scene SceneSaver::Load(std::string_view path) {
		return Scene();
	}
}