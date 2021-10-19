#pragma once
namespace WestEngine
{
	/// <summary>
	/// this class used like a interface like in C#
	/// </summary>
	class Behaviour abstract
	{
	public:
		std::string name;
		virtual void Update(const float& dt) = 0;
		virtual void Start() = 0;
		virtual void OnValidate() = 0;
		virtual void OnImgui() = 0;
		virtual void Save() = 0;
		virtual void Load() = 0;
	};
}
