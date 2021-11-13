#include "Transform.h"
#include "Data/Math.h"
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "imgui/imgui.h"
#include "glm/simd/matrix.h"
#include <glm/gtc/type_ptr.hpp>

namespace WestEngine
{
	Transform::~Transform()  {
		RETURNIF(disposed);
		disposed = true;
		OnRemoved();
	}

	Transform::Transform(const Entity* _entity) : Companent(_entity, "Transform"),
		rotation(
			
			
			
			identity<
			
			
			
			
			
			quat>()),
		matrix(Math::identity<Math::mat4>()), 
		scale(Math::one<Math::vec3>()) {

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
		
		matrix = Math::identity<Math::mat4>() * Math::toMat4(rotation)
			            * Math::scale(scale) * Math::translate(position);

		if (notify) {
			OnTransformChanged.Invoke(Math::value_ptr(matrix));
		}
	}

	void Transform::SetMatrix(const Math::mat4& mat4, bool updateMatrix) {
		matrix = mat4;

		position = matrix[3];
		for (int i = 0; i < 3; i++)
			scale[i] = Math::length(Math::vec3(matrix[i]));
		const Math::mat3 rotMtx(
			Math::vec3(matrix[0]) / scale[0],
			Math::vec3(matrix[1]) / scale[1],
			Math::vec3(matrix[2]) / scale[2]);
		rotation = Math::quat_cast(rotMtx);

		eulerAngles = Math::eulerAngles(rotation);
		eulerAngles = Math::vec3(Math::degrees(eulerAngles.x), Math::degrees(eulerAngles.y), Math::degrees(eulerAngles.z));
		if (updateMatrix) UpdateTranslation();
	}
	
	void Transform::SetPosition(const Math::vec3& vec, bool updateMatrix) {
		position = vec;
		if (updateMatrix) UpdateTranslation();
	}
	
	void Transform::SetScale(const Math::vec3& vec, bool updateMatrix) {
		scale = vec;
		if (updateMatrix) UpdateTranslation();
	}

	/// <param name="euler">in degree</param>
	void Transform::SetEulerAngles(const Math::vec3& euler, bool updateMatrix) {
		eulerDegree = euler;
		eulerAngles = Math::vec3(Math::radians(euler.x), Math::radians(euler.y), Math::radians(euler.z));
		if (updateMatrix) UpdateTranslation();
	}
	
	void Transform::SetRotation(const Math::quat& quat, bool updateMatrix) {
		rotation = quat;
		eulerAngles = Math::eulerAngles(rotation);
		eulerDegree = Math::vec3(Math::degrees(eulerAngles.x), Math::degrees(eulerAngles.y), Math::degrees(eulerAngles.z));
		if (updateMatrix) UpdateTranslation();
	}
}