#pragma once
#include <iostream>
#include <vector>
#include "glm/glm.hpp"

namespace WestEngine
{ 
	// these are callbacks
	typedef void(*Action)();
	typedef void(*Actionf)(int);
	typedef void(*Actioni)(int);

	typedef void(*Changed2i)(const int&, const int&);
	typedef void(*Changed2f)(const float&, const float&);
	typedef void(*Changed3f)(const float&, const float&, const float&);

	class Event
	{
	private:
		std::vector<Action> actions;
	public:
		void Add(const Action& func);
		void Invoke() const;
		void operator()() { Invoke(); }
	};

	class Eventi
	{
	private:
		std::vector<Actioni> actions;
	public:
		void Add(const Actioni& func);
		void Invoke(const int& x) const;
		void operator()(const int& x) { Invoke(x); }
	};

	class Eventf
	{
	private:
		std::vector<Actionf> actions;
	public:
		void Add(const Actionf& func);
		void Invoke(const float& x) const;
		void operator()(const float& x) { Invoke(x); }
	};

	class Action2i
	{
	private:
		std::vector<Changed2i> actions;
	public:
		void Add(const Changed2i& func);
		void Invoke(const int& x, const int& y) const;
		void Invoke(const glm::ivec2& pos) const;
		void operator()(const glm::ivec2& pos) { Invoke(pos); }
		void operator()(const int& x, const int& y) const { Invoke(x, y); };
	};

	class Action2f
	{
	private:
		std::vector<Changed2f> actions;
	public:
		void Add(const Changed2f& func);
		void Invoke(const float& x, const float& y) const;
		void Invoke(const glm::vec2& pos) const;
		void operator()(const glm::vec2& pos) { Invoke(pos); }
		void operator()(const float& x, const float& y) const { Invoke(x, y); };
	};

	class Action3f
	{
	private:
		std::vector<Changed3f> actions;
	public:
		void Add(const Changed3f& func);
		void Invoke(const float& x, const float& y, const float& z) const;
		void Invoke(const glm::vec3& pos) const;
		void operator()(const glm::vec3& pos) { Invoke(pos); }
		void operator()(const float& x, const float& y, const float& z) const { Invoke(x, y, z); };
	};
}

