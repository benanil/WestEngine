#include "Transform.h"
#include "Data/Math.h"
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "imgui/imgui.h"

namespace WestEngine
{
	Transform::~Transform()  {
		RETURNIF(disposed);
		disposed = true;
		OnRemoved();
	}

	Transform::Transform(const Entity* _entity) : Companent(_entity, "Transform"),
		rotation(glm::identity<glm::quat>()),
		matrix(glm::identity<glm::mat4>()), 
		scale(glm::one<glm::vec3>()) {

	}

	void Transform::Update(const float& dt) { }
	void Transform::Start() { }
	
	void Transform::Save() {}
	void Transform::Load() {}

	void Transform::OnValidate() {
		UpdateTranslation();
	}
	
	void Transform::OnImgui() {

		if (ImGui::CollapsingHeader("Transform")) {
			if (ImGui::DragFloat3("Position", &position.x, 0.1f)) UpdateTranslation();
			if (ImGui::DragFloat3("Euler", &eulerDegree.x, 0.1f)) UpdateTranslation();
			if (ImGui::DragFloat3("Scale", &scale.x, 0.1f, 0, 1000)) UpdateTranslation();
		}
	}

	void Transform::AddOnTransformChanged(const CallbackMat& action) { OnTransformChanged.Add(action); }

	void Transform::UpdateTranslation(bool notify) {
		matrix = glm::identity<glm::mat4>() * glm::toMat4(rotation) 
			    * glm::scale(scale) * glm::translate(position);
		if (notify) {
			OnTransformChanged.Invoke(&matrix[0][0]);
		}
	}

	void Transform::SetMatrix(const glm::mat4& mat4, bool updateMatrix) {
		matrix = mat4;

		position = matrix[3];
		for (int i = 0; i < 3; i++)
			scale[i] = glm::length(glm::vec3(matrix[i]));
		const glm::mat3 rotMtx(
			glm::vec3(matrix[0]) / scale[0],
			glm::vec3(matrix[1]) / scale[1],
			glm::vec3(matrix[2]) / scale[2]);
		rotation = glm::quat_cast(rotMtx);

		eulerAngles = glm::eulerAngles(rotation);
		eulerAngles = glm::vec3(glm::degrees(eulerAngles.x), glm::degrees(eulerAngles.y), glm::degrees(eulerAngles.z));
		if (updateMatrix) UpdateTranslation();
	}
	
	void Transform::SetPosition(const glm::vec3& vec, bool updateMatrix) {
		position = vec;
		if (updateMatrix) UpdateTranslation();
	}
	
	void Transform::SetScale(const glm::vec3& vec, bool updateMatrix) {
		scale = vec;
		if (updateMatrix) UpdateTranslation();
	}

	/// <param name="euler">in degree</param>
	void Transform::SetEulerAngles(const glm::vec3& euler, bool updateMatrix) {
		eulerDegree = euler;
		eulerAngles = glm::vec3(glm::degrees(euler.x), glm::degrees(euler.y), glm::degrees(euler.z));
		if (updateMatrix) UpdateTranslation();
	}
	
	void Transform::SetRotation(const glm::quat& quat, bool updateMatrix) {
		rotation = quat;
		if (updateMatrix) UpdateTranslation();
	}

	
}