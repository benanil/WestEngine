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
		
		
		
		
		vec3 eulerAngles;
		EventMat OnTransformChanged;
	public:
		~Transform();
		Transform(const Entity* _entity);
		Transform* parent;

		
		
		
		
		
		
		
		mat4 matrix;
		Math::vec3 position   ;
		Math::vec3 scale      ;
		Math::vec3 eulerDegree;
		Math::quat rotation   ;

		const Math::mat4& GetMatrix()      const { return matrix; }
		const Math::vec3& GetPosition()    const { return position; }
		const Math::vec3& GetScale()       const { return scale; }
		const Math::vec3& GetEulerAngles() const { return eulerAngles; }
		const Math::quat& GetRotation()    const { return rotation; }

		void SetMatrix     (const Math::mat4& mat4 , bool updateMatrix = true);
		void SetPosition   (const Math::vec3& vec3 , bool updateMatrix = true);
		void SetScale      (const Math::vec3& vec3 , bool updateMatrix = true);
		void SetEulerAngles(const Math::vec3& euler, bool updateMatrix = true);
		void SetRotation   (const Math::quat& quat , bool updateMatrix = true);

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

