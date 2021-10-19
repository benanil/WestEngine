#include "Transform.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "imgui/imgui.h"

namespace WestEngine
{
	Transform::~Transform() {  }

	Transform::Transform(Entity* _entity) :
		entity(_entity) , 
		rotation(glm::identity<glm::quat>()),
		matrix(glm::identity<glm::mat4>()), 
		scale(glm::one<glm::vec3>()) {
	}

	void Transform::Update(const float& dt) { }
	void Transform::Start() { }

	void Transform::OnValidate() {
		UpdateTranslation();
	}
	
	void Transform::OnImgui() {

		if (ImGui::CollapsingHeader("Transform")) {
			if (ImGui::DragFloat3("Position", &position.x, 0.1f, -10000, 10000)) UpdateTranslation();
			if (ImGui::DragFloat3("Euler", &eulerDegree.x, 0.1f, -10000, 10000)) UpdateTranslation();
			if (ImGui::DragFloat3("Scale", &scale.x, 0.1f, 0, 1000)) UpdateTranslation();
		}
	}

	void Transform::AddOnTransformChanged(const Action& action) { OnTransformChanged.Add(action); }

	void Transform::UpdateTranslation(bool notify = true) {
		matrix = glm::toMat4(rotation) * glm::scale(scale) * glm::translate(position);
		if (notify) {
			OnTransformChanged.Invoke();
		}
	}

	void Transform::SetMatrix(const glm::mat4& mat4, bool updateMatrix = true) {
		matrix = mat4;
		if (updateMatrix) UpdateTranslation();
	}
	
	void Transform::SetPosition(const glm::vec3& vec, bool updateMatrix = true) {
		position = vec;
		if (updateMatrix) UpdateTranslation();
	}
	
	void Transform::SetScale(const glm::vec3& vec, bool updateMatrix = true) {
		scale = vec;
		if (updateMatrix) UpdateTranslation();
	}

	/// <param name="euler">in degree</param>
	void Transform::SetEulerAngles(const glm::vec3& euler, bool updateMatrix = true) {
		eulerDegree = euler;
		eulerAngles = glm::degrees<glm::vec3>(euler);
		if (updateMatrix) UpdateTranslation();
	}
	
	void Transform::SetRotation(const glm::quat& quat, bool updateMatrix = true) {
		rotation = quat;
		if (updateMatrix) UpdateTranslation();
	}
}