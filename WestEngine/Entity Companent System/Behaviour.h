#pragma once
namespace WestEngine
{
	/// <summary>
	/// this class used like a interface in C#
	/// </summary>
	class Behaviour abstract
	{
	protected:
		bool disposed;
	public:
		const char* name;
		Behaviour(const char* _name);
		virtual void Update(const float& dt) = 0;
		virtual void Start() = 0;
		virtual void OnValidate() = 0;
		virtual void OnImgui() = 0;
		virtual void Save() = 0;
		virtual void Load() = 0;
	};
}
