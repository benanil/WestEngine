#pragma once
#include "Common.h"
#include "Behaviour.h"
#include "Entity.h"
#include "Component.h"
#include "glm/detail/type_quat.hpp"
#include "glm/simd/matrix.h"

namespace WestEngine
{
	class Transform : public Companent
	{
		glm::vec3 eulerAngles;
		EventMat OnTransformChanged;
	public:
		~Transform();
		Transform(const Entity* _entity);
		Transform* parent;

		glm::mat4 matrix     ;
		glm::vec3 position   ;
		glm::vec3 scale      ;
		glm::vec3 eulerDegree;
		glm::quat rotation   ;

		const glm::mat4& GetMatrix()      const { return matrix; }
		const glm::vec3& GetPosition()    const { return position; }
		const glm::vec3& GetScale()       const { return scale; }
		const glm::vec3& GetEulerAngles() const { return eulerAngles; }
		const glm::quat& GetRotation()    const { return rotation; }

		void SetMatrix     (const glm::mat4& mat4 , bool updateMatrix = true);
		void SetPosition   (const glm::vec3& vec3 , bool updateMatrix = true);
		void SetScale      (const glm::vec3& vec3 , bool updateMatrix = true);
		void SetEulerAngles(const glm::vec3& euler, bool updateMatrix = true);
		void SetRotation   (const glm::quat& quat , bool updateMatrix = true);

		void Update(const float& dt) override;
		void Start() override;
		void OnValidate() override;
		void OnImgui() override;
		void Save() override;
		void Load() override;

		void AddOnTransformChanged(const CallbackMat& action);
		void UpdateTranslation(bool notify = true);
	};
}

