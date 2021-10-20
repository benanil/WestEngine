#include "Scene.h"
#include "spdlog/spdlog.h"

namespace WestEngine
{
	Scene::~Scene() {
		entities.clear();
	}

	Scene::Scene() : path("Scenes/default.scene"), name("default") 
	{
		spdlog::info("scene added to scenes");
		SceneManager::AddScene(this);
	}

	std::shared_ptr<Scene> Scene::Create(std::string name) {
		auto scene = std::make_shared<Scene>();
		scene->name = name;
		scene->index = SceneManager::SceneCount();
		return scene;
	}

	Scene::Scene(std::string_view path) {
		// to be continued
	}

	void Scene::Start() const {
		for (auto& entity : entities) {
			entity->Start();
		}
	}

	void Scene::Update() const {
		for (auto& entity : entities) {
			entity->Update(Time::deltaTime);
		}
	}

	void Scene::Save() const {
		
	}

	void Scene::Load() {
		
	}

	void Scene::Destroy() {
		entities.clear();
	}

	void Scene::EditorUpdate() const {
		InspectorWindow();
		HierarchyWindow();
	}

	Entity* Scene::CurrentEntity = NULL;

	void Scene::InspectorWindow() const {

		ImGui::Begin("Properties");
		if (CurrentEntity) { CurrentEntity->OnImgui(); }
		ImGui::End();
	}

	void Scene::HierarchyWindow() const {
		static bool open = true;
		ImGui::Begin("Inspector");
		for (auto& entity : entities) 
		{
			if (ImGui::TreeNode(entity->name.c_str())) {
				ImGui::TreePop();
			}
		}
		ImGui::End();
	}

	void Scene::AddEntity(const std::shared_ptr<Entity> entity) {
		entities.push_back(entity);
	}

	void Scene::AddEntity(const Entity* entity) {
		entities.push_back(std::make_shared<Entity>(entity));
	}
	
	void Scene::RemoveEntity(const Entity* entity) {
		entities.remove_if([entity](Entity en)
		{
			return en.name == entity->name;
		});
	}

	// SCENE MANAGER 
	std::shared_ptr<Scene> SceneManager::CurrentScene = NULL;
	std::shared_ptr<Scene> SceneManager::GetActiveScene() { return CurrentScene; }
	
	void SceneManager::RemoveScene(int index) {
		scenes.remove_if([index](Scene scene)
		{
			return scene.index == index;
		});
	}
	
	void SceneManager::RemoveScene(const std::string& name) {
		scenes.remove_if([&name](Scene scene)
		{
			return scene.name == name;
		});
	}

	void SceneManager::AddScene(std::shared_ptr<Scene> scene) {
		scenes.push_back(scene);
	}
	
	void SceneManager::AddScene(const Scene* scene) {
		scenes.push_back(std::make_shared<Scene>(scene));
	}
	
	void SceneManager::LoadScene(int index) {
		for (auto& scene : scenes) 
		{
			if (scene->index == index) 
			{
				if (CurrentScene) { CurrentScene->Destroy(); }
				scene->Load();
				CurrentScene = scene;
				return;
			}
		}
	}
	
	// SAVE LOAD
	void SceneManager::LoadScene(std::string_view name) {
	
	}

	void SceneSaver::Save(std::string_view path) {
	
	}
	
	Scene SceneSaver::Load(std::string_view path) {
		return Scene();
	}
}